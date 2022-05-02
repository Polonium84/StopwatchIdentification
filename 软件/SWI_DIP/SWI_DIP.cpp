#include "SWI_DIP.h"
#include "dip_settings.h"
#include "swi_protocol.hpp"

#pragma region GLOBAL
DipSettings settings;
string workDir;
Mat img;
Mat img_source;
Mat img_preProcess;
Mat img_dial;
Mat img_indicator;
Circle sDial, lDial;
Line sIndicator, lIndicator;
int width, height;
#pragma endregion

int main(int argc, char** argv) {
	InitializeSettings(settings);
	/*
	if (IsDependentMode(argc, argv))
		RunDependentMode();
	else
		RunIndependentMode();
	*/
	RunDependentMode();
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
	DIP_Binarize(img, true);
	DIP_Open(img);
	DIP_Thin(img);
	DIP_Edge(img);
	//

}
void GetSettings() {
	string type;
	int estimate;
	Send(_P_SET_WorkDir);//设置工作路径
	cin >> workDir;
	Send(_P_SET_SWSType);//设置秒表型号
	cin >> type;
	if (type == "504")
		settings.swType = SW504;
	else if (type == "505")
		settings.swType = SW505;
	Send(_P_SET_Estimate);//设置是否估读
	cin >> estimate;
	if (estimate)
		settings.estimate = true;
	else
		settings.estimate = false;
	Send(_P_SET_FixValue);//设置修正值
	cin >> settings.fix;
	//printf_s("%s,%d,%d,%f", workDir.c_str(), settings.swType, settings.estimate, settings.fix);
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
	Mat img_circles = DrawCircle(img_source, circles);
	SaveImage(img_circles, "circles");
	FilterCircle(circles);
	Mat img_dials = DrawCircle(img_source, circles);
	SaveImage(img_dials, "dials");
	Send(_P_MES_DialFinish);
}
vector<Circle> DIP_HoughCircle(Mat img) {

}
void FilterCircle(vector<Circle>& circles) {

}
Mat DrawCircle(Mat img, vector<Circle> circles) {

}