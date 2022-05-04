#ifndef DIP_SETTINGS_H
#define DIP_SETTING_H

#include <opencv2/core.hpp>
//����ͼ���������ģʽ
enum DipMode {
	MANUAL = 0,  //�˹�
	AUTO = 1     //�Զ�
};
//����ͺ�
enum SWType {
	SW504 = 0,   //504
	SW505 = 1    //505
};
//ͼ���˲���ʽ
enum FilterMode {
	MEAN = 0,    //��ֵ�˲�
	MEDIAN = 1,  //��ֵ�˲�
	BILATERAL = 2//˫���˲�
};
//ͼ���ֵ����ʽ
enum BinarizeMode {
	CLASSIC = 0, //�ֶ�����
	OTSU = 1     //OTSU�㷨
};
//��Ե��ⷽʽ
enum EdgeMode {
	SOBEL = 0,   //Sobel����
	LAPLACE = 1, //Laplace����
	CANNY = 2    //Canny�㷨
};
//Sobel���Ӽ�ⷽ��
enum SobelDirection {
	X = 0,       //X
	Y = 1,       //Y
	XY = 2       //X+Y
};
//��������
struct DipSettings {
	SWType swType;//����ͺ�
	bool estimate;//�Ƿ����
	double fix;//����ֵ
	bool filter;//�Ƿ��˲�
	FilterMode filterMode;//�˲���ʽ
	BinarizeMode binarizeMode;//��ֵ����ʽ
	int binarizeThreshold;//��ֵ����ֵ
	bool thin;//�Ƿ�ϸ��
	int thinTimes;//ϸ����������
	bool open;//�Ƿ�����
	EdgeMode edgeMode;//��Ե��ⷽʽ
	double cannyThreshold1;//canny�㷨����ֵ
	double cannyThreshold2;//canny�㷨����ֵ
	SobelDirection sobelDirection;//Sobel���ӷ���
	double houghCircle_dp;//����Բ����ۼ����ֱ���
	double houghCircle_minDist;//����Բ�����СԲ�ľ���
	double houghCircle_param1;//����Բ����Ե���ĸ���ֵ
	double houghCircle_param2;//����Բ���Բ���ۼ�����ֵ
	double houghLine_rho;//����ֱ�߼���ۼ������طֱ���
	double houghLine_theta;//����ֱ�߼���ۼ����Ƕȷֱ���
	int houghLine_threshold;//����ֱ�߼���ۼ�����ֵ
	double houghLine_minLineLength;//����ֱ�߼����Сֱ�߳���
	double houghLine_maxLineGap;//����ֱ�߼�����ֱ�߼��
	cv::Scalar loopColor;//Բ��������ɫ
	cv::Scalar centerColor;//Բ�Ļ�����ɫ
	cv::Scalar lineColor;//ֱ�߻�����ɫ
};
/// <summary>
/// ��ʼ������
/// </summary>
/// <param name="ds">����</param>
void InitializeSettings(DipSettings& ds);

#endif // !SWI_SETTINGS_H