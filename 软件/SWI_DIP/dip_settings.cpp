#include "dip_settings.h"

void InitializeSettings(DipSettings& ds) {
	ds.swType = SW505;
	ds.estimate = true;
	ds.fix = 0.0;
	ds.filter = true;
	ds.filterMode = BILATERAL;
	ds.binarizeMode = OTSU;
	ds.binarizeThreshold = 127;
	ds.thin = true;
	ds.thinTimes = 12;
	ds.open = false;
	ds.edgeMode = LAPLACE;
	ds.cannyThreshold1 = 5;
	ds.cannyThreshold2 = 20;
	ds.sobelDirection = XY;
	ds.houghCircle_dp = 1;
	ds.houghCircle_minDist = 200;
	ds.houghCircle_param1 = 100.0;
	ds.houghCircle_param2 = 120.0;
	ds.houghLine_rho = 1;
	ds.houghLine_theta = CV_PI / 180;
	ds.houghLine_threshold = 100;
	ds.houghLine_minLineLength = 50;
	ds.houghLine_maxLineGap = 20;
	ds.loopColor = cv::Scalar(255, 0, 255);
	ds.centerColor = cv::Scalar(0, 0, 255);
	ds.lineColor = cv::Scalar(0, 255, 0);
}