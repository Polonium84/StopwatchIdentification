#include <iostream>
#include <ctime>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void testimg(Mat, const char*);
Mat PreProcess(Mat);
Mat Binarize(Mat);
Mat Edge(Mat);
Mat HoughCircle(Mat);

String IMGPATH = "F:\\毕业设计\\图片素材\\source.jpg";
Mat originImg;

int main()
{
    originImg = imread(IMGPATH);
    Mat m = originImg;
    //testimg(m, "test");
    m = PreProcess(m);
    m = Binarize(m);
    m = Edge(m);
    m = HoughCircle(m);
    testimg(m, "HoughCircle");
    return 0;
}
Mat PreProcess(Mat m) 
{
    Mat out;
    blur(m, out, Size(9,9));
    bilateralFilter(m, out, 9, 75, 75);//双边带滤波，可保留边缘
    return out;
}
Mat Binarize(Mat m)
{
    Mat out;
    Mat gray;
    cvtColor(m, gray, ColorConversionCodes::COLOR_BGR2GRAY);
    threshold(gray, out, 0, 255, ThresholdTypes::THRESH_OTSU);
    //threshold(gray, out, 127, 255, ThresholdTypes::THRESH_BINARY);
    return out;
}
Mat Edge(Mat m)
{
    Mat out;
    //Sobel(m, out, CV_8U, 1, 1);
    Laplacian(m, out, CV_8U);
    //Canny(m, out, 5, 20);
    return out;
}
Mat HoughCircle(Mat m)
{
    Mat out = originImg;
    vector<Vec3f> circles;
    HoughCircles(m, circles, HoughModes::HOUGH_GRADIENT, 1, 200,100.0,200.0);
    for (size_t i = 0; i < circles.size(); i++)
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        // draw the circle center
        circle(out, center, 10, Scalar(0, 255, 0), -1, 8, 0);
        // draw the circle outline
        circle(out, center, radius, Scalar(0, 0, 255), 10, 8, 0);
    }
    return out;
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
        "%d-%d-%d-%d-%d-%d-%s.jpg",
        tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, s
    );
    String savePath = name;
    if (int key = waitKey(10000) == 's') {
        if (imwrite(savePath, m))
            std::cout << "Saved!" << std::endl;
        std::cout << savePath;
    }
}

