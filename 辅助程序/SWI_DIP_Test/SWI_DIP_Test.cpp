#include "SWI_DIP_Test.h"
#pragma region GLOBAL
String IMGPATH = "F:\\毕业设计\\图片素材\\source.jpg";
Mat originImg;
Mat img_preProcess;
Mat img_binary;
Mat img_edge;
Mat img_circle;
Mat img_line;
Dial sDial, lDial;
Indicator sIndicator, lIndicator;
int img_width, img_height;
#pragma endregion
int main()
{
    originImg = imread(IMGPATH);
    img_width = originImg.cols;
    img_height = originImg.rows;
    Mat m = originImg;
    img_preProcess = PreProcess(originImg);
    cout << img_width << endl;
    cout << img_height << endl;
    DetectCircle(img_preProcess);
    DetectIndicator(img_preProcess);
    testimg(img_line, "FiltrateLine");
    return 0;
}
void DetectCircle(Mat m) 
{
    cout << "***Beginning detect circle..." << endl;
    m = Binarize(m, false);
    m = Edge(m);
    HoughCircle(m);
    cout << "***Detect circle completed." << endl;
}
void DetectIndicator(Mat m)
{
    cout << "***Beginning detect indicator..." << endl;
    m = Binarize(m, true);
    m = Thin(m);
    m = Edge(m);
    HoughLine(m);
    cout << "***Detect indicator completed." << endl;
}
Mat PreProcess(Mat m)
{
    Mat out;
    //blur(m, out, Size(9, 9));
    bilateralFilter(m, out, 9, 75, 75);//双边带滤波，可保留边缘
    cout << "PreProcess Succeed" << endl;
    return out;
}
Mat Binarize(Mat m,bool inv)
{
    Mat out;
    Mat gray;
    cvtColor(m, gray, ColorConversionCodes::COLOR_BGR2GRAY);
    if(inv)
        threshold(gray, out, 0, 255, ThresholdTypes::THRESH_OTSU + ThresholdTypes::THRESH_BINARY_INV);
    else
        threshold(gray, out, 0, 255, ThresholdTypes::THRESH_OTSU);
    //threshold(gray, out, 127, 255, ThresholdTypes::THRESH_BINARY);
    cout << "Binarize Succeed" << endl;
    return out;
}
Mat Thin(Mat m)
{
    Mat out;
    gThin(m, out, 12);
    cout << "Thin Succeed" << endl;
    return out;
}
Mat Open(Mat m)
{
    Mat out;
    Mat element = getStructuringElement(MorphShapes::MORPH_RECT, Size(5, 5));
    morphologyEx(m, out, MorphTypes::MORPH_OPEN, element);
    cout << "Open Succeed" << endl;
    return out;
}
Mat Edge(Mat m)
{
    Mat out;
    //Sobel(m, out, CV_8U, 1, 1);
    Laplacian(m, out, CV_8U);
    //Canny(m, out, 5, 20);
    cout << "Edge Detection Succeed" << endl;
    return out;
}
void HoughCircle(Mat m)
{
    Mat out = originImg;
    vector<Vec3f> circles;
    HoughCircles(m, circles, HoughModes::HOUGH_GRADIENT, 1, 200, 100.0, 200.0);
    vector<Vec3f> dials = FiltrateCircle(circles);//筛选
    cout << "绘制圆个数：" << dials.size() << endl;
    for (size_t i = 0; i < dials.size(); i++)
    {
        Point center(cvRound(dials[i][0]), cvRound(dials[i][1]));
        int radius = cvRound(dials[i][2]);
        circle(out, center, 10, Scalar(0, 255, 0), -1, 8, 0);
        circle(out, center, radius, Scalar(0, 0, 255), 10, 8, 0);
    }
    if (dials.size() == 2)
    {
        int t1, t2;
        if (dials[0][2] > dials[1][2])//0为大表盘
            t1 = 0, t2 = 1;
        else//1为大表盘
            t1 = 1, t2 = 0;
        lDial.center = Point(dials[t1][0], dials[t1][1]);
        lDial.radius = dials[t1][2];
        sDial.center = Point(dials[t2][0], dials[t2][1]);
        sDial.radius = dials[t2][2];
    }
    else
        cerr << "圆检测出错，共检测到" << dials.size() << "个圆" << endl;
    img_circle = out;
    cout << "Hough Circle Succeed" << endl;
}
vector<Vec3f> FiltrateCircle(vector<Vec3f> circles)
{
    if (circles.size() == 2)//刚好有2个圆时无需筛选
        return circles;
    else if (circles.size() < 2)
    {
        cerr << "Too few circles";//少于2个圆时，识别出错
        return circles;
    }
    cout << "检测圆个数：" << circles.size() << endl;
    //多于2个圆时，进行筛选
    vector<int> circles_to_remove;
    for (size_t i = 0; i < circles.size(); i++)
    {
        float x = circles[i][0];//圆心横坐标
        float y = circles[i][1];//圆心纵坐标
        int r = circles[i][2];//半径
        printf_s("-----(%.0f,%.0f) %d\n", x, y, r);
        if (x + r > img_width || x - r < 0 || y + r > img_height || y - r < 0)//判断圆是否完整
        {
            circles_to_remove.push_back(i);
            printf_s("-----剔除\n");
        }
    }
    RemoveCircle(circles, circles_to_remove);
    return circles;
}
void RemoveCircle(vector<Vec3f>& source, vector<int> target)
{
    cout << "剔除圆个数:" << target.size() << endl;
    int offset = 0;
    for (vector<int>::iterator it = target.begin(); it != target.end(); it++)
    {
        int index = *it - offset;
        source.erase(source.begin() + index);
        offset++;
    }
}
void HoughLine(Mat m)
{
    Mat out = img_circle;
    vector<Vec4i> lines;
    HoughLinesP(m, lines, 1, CV_PI / 180, 100, 50, 10);
    vector<Vec4i> indicators = FiltrateLine(lines);//筛选
    for (size_t i = 0; i < indicators.size(); i++)
    {
        line(out, Point(indicators[i][0], indicators[i][1]),
            Point(indicators[i][2], indicators[i][3]), Scalar(255, 0, 0), 10, 8);
    }
    img_line = out;
    cout << "Hough Line Succeed" << endl;
}
vector<Vec4i> FiltrateLine(vector<Vec4i> lines)
{
    vector<int> lines_to_remove;
    if (lines.size() == 2)//刚好有2个指针时无需筛选
        return lines;
    else if (lines.size() < 2)
    {
        cerr << "Too few lines";//少于2个指针时，识别出错
        return lines;
    }
    cout << "检测直线个数：" << lines.size() << endl;
    for (size_t i = 0; i < lines.size(); i++)
    {
        if (Length(Midpoint(Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3])), 
            lDial.center) > lDial.radius)//判断直线是否在表盘外
        {
            printf("直线{(%d,%d)-(%d,%d)}在表盘外\n", lines[i][0], lines[i][1], lines[i][2], lines[i][3]);
            lines_to_remove.push_back(i);
        }
    }
    RemoveLine(lines, lines_to_remove);
    lines_to_remove.clear();
    auto angel = [](double cos)->double {return acos(abs(cos)) * 180 / CV_PI; };
    double threshold_angel = 10;//夹角阈值
    auto lengthDiffRatio = [](double l, double r)->double {return abs(l - r) / r; };
    double threshold_ratio = 0.7;//相对长度差阈值
    for (size_t i = 0; i < lines.size(); i++)
    {
        Point begin = Point(lines[i][0], lines[i][1]);
        Point end = Point(lines[i][2], lines[i][3]);
        if (angel(CosineLaw(sDial.center, begin, end)) > threshold_angel &&
            angel(CosineLaw(lDial.center, begin, end)) > threshold_angel)//判断三点是否基本成一条直线
        {
            printf("直线{(%d,%d)-(%d,%d)}，小表盘夹角%.2f度",
                begin.x, begin.y, end.x, end.y, angel(CosineLaw(sDial.center, begin, end)));
            printf(";大表盘夹角%.2f度\n",angel(CosineLaw(lDial.center, begin, end)));
            lines_to_remove.push_back(i);
        }
        else if (lengthDiffRatio(Length(lines[i]), sDial.radius) > threshold_ratio &&
            lengthDiffRatio(Length(lines[i]), lDial.radius) > threshold_ratio)//判断长度是否接近半径
        {
            printf("直线{(%d,%d)-(%d,%d)}，小表盘半径性相对差%.2f%%",
                begin.x, begin.y, end.x, end.y, lengthDiffRatio(Length(lines[i]), sDial.radius * 100));
            printf(";大表盘半径相对差%.2f%%\n", lengthDiffRatio(Length(lines[i]), lDial.radius * 100));
            lines_to_remove.push_back(i);
        }
    }
    RemoveLine(lines, lines_to_remove);
    return lines;
}
void RemoveLine(vector<Vec4i>& source, vector<int> target)
{
    cout << "剔除直线个数：" << target.size() << endl;
    int offset = 0;
    for (vector<int>::iterator it = target.begin(); it != target.end(); it++)
    {
        int index = *it - offset;
        source.erase(source.begin() + index);
        offset++;
    }
}
void testimg(Mat m, const char* s)
{
    namedWindow("test", 0);
    resizeWindow("test", 570, 480);
    imshow("test", m);
    time_t t = time(0);
    tm* tm = localtime(&t);
    char name[1024];
    sprintf_s(
        name,
        sizeof(name),
        "./output/%d-%d-%d-%d-%d-%d-%s.jpg",
        tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, s
    );
    String savePath = name;
    if (int key = waitKey(10000) == 's') {
        if (imwrite(savePath, m))
            std::cout << "Saved!" << std::endl;
        std::cout << savePath;
    }
}

