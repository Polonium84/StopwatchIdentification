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

//��ѧ���㲿��
#pragma region dip_math.cpp
/// <summary>
/// ��ֱ�ߵĳ���
/// </summary>
/// <param name="line">����ֱ��</param>
/// <returns>ֱ�߳���</returns>
double Length(Line line);
/// <summary>
/// ����������
/// </summary>
/// <param name="p1">��һ��</param>
/// <param name="p2">�ڶ���</param>
/// <returns>��������</returns>
double Length(Point p1, Point p2);
/// <summary>
/// ���������߼н�����ֵ
/// </summary>
/// <param name="p1">��һ�㣨���㣩</param>
/// <param name="p2">�ڶ���</param>
/// <param name="p3">������</param>
/// <returns>�������ֵ</returns>
double CosineLaw(Point p1, Point p2, Point p3);
/// <summary>
/// ���������н�����ֵ
/// </summary>
/// <param name="v1">����һ</param>
/// <param name="v2">������</param>
/// <returns>�������ֵ</returns>
double CosineLaw(Line v1, Line v2);
/// <summary>
/// ���е�
/// </summary>
/// <param name="p1">��һ��</param>
/// <param name="p2">�ڶ���</param>
/// <returns>�е�</returns>
Point Midpoint(Point p1, Point p2);
/// <summary>
/// ���е�
/// </summary>
/// <param name="line">�����߶�</param>
/// <returns>�е�</returns>
Point Midpoint(Line line);
/// <summary>
/// ��Բ����һ������������Բ�Ľ���
/// </summary>
/// <param name="p">Ŀ���</param>
/// <param name="center">Բ��</param>
/// <param name="radius">Բ�뾶</param>
/// <returns>����</returns>
Point IntersectionPoint(Point p, Point center, int radius);
/// <summary>
/// ��������˳ʱ��н��Ƿ����180��
/// </summary>
/// <param name="v1">����һ</param>
/// <param name="v2">������</param>
/// <returns>�Ƿ����180��</returns>
bool IsMoreThan180(Line v1, Line v2);
/// <summary>
/// ��ȡһ��Բ��Բ��
/// </summary>
/// <param name="circle">Ŀ��Բ</param>
/// <returns>Բ��</returns>
Point GetCenter(Circle circle);
/// <summary>
/// ��ȡ���������
/// </summary>
/// <param name="p1">��һ��</param>
/// <param name="p2">�ڶ���</param>
/// <returns>���������</returns>
Line ToLine(Point p1, Point p2);
#pragma endregion
//ϸ���㷨����
#pragma region dip_thin.cpp
/// <summary>
/// ͼ��ϸ��
/// </summary>
/// <param name="src">����ͼ��</param>
/// <param name="dst">���ͼ��</param>
/// <param name="intera">ϸ����������</param>
void Thin(Mat& src, Mat& dst, int intera);
#pragma endregion
//����̨�������
#pragma region console.cpp
/// <summary>
/// �����Ϣ
/// </summary>
/// <param name="text">����</param>
void Info(const char* text);
/// <summary>
/// �������
/// </summary>
/// <param name="text">����</param>
void Warn(const char* text);
/// <summary>
/// �������
/// </summary>
/// <param name="text">����</param>
void Error(const char* text);
/// <summary>
/// ���ʹ���
/// </summary>
/// <param name="code">����</param>
void Send(const char* code);
/// <summary>
/// ���ʹ��뼰����
/// </summary>
/// <param name="code">����</param>
/// <param name="content">����</param>
void Send(const char* code, const char* content);
/// <summary>
/// ��Ӧ����/��
/// </summary>
/// <param name="ans">��/��</param>
void Respond(bool ans);
#pragma endregion
//�����򲿷�
#pragma region SWI_DIP.cpp
/// <summary>
/// �ж��Ƿ�Ϊ��������ģʽ
/// </summary>
/// <param name="argc">���ݲ�������</param>
/// <param name="argv">���ݲ�������</param>
/// <returns>�Ƿ�Ϊ��������ģʽ</returns>
bool IsDependentMode(int argc, char** argv);
/// <summary>
/// �Զ���ģʽ����
/// </summary>
void RunIndependentMode();
/// <summary>
/// �Ը���ģʽ����
/// </summary>
void RunDependentMode();
/// <summary>
/// ��ȡ����
/// ��������ģʽʹ�ã�
/// </summary>
void GetSettings();
/// <summary>
/// ��ȡ����Ŀ¼�µ�ͼ��
/// </summary>
void ReadImage();
/// <summary>
/// ����ͼ��
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
/// <param name="filename">�ļ���</param>
void SaveImage(Mat img, const char* filename);
/// <summary>
/// ��ʾͼ��
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
/// <param name="name">������</param>
void ShowImage(Mat img, const char* name);
/// <summary>
/// ͼ��Ԥ����
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
void DIP_PreProcess(Mat& img);
/// <summary>
/// ��ֵ������
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
/// <param name="inv">�Ƿ���</param>
void DIP_Binarize(Mat& img, bool inv);
/// <summary>
/// ������
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
void DIP_Open(Mat& img);
/// <summary>
/// ͼ��ϸ��
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
void DIP_Thin(Mat& img);
/// <summary>
/// ��Ե���
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
void DIP_Edge(Mat& img);
/// <summary>
/// ����Բ���
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
/// <returns>����Բ</returns>
vector<Circle> DIP_HoughCircle(Mat img);
/// <summary>
/// ����ֱ�߼��
/// </summary>
/// <param name="img">Ŀ��ͼ��</param>
/// <returns>����ֱ��</returns>
vector<Line> DIP_HoughLine(Mat img);
/// <summary>
/// ɸѡԲ
/// </summary>
/// <param name="circles">����Բ��Ϣ������</param>
void FilterCircle(vector<Circle>& circles);
/// <summary>
/// ɸѡֱ��
/// </summary>
/// <param name="lines">����ֱ����Ϣ������</param>
void FilterLine(vector<Line>& lines);
/// <summary>
/// ɾ��Բ
/// </summary>
/// <param name="source">ԭ����</param>
/// <param name="target">��ɾ����Բ���</param>
void RemoveCircle(vector<Circle>& source, vector<int> target);
/// <summary>
/// ɾ��ֱ��
/// </summary>
/// <param name="source">ԭ����</param>
/// <param name="target">��ɾ����ֱ�����</param>
void RemoveLine(vector<Line>& source, vector<int> target);
/// <summary>
/// ����Բ
/// </summary>
/// <param name="img">ԭͼ��</param>
/// <param name="circles">�����Ƶ�Բ</param>
void DrawCircle(Mat& img, vector<Circle> circles);
/// <summary>
/// ����ֱ��
/// </summary>
/// <param name="img">ԭͼ��</param>
/// <param name="lines">�����Ƶ�ֱ��</param>
void DrawLine(Mat& img, vector<Line> lines);
/// <summary>
/// ���Ʊ��̺�ָ��
/// </summary>
void DrawAll();
/// <summary>
/// ������
/// </summary>
/// <param name="m">����ͼ��</param>
void DetectDial(Mat m);
/// <summary>
/// ���ָ��
/// </summary>
/// <param name="m">����ͼ��</param>
void DetectIndicator(Mat m);
/// <summary>
/// ����������
/// </summary>
void Settle();
/// <summary>
/// ���Ͷ������
/// </summary>
void SendResult();
#pragma endregion

#endif // !SWI_DIP_H