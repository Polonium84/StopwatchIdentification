#ifndef SWI_DIP_H
#define SWI_DIP_H

#include <iostream>
#include <ctime>
#include <cstring>
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
//控制台输出部分
#pragma region console.cpp
void Info(const char* text);
void Warn(const char* text);
void Error(const char* text);
void Send(const char* code);
void Send(const char* code, const char* content);
void Respond(bool ans);
#pragma endregion
//异常处理部分
#pragma region dip_exception.cpp

#pragma endregion
//主程序部分
#pragma region SWI_DIP.cpp
bool IsDependentMode(int argc, char** argv);
void RunIndependentMode();
void RunDependentMode();
void GetSettings();
void ReadImage();
void SaveImage(Mat img, const char* filename);
void ShowImage(Mat img, const char* name);
void DIP_PreProcess(Mat& img);
void DIP_Binarize(Mat& img, bool inv);
void DIP_Open(Mat& img);
void DIP_Thin(Mat& img);
void DIP_Edge(Mat& img);
vector<Circle> DIP_HoughCircle(Mat img);
vector<Line> DIP_HoughLine(Mat img);
void FilterCircle(vector<Circle>& circles);
void FilterLine(vector<Line>& lines);
Mat DrawCircle(Mat img, vector<Circle> circles);
Mat DrawLine(Mat img, vector<Line> lines);
void DetectDial(Mat m);
void DetectIndicator(Mat m);
#pragma endregion

#endif // !SWI_DIP_H