#include "SWI_DIP.h"
#include "dip_settings.h"
#include "swi_protocol.hpp"

#pragma region GLOBAL
DipSettings settings;
string workDir;
Mat img;
Mat img_source;
Mat img_preProcess;
Mat img_finish;
Circle sDial, lDial;
Line sIndicator, lIndicator;
Line zero_line;
int width, height;
double result_sec, result_min;
double fix;
#pragma endregion

int main(int argc, char** argv) {
	Info("Run in dependent mode");
	InitializeSettings(settings);
	if (argc == 6)
		GetSettings(argv);
	else
		GetSettings();
	ReadImage();
	DIP_PreProcess(img);
	DetectDial(img.clone());
	DetectIndicator(img.clone());
	DrawAll();
	SaveImage(img_finish, "finish");
	Settle();
	SendResult();
	return 0;
}
bool IsDependentMode(int argc, char** argv) {
	string mode;
	if (argc > 1)
		mode = argv[1];
	if (mode.find("dependent") != -1)
		return true;
	else
		return false;
}
void RunIndependentMode() {
	Info("Run in independent mode");
	workDir = "F:\\毕业设计\\图片素材\\程序测试";
	ReadImage();

}
void RunDependentMode() {
	Info("Run in dependent mode");
	GetSettings();
	ReadImage();
	DIP_PreProcess(img);
	//
	DetectDial(img.clone());
	//
	DetectIndicator(img.clone());
	DrawAll();
	SaveImage(img_finish, "finish");
	Settle();
	SendResult();
}
void GetSettings(char** argv) {
	Send(_P_SET_WorkDir);//设置工作路径
	workDir = argv[2];
	cout << argv[2] << endl;
	Send(_P_SET_SWSType);//设置秒表型号
	string type = argv[3];
	cout << argv[3] << endl;
	if (type == "504")
		settings.swType = SW504;
	else if (type == "505")
		settings.swType = SW505;
	Send(_P_SET_Estimate);//设置是否估读
	int estimate = atoi(argv[4]);
	cout << argv[4] << endl;
	if (estimate)
		settings.estimate = true;
	else
		settings.estimate = false;
	Send(_P_SET_FixValue);//设置修正值
	settings.fix = atof(argv[5]);
	cout << argv[5] << endl;
}
void GetSettings() {
	Send(_P_SET_WorkDir);//设置工作路径
	workDir = "F:\\毕业设计\\图片素材\\程序测试";
	Send(_P_SET_SWSType);//设置秒表型号
	settings.swType = SW504;
	Send(_P_SET_Estimate);//设置是否估读
	settings.estimate = false;
	Send(_P_SET_FixValue);//设置修正值
	settings.fix = 0.0;
}
void ReadImage() {
	string img_path = workDir + "\\source.jpg";
	img_source = imread(img_path);
	img = img_source;
	width = img_source.cols;
	height = img_source.rows;
}
void SaveImage(Mat img, const char* filename) {
	string save_path = workDir + '\\' + filename + ".jpg";
	imwrite(save_path, img);
}
void ShowImage(Mat img, const char* name) {
	int width = 640;
	int height = width * (double)(img.rows / img.cols);
	namedWindow(name, 0);
	resizeWindow(name, width, height);
	imshow(name, img);
}
void DIP_PreProcess(Mat& img) {
	Send(_P_MES_PreStart);
	Mat source = img;
	Mat out;
	switch (settings.filterMode)
	{
	case MEAN:
		blur(source, out, Size(9, 9));
		break;
	case MEDIAN:
		medianBlur(source, out, 7);
		break;
	case BILATERAL:
		bilateralFilter(source, out, 9, 75, 75);
		break;
	default:
		break;
	}
	img = out;
	SaveImage(img, "pre_process");
	Send(_P_MES_PreFinish);
}
void DIP_Binarize(Mat& img, bool inv) {
	Send(_P_MES_BinStart);
	Mat source = img;
	Mat gray;
	Mat out;
	cvtColor(source, gray, ColorConversionCodes::COLOR_BGR2GRAY);
	if (settings.binarizeMode == OTSU) {
		if (inv)
			threshold(gray, out, 0, 255, ThresholdTypes::THRESH_OTSU + ThresholdTypes::THRESH_BINARY_INV);
		else
			threshold(gray, out, 0, 255, ThresholdTypes::THRESH_OTSU);
	}
	else {
		if (inv)
			threshold(gray, out, settings.binarizeThreshold, 255, ThresholdTypes::THRESH_BINARY_INV);
		else
			threshold(gray, out, settings.binarizeThreshold, 255, ThresholdTypes::THRESH_BINARY);
	}
	img = out;
	const char* filename = inv ? "binarize_inv" : "binarize";
	SaveImage(img, filename);
	Send(_P_MES_BinFinish);
}
void DIP_Thin(Mat& img) {
	Send(_P_MES_ThinStart);
	Mat source = img;
	Mat out;
	Thin(source, out, settings.thinTimes);
	img = out;
	SaveImage(img, "thin");
	Send(_P_MES_ThinFinish);
}
void DIP_Open(Mat& img) {
	Send(_P_MES_OpenStart);
	Mat source = img;
	Mat out;
	Mat element = getStructuringElement(MorphShapes::MORPH_RECT, Size(5, 5));
	morphologyEx(source, out, MorphTypes::MORPH_OPEN, element);
	img = out;
	SaveImage(img, "open");
	Send(_P_MES_OpenFinish);
}
void DIP_Edge(Mat& img) {
	Send(_P_MES_EdgeStart);
	Mat source = img;
	Mat out;
	switch (settings.edgeMode)
	{
	case SOBEL:
		switch (settings.sobelDirection)
		{
		case X:
			Sobel(source, out, CV_8U, 1, 0);
			break;
		case Y:
			Sobel(source, out, CV_8U, 0, 1);
			break;
		case XY:
			Sobel(source, out, CV_8U, 1, 1);
			break;
		default:
			break;
		}
		break;
	case LAPLACE:
		Laplacian(source, out, CV_8U);
		break;
	case CANNY:
		Canny(source, out, settings.cannyThreshold1, settings.cannyThreshold2);
		break;
	default:
		break;
	}
	img = out;
	SaveImage(img, "edge");
	Send(_P_MES_EdgeFinish);
}
void DetectDial(Mat img) {
	Send(_P_MES_DialStart);
	DIP_Binarize(img, false);
	DIP_Edge(img);
	vector<Circle> circles = DIP_HoughCircle(img);
	Mat img_circles = img_source.clone();
	DrawCircle(img_circles, circles);
	SaveImage(img_circles, "circles");
	FilterCircle(circles);
	Mat img_dials = img_source.clone();
	DrawCircle(img_dials, circles);
	SaveImage(img_dials, "dials");
	sDial = circles[0];
	lDial = circles[1];
	zero_line = ToLine(GetCenter(lDial), GetCenter(sDial));
	Send(_P_MES_DialFinish);
}
void DetectIndicator(Mat img) {
	Send(_P_MES_IndStart);
	DIP_Binarize(img, true);
	DIP_Thin(img);
	DIP_Edge(img);
	vector<Line> lines = DIP_HoughLine(img);
	Mat img_lines = img_source.clone();
	DrawLine(img_lines, lines);
	SaveImage(img_lines, "lines");
	FilterLine(lines);
	Mat img_indicators = img_source.clone();
	DrawLine(img_indicators, lines);
	SaveImage(img_indicators, "indicators");
	Line line = lines[0];
	Point p1 = Point(line[0], line[1]);
	Point p2 = Point(line[2], line[3]);
	if (Length(GetCenter(sDial), p1) > Length(GetCenter(sDial), p2))
		sIndicator = ToLine(
			GetCenter(sDial), 
			IntersectionPoint(p1, GetCenter(sDial), sDial[2])
		);
	else
		sIndicator = ToLine(
			GetCenter(sDial),
			IntersectionPoint(p2, GetCenter(sDial), sDial[2])
		);//将圆心至直线与圆交点的连线作为指针
	line = lines[1];
	p1 = Point(line[0], line[1]);
	p2 = Point(line[2], line[3]);
	if (Length(GetCenter(lDial), p1) > Length(GetCenter(lDial), p2))
		lIndicator = ToLine(
			GetCenter(lDial),
			IntersectionPoint(p1, GetCenter(lDial), lDial[2])
		);
	else
		lIndicator = ToLine(
			GetCenter(lDial),
			IntersectionPoint(p2, GetCenter(lDial), lDial[2])
		);//将圆心至直线与圆交点的连线作为指针
	Send(_P_MES_IndFinish);
}
vector<Circle> DIP_HoughCircle(Mat img) {
	Send(_P_MES_HCStart);
	vector<Circle> circles;
	HoughCircles(
		img,
		circles,
		HoughModes::HOUGH_GRADIENT,
		settings.houghCircle_dp,
		settings.houghCircle_minDist,
		settings.houghCircle_param1,
		settings.houghCircle_param2
	);
	Send(_P_MES_HCFinish);
	return circles;
}
vector<Line> DIP_HoughLine(Mat img) {
	Send(_P_MES_HLStart);
	vector<Line> lines;
	HoughLinesP(
		img,
		lines,
		settings.houghLine_rho,
		settings.houghLine_theta,
		settings.houghLine_threshold,
		settings.houghLine_minLineLength,
		settings.houghLine_maxLineGap
	);
	Send(_P_MES_HLFinish);
	return lines;
}
void FilterCircle(vector<Circle>& circles) {
	if (circles.size() < 2)//圆少于2个，检测出错
	{
		Send(_P_ERR_HCError);
		return;
	}
	else if (circles.size() == 2)//圆刚好2个，不用筛选
		return;
	//清除不完整的圆
	vector<int> circles_to_remove;
	for (size_t i = 0; i < circles.size(); i++)
	{
		float x = circles[i][0];//圆心横坐标
		float y = circles[i][1];//圆心纵坐标
		int r = circles[i][2];//半径
		if (x + r > width || x - r < 0 || y + r > height || y - r < 0)//判断圆是否完整
		{
			circles_to_remove.push_back(i);
		}
	}
	RemoveCircle(circles, circles_to_remove);
	circles_to_remove.clear();
	//按半径大小排序
	sort(
		circles.begin(), 
		circles.end(), 
		[](Circle a, Circle b)->bool {return a[2] > b[2]; }
	);
	Circle lCircle = circles[0];//半径最大作为大表盘
	//检测小表盘
	for (size_t i = 0; i < circles.size(); i++)
	{
		float x = circles[i][0];//圆心横坐标
		float y = circles[i][1];//圆心纵坐标
		int r = circles[i][2];//半径
		if (Length(GetCenter(lDial), Point(x, y)) + r >= lDial[2] || y >= lDial[1])//判断是否在大表盘上半部分
			circles_to_remove.push_back(i);
	}
	RemoveCircle(circles, circles_to_remove);
	sort(
		circles.begin(),
		circles.end(),
		[](Circle a, Circle b)->bool {
			double ratio_a = (double)lDial[2] / a[2];
			double ratio_b = (double)lDial[2] / b[2];
			return abs(ratio_a - 3.6) < abs(ratio_b - 3.6);
		}
	);//按大小表盘半径比例接近3.6排序
	Circle sCircle = circles[0];
	circles = { sCircle, lCircle };
}
void FilterLine(vector<Line>& lines) {
	if (lines.size() < 2)//直线少于2个，检测出错
	{
		Send(_P_ERR_HCError);
		return;
	}
	else if (lines.size() == 2)//直线刚好2个，不用筛选
		return;
	//清除在表盘外的直线
	vector<int> lines_to_remove;
	for (size_t i = 0; i < lines.size(); i++)
	{
		if (Length(Midpoint(lines[i]), GetCenter(lDial)) > lDial[2])//判断直线是否在大表盘外
		{
			lines_to_remove.push_back(i);
		}
	}
	RemoveLine(lines, lines_to_remove);
	lines_to_remove.clear();
	auto angle = [](double cos)->double {return acos(abs(cos)) * 180 / CV_PI; };//计算夹角
	double threshold_angle = 15;//夹角阈值
	vector<Line> probable_sIndicator, probable_lIndicator;
	for (size_t i = 0; i < lines.size(); i++)
	{
		Point begin = Point(lines[i][0], lines[i][1]);
		Point end = Point(lines[i][2], lines[i][3]);
		if (angle(CosineLaw(GetCenter(sDial), begin, end)) < threshold_angle &&
			Length(Midpoint(begin, end), GetCenter(sDial)) < sDial[2])//与小表盘圆心共线，且在小表盘内
			probable_sIndicator.push_back(lines[i]);//可能为小表盘指针
		if (angle(CosineLaw(GetCenter(lDial), begin, end)) < threshold_angle)//与大表盘圆心共线
			probable_lIndicator.push_back(lines[i]);//可能为大表盘指针
	}
	sort(
		probable_sIndicator.begin(),
		probable_sIndicator.end(),
		[](Line l1, Line l2)->bool {
			double len1 = Length(l1);
			double len2 = Length(l2);
			return abs(len1 - sDial[2]) < abs(len2 - sDial[2]);
		}
	);//长度越接近表盘半径，越可能是指针
	sort(
		probable_lIndicator.begin(),
		probable_lIndicator.end(),
		[](Line l1, Line l2)->bool {
			double len1 = Length(l1);
			double len2 = Length(l2);
			return abs(len1 - lDial[2]) < abs(len2 - lDial[2]);
		}
	);//长度越接近表盘半径，越可能是指针
	lines = { probable_sIndicator[0], probable_lIndicator[0] };
}
void RemoveCircle(vector<Circle>& source, vector<int> target)
{
	int offset = 0;
	for (vector<int>::iterator it = target.begin(); it != target.end(); it++)
	{
		int index = *it - offset;
		source.erase(source.begin() + index);
		offset++;
	}
}
void RemoveLine(vector<Line>& source, vector<int> target)
{
	int offset = 0;
	for (vector<int>::iterator it = target.begin(); it != target.end(); it++)
	{
		int index = *it - offset;
		source.erase(source.begin() + index);
		offset++;
	}
}
void DrawCircle(Mat& img, vector<Circle> circles) {
	for(size_t i = 0; i < circles.size(); i++) {
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(img, center, 12, settings.centerColor, -1, 8, 0);
		circle(img, center, radius, settings.loopColor, 12, 8, 0);
	}
}
void DrawLine(Mat& img, vector<Line> lines) {
	for (size_t i = 0; i < lines.size(); i++) {
		Point p1 = Point(lines[i][0], lines[i][1]);
		Point p2 = Point(lines[i][2], lines[i][3]);
		line(img, p1, p2, settings.lineColor, 12, 8);
	}
}
void DrawAll() {
	img_finish = img_source.clone();
	DrawCircle(img_finish, { sDial,lDial });
	DrawLine(img_finish, { sIndicator,lIndicator });
}
void Settle() {
	Send(_P_MES_CalStart);
	double sAngle, lAngle;
	if (IsMoreThan180(zero_line, sIndicator))
		sAngle = 360 - (acos(CosineLaw(zero_line, sIndicator)) * 180 / CV_PI);
	else
		sAngle = acos(CosineLaw(zero_line, sIndicator)) * 180 / CV_PI;
	if (IsMoreThan180(zero_line, lIndicator))
		lAngle = 360 - (acos(CosineLaw(zero_line, lIndicator)) * 180 / CV_PI);
	else
		lAngle = acos(CosineLaw(zero_line, lIndicator)) * 180 / CV_PI;
	switch (settings.swType)
	{
	case SW504:
		result_min = floor(sAngle * 15 / 360);
		if (settings.estimate)
			result_sec = round(lAngle * 100 * 30 / 360) / 100 + fix;
		else
			result_sec = round(lAngle * 5 * 30 / 360) / 5 + fix;
		if ((int)floor(sAngle * 30 / 360) % 2 == 1)
			result_sec += 30;
		break;
	case SW505:
		if (settings.estimate)
			result_sec = round(lAngle * 100 * 60 / 360) / 100 + fix;
		else
			result_sec = round(lAngle * 5 * 60 / 360) / 5 + fix;
		result_min = floor(sAngle * 30 / 360);
		break;
	default:
		break;
	}
	Send(_P_MES_CalFinish);
}
void SendResult() {
	Send(_P_OUT_Min, to_string(result_min).c_str());
	Send(_P_OUT_Sec, to_string(result_sec).c_str());
}