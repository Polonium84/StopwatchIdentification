#include "SWI_DIP_Test.h"

String IMGPATH = "F:\\毕业设计\\图片素材\\source.jpg";
Mat originImg;
Mat img_preProcess;
Mat img_binary;
Mat img_edge;
Mat img_circle;
Mat img_line;
Dial sDial, lDial;
Indicator sIndicator, lIndicator;

int main()
{
    originImg = imread(IMGPATH);
    Mat m = originImg;
    img_preProcess = PreProcess(originImg);
    DetectCircle(img_preProcess);
    DetectIndicator(img_preProcess);
    //testimg(m, "Thin1");
    //m = Open(m);
    //testimg(m, "Edge_Thin");
    //return 0;
    testimg(img_line, "HoughLine_New");
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
    FiltrateCircle(circles);//筛选
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle(out, center, 10, Scalar(0, 255, 0), -1, 8, 0);
        // draw the circle outline
        circle(out, center, radius, Scalar(0, 0, 255), 10, 8, 0);
    }
    img_circle = out;
    cout << "Hough Circle Succeed" << endl;
}
void FiltrateCircle(vector<Vec3f>& circles)
{
    if (circles.size() == 2)//刚好有2个圆时无需筛选
        return;
    else if (circles.size() < 2)
    {
        cerr << "Too few circles";//少于2个圆时，识别出错
        return;
    }
    //多于2个圆时，进行筛选
    int circles_to_remove[100];
}
void HoughLine(Mat m)
{
    Mat out = img_circle;
    vector<Vec4i> lines;
    HoughLinesP(m, lines, 1, CV_PI / 180, 100, 50, 10);
    FiltrateLine(lines);//筛选
    for (size_t i = 0; i < lines.size(); i++)
    {
        line(out, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(255, 0, 0), 10, 8);
    }
    img_line = out;
    cout << "Hough Line Succeed" << endl;
}
void FiltrateLine(vector<Vec4i>& lines)
{
    int lines_to_remove[100];

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
        tm->tm_year + 1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, s
    );
    String savePath = name;
    if (int key = waitKey(10000) == 's') {
        if (imwrite(savePath, m))
            std::cout << "Saved!" << std::endl;
        std::cout << savePath;
    }
}

