#ifndef SWI_DIP_Test_H
#define SWI_DIP_Test_H
#endif // !SWI_DIP_test_H

#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//SWI_DIP_Test.cpp
//主程序
void testimg(Mat m, const char* s);
Mat PreProcess(Mat m);
Mat Binarize(Mat m, bool inv);
Mat Thin(Mat m);
Mat Open(Mat m);
Mat Edge(Mat m);
void HoughCircle(Mat m);
void HoughLine(Mat m);
void DetectCircle(Mat m);
void DetectIndicator(Mat m);
vector<Vec3f> FiltrateCircle(vector<Vec3f> circles);
vector<Vec4i> FiltrateLine(vector<Vec4i> lines);
void RemoveCircle(vector<Vec3f>& source, vector<int> target);
void RemoveLine(vector<Vec4i>& source, vector<int> target);
void Settle(void);
typedef Vec4i Line;
typedef Vec3f Circle;

//Thin.cpp
//细化算法部分
void ThinSubiteration1(Mat& pSrc, Mat& pDst);
void ThinSubiteration2(Mat& pSrc, Mat& pDst);
void gThin(cv::Mat& src, cv::Mat& dst, int intera);

//Math.cpp
//数学计算部分
double Length(Vec4i line);
double Length(Point p1, Point p2);
double CosineLaw(Point p1, Point p2, Point p3);
double CosineLaw(Vec4i v1, Vec4i v2);
Point Midpoint(Point p1, Point p2);
Point Midpoint(Vec4i line);
Point IntersectionPoint(Point p, Point center, int radius);
bool IsMoreThan180(Vec4i v1, Vec4i v2);

enum SWType {
	SW504 = 1,
	SW505 = 2
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
	operator Vec4i() {
		return{ p1.x,p1.y,p2.x,p2.y };
	}
};
