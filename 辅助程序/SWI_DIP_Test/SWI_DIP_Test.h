#ifndef SWI_DIP_Test_H
#define SWI_DIP_Test_H
#endif // !SWI_DIP_test_H

#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//SWI_DIP_Test.cpp
//主程序
void testimg(Mat m, const char* s);
Mat PreProcess(Mat m);
Mat Binarize(Mat m,bool inv);
Mat Thin(Mat m);
Mat Open(Mat m);
Mat Edge(Mat m);
void HoughCircle(Mat m);
void HoughLine(Mat m);
void DetectCircle(Mat m);
void DetectIndicator(Mat m);
void FiltrateCircle(vector<Vec3f>& circles);
void FiltrateLine(vector<Vec4i>& lines);

//Thin.cpp
//细化算法部分
void ThinSubiteration1(Mat& pSrc, Mat& pDst);
void ThinSubiteration2(Mat& pSrc, Mat& pDst);
void gThin(cv::Mat& src, cv::Mat& dst, int intera);

//Math.cpp
//数学计算部分
double Length(Vec4i line);
double Length(Point p1, Point p2);

enum DialType {
	Small = 1,
	Large = 2
};

struct Dial
{
	//DialType dialType;
	Point center;
	int radius;
};

struct Indicator
{
	//DialType dialType;
	Point p1;
	Point p2;
};

