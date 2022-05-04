#ifndef DIP_SETTINGS_H
#define DIP_SETTING_H

#include <opencv2/core.hpp>
//数字图像处理程序工作模式
enum DipMode {
	MANUAL = 0,  //人工
	AUTO = 1     //自动
};
//秒表型号
enum SWType {
	SW504 = 0,   //504
	SW505 = 1    //505
};
//图像滤波方式
enum FilterMode {
	MEAN = 0,    //均值滤波
	MEDIAN = 1,  //中值滤波
	BILATERAL = 2//双边滤波
};
//图像二值化方式
enum BinarizeMode {
	CLASSIC = 0, //手动设置
	OTSU = 1     //OTSU算法
};
//边缘检测方式
enum EdgeMode {
	SOBEL = 0,   //Sobel算子
	LAPLACE = 1, //Laplace算子
	CANNY = 2    //Canny算法
};
//Sobel算子检测方向
enum SobelDirection {
	X = 0,       //X
	Y = 1,       //Y
	XY = 2       //X+Y
};
//总体设置
struct DipSettings {
	SWType swType;//秒表型号
	bool estimate;//是否估读
	double fix;//修正值
	bool filter;//是否滤波
	FilterMode filterMode;//滤波方式
	BinarizeMode binarizeMode;//二值化方式
	int binarizeThreshold;//二值化阈值
	bool thin;//是否细化
	int thinTimes;//细化迭代次数
	bool open;//是否开运算
	EdgeMode edgeMode;//边缘检测方式
	double cannyThreshold1;//canny算法低阈值
	double cannyThreshold2;//canny算法高阈值
	SobelDirection sobelDirection;//Sobel算子方向
	double houghCircle_dp;//霍夫圆检测累加器分辨率
	double houghCircle_minDist;//霍夫圆检测最小圆心距离
	double houghCircle_param1;//霍夫圆检测边缘检测的高阈值
	double houghCircle_param2;//霍夫圆检测圆心累加器阈值
	double houghLine_rho;//霍夫直线检测累加器像素分辨率
	double houghLine_theta;//霍夫直线检测累加器角度分辨率
	int houghLine_threshold;//霍夫直线检测累加器阈值
	double houghLine_minLineLength;//霍夫直线检测最小直线长度
	double houghLine_maxLineGap;//霍夫直线检测最大直线间隔
	cv::Scalar loopColor;//圆环绘制颜色
	cv::Scalar centerColor;//圆心绘制颜色
	cv::Scalar lineColor;//直线绘制颜色
};
/// <summary>
/// 初始化设置
/// </summary>
/// <param name="ds">设置</param>
void InitializeSettings(DipSettings& ds);

#endif // !SWI_SETTINGS_H