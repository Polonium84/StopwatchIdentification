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
/// <summary>
/// 求直线的长度
/// </summary>
/// <param name="line">待求直线</param>
/// <returns>直线长度</returns>
double Length(Line line);
/// <summary>
/// 求两点间距离
/// </summary>
/// <param name="p1">第一点</param>
/// <param name="p2">第二点</param>
/// <returns>两点间距离</returns>
double Length(Point p1, Point p2);
/// <summary>
/// 求三点连线夹角余弦值
/// </summary>
/// <param name="p1">第一点（顶点）</param>
/// <param name="p2">第二点</param>
/// <param name="p3">第三点</param>
/// <returns>求得余弦值</returns>
double CosineLaw(Point p1, Point p2, Point p3);
/// <summary>
/// 求两向量夹角余弦值
/// </summary>
/// <param name="v1">向量一</param>
/// <param name="v2">向量二</param>
/// <returns>求得余弦值</returns>
double CosineLaw(Line v1, Line v2);
/// <summary>
/// 求中点
/// </summary>
/// <param name="p1">第一点</param>
/// <param name="p2">第二点</param>
/// <returns>中点</returns>
Point Midpoint(Point p1, Point p2);
/// <summary>
/// 求中点
/// </summary>
/// <param name="line">输入线段</param>
/// <returns>中点</returns>
Point Midpoint(Line line);
/// <summary>
/// 求圆心与一点所在射线与圆的交点
/// </summary>
/// <param name="p">目标点</param>
/// <param name="center">圆心</param>
/// <param name="radius">圆半径</param>
/// <returns>交点</returns>
Point IntersectionPoint(Point p, Point center, int radius);
/// <summary>
/// 求两向量顺时针夹角是否大于180度
/// </summary>
/// <param name="v1">向量一</param>
/// <param name="v2">向量二</param>
/// <returns>是否大于180度</returns>
bool IsMoreThan180(Line v1, Line v2);
/// <summary>
/// 获取一个圆的圆心
/// </summary>
/// <param name="circle">目标圆</param>
/// <returns>圆心</returns>
Point GetCenter(Circle circle);
/// <summary>
/// 获取两点的连线
/// </summary>
/// <param name="p1">第一点</param>
/// <param name="p2">第二点</param>
/// <returns>两点间连线</returns>
Line ToLine(Point p1, Point p2);
#pragma endregion
//细化算法部分
#pragma region dip_thin.cpp
/// <summary>
/// 图像细化
/// </summary>
/// <param name="src">输入图像</param>
/// <param name="dst">输出图像</param>
/// <param name="intera">细化迭代次数</param>
void Thin(Mat& src, Mat& dst, int intera);
#pragma endregion
//控制台输出部分
#pragma region console.cpp
/// <summary>
/// 输出信息
/// </summary>
/// <param name="text">内容</param>
void Info(const char* text);
/// <summary>
/// 输出警告
/// </summary>
/// <param name="text">内容</param>
void Warn(const char* text);
/// <summary>
/// 输出错误
/// </summary>
/// <param name="text">内容</param>
void Error(const char* text);
/// <summary>
/// 发送代码
/// </summary>
/// <param name="code">代码</param>
void Send(const char* code);
/// <summary>
/// 发送代码及数据
/// </summary>
/// <param name="code">代码</param>
/// <param name="content">内容</param>
void Send(const char* code, const char* content);
/// <summary>
/// 响应（是/否）
/// </summary>
/// <param name="ans">是/否</param>
void Respond(bool ans);
#pragma endregion
//主程序部分
#pragma region SWI_DIP.cpp
/// <summary>
/// 判断是否为附属运行模式
/// </summary>
/// <param name="argc">传递参数数量</param>
/// <param name="argv">传递参数内容</param>
/// <returns>是否为附属运行模式</returns>
bool IsDependentMode(int argc, char** argv);
/// <summary>
/// 以独立模式运行
/// </summary>
void RunIndependentMode();
/// <summary>
/// 以附属模式运行
/// </summary>
void RunDependentMode();
/// <summary>
/// 获取设置
/// （仅附属模式使用）
/// </summary>
void GetSettings();
/// <summary>
/// 读取工作目录下的图像
/// </summary>
void ReadImage();
/// <summary>
/// 保存图像
/// </summary>
/// <param name="img">目标图像</param>
/// <param name="filename">文件名</param>
void SaveImage(Mat img, const char* filename);
/// <summary>
/// 显示图像
/// </summary>
/// <param name="img">目标图像</param>
/// <param name="name">窗口名</param>
void ShowImage(Mat img, const char* name);
/// <summary>
/// 图像预处理
/// </summary>
/// <param name="img">目标图像</param>
void DIP_PreProcess(Mat& img);
/// <summary>
/// 二值化处理
/// </summary>
/// <param name="img">目标图像</param>
/// <param name="inv">是否反相</param>
void DIP_Binarize(Mat& img, bool inv);
/// <summary>
/// 开运算
/// </summary>
/// <param name="img">目标图像</param>
void DIP_Open(Mat& img);
/// <summary>
/// 图像细化
/// </summary>
/// <param name="img">目标图像</param>
void DIP_Thin(Mat& img);
/// <summary>
/// 边缘检测
/// </summary>
/// <param name="img">目标图像</param>
void DIP_Edge(Mat& img);
/// <summary>
/// 霍夫圆检测
/// </summary>
/// <param name="img">目标图像</param>
/// <returns>所得圆</returns>
vector<Circle> DIP_HoughCircle(Mat img);
/// <summary>
/// 霍夫直线检测
/// </summary>
/// <param name="img">目标图像</param>
/// <returns>所得直线</returns>
vector<Line> DIP_HoughLine(Mat img);
/// <summary>
/// 筛选圆
/// </summary>
/// <param name="circles">存有圆信息的容器</param>
void FilterCircle(vector<Circle>& circles);
/// <summary>
/// 筛选直线
/// </summary>
/// <param name="lines">存有直线信息的容器</param>
void FilterLine(vector<Line>& lines);
/// <summary>
/// 删除圆
/// </summary>
/// <param name="source">原容器</param>
/// <param name="target">待删除的圆序号</param>
void RemoveCircle(vector<Circle>& source, vector<int> target);
/// <summary>
/// 删除直线
/// </summary>
/// <param name="source">原容器</param>
/// <param name="target">待删除的直线序号</param>
void RemoveLine(vector<Line>& source, vector<int> target);
/// <summary>
/// 绘制圆
/// </summary>
/// <param name="img">原图像</param>
/// <param name="circles">待绘制的圆</param>
void DrawCircle(Mat& img, vector<Circle> circles);
/// <summary>
/// 绘制直线
/// </summary>
/// <param name="img">原图像</param>
/// <param name="lines">待绘制的直线</param>
void DrawLine(Mat& img, vector<Line> lines);
/// <summary>
/// 绘制表盘和指针
/// </summary>
void DrawAll();
/// <summary>
/// 检测表盘
/// </summary>
/// <param name="m">输入图像</param>
void DetectDial(Mat m);
/// <summary>
/// 检测指针
/// </summary>
/// <param name="m">输入图像</param>
void DetectIndicator(Mat m);
/// <summary>
/// 计算读数结果
/// </summary>
void Settle();
/// <summary>
/// 发送读数结果
/// </summary>
void SendResult();
#pragma endregion

#endif // !SWI_DIP_H