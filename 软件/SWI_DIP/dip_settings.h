#ifndef DIP_SETTINGS_H
#define DIP_SETTING_H
#endif // !SWI_SETTINGS_H

#include <opencv2/core.hpp>

enum DipMode {
	MANUAL = 0,
	AUTO = 1
};
enum SWType {
	SW504 = 0,
	SW505 = 1
};
enum FilterMode {
	MEAN = 0,
	MEDIAN = 1,
	BILATERAL = 2
};
enum BinarizeMode {
	CLASSIC = 0,
	OTSU = 1
};
enum EdgeMode {
	SOBEL = 0,
	LAPLACE = 1,
	CANNY = 2
};
enum SobelDirection {
	X = 0,
	Y = 1,
	XY = 2
};
struct DipSettings {
	DipMode dipMode;
	SWType swType;
	bool filter;
	FilterMode filterMode;
	BinarizeMode binarizeMode;
	int binarizeThreshold;
	bool thin;
	int thinTimes;
	bool open;
	EdgeMode edgeMode;
	double cannyThreshold1;
	double cannyThreshold2;
	SobelDirection sobelDirection;
	double houghCircle_dp;
	double houghCircle_minDist;
	double houghCircle_param1;
	double houghCircle_param2;
	double houghLine_rho;
	double houghLine_theta;
	int houghLine_threshold;
	double houghLine_minLineLength;
	double houghLine_maxLineGap;
	cv::Scalar loopColor;
	cv::Scalar centerColor;
	cv::Scalar lineColor;
};
void InitializeSettings(DipSettings& ds);
