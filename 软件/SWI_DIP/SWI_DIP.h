#ifndef SWI_DIP_H
#define SWI_DIP_H
#endif // !SWI_DIP_H

#include <iostream>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <regex>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

typedef Vec4i Line;
typedef Vec3f Circle;

//数学运算部分
#pragma region dip_math.cpp
double Length(Line line);
double Length(Point p1, Point p2);
double CosineLaw(Point p1, Point p2, Point p3);
double CosineLaw(Line v1, Line v2);
Point Midpoint(Point p1, Point p2);
Point Midpoint(Line line);
Point IntersectionPoint(Point p, Point center, int radius);
bool IsMoreThan180(Line v1, Line v2);
#pragma endregion
//细化算法部分
#pragma region dip_thin.cpp
void Thin(Mat& src, Mat& dst, int intera);
#pragma endregion
//异常处理部分
#pragma region dip_exception.cpp

#pragma endregion
//主程序部分
#pragma region SWI_DIP.cpp
bool AutoMode(int argc, char** argv);
#pragma endregion
