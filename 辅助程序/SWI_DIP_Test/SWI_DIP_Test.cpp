#include <iostream>
#include <ctime>
#include <string>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void testimg(Mat, const char*);
Mat PreProcess(Mat);
Mat Binarize(Mat);
Mat Open(Mat);
Mat Edge(Mat);
void HoughCircle(Mat);
void HoughLine(Mat);

String IMGPATH = "F:\\毕业设计\\图片素材\\source.jpg";
Mat originImg;
Mat img_circle;
Mat img_line;

int main()
{
    originImg = imread(IMGPATH);
    Mat m = originImg;
    //testimg(m, "test");
    m = PreProcess(m);
    m = Binarize(m);
    m = Open(m);
    //testimg(m, "Open");
    //return 0;
    m = Edge(m);
    HoughCircle(m);
    HoughLine(m);
    testimg(img_line, "HoughLine");
    return 0;
}
Mat PreProcess(Mat m)
{
    Mat out;
    //blur(m, out, Size(9, 9));
    bilateralFilter(m, out, 9, 75, 75);//双边带滤波，可保留边缘
    cout << "PreProcess Succeed" << endl;
    return out;
}
Mat Binarize(Mat m)
{
    Mat out;
    Mat gray;
    cvtColor(m, gray, ColorConversionCodes::COLOR_BGR2GRAY);
    threshold(gray, out, 0, 255, ThresholdTypes::THRESH_OTSU);
    //threshold(gray, out, 127, 255, ThresholdTypes::THRESH_BINARY);
    cout << "Binarize Succeed" << endl;
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
void HoughLine(Mat m)
{
    Mat out = img_circle;
    vector<Vec4i> lines;
    HoughLinesP(m, lines, 1, CV_PI / 180, 80, 50, 5);
    for (size_t i = 0; i < lines.size(); i++)
    {
        line(out, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(255, 0, 0), 10, 8);
    }
    img_line = out;
    cout << "Hough Line Succeed" << endl;
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

