#ifndef SWI_PROTOCOL_HPP
#define SWI_PROTOCOL_HPP
//设置代码
constexpr auto _P_SET_WorkDir = "SET01";
constexpr auto _P_SET_SWSType = "SET02";
constexpr auto _P_SET_Filter = "SET03";
constexpr auto _P_SET_FilterMode = "SET03A";
constexpr auto _P_SET_BinarizeMode = "SET04";
constexpr auto _P_SET_BinThreshold = "SET04A";
constexpr auto _P_SET_Thin = "SET05";
constexpr auto _P_SET_ThinTimes = "SET05A";
constexpr auto _P_SET_Open = "SET06";
constexpr auto _P_SET_EdgeMode = "SET07";
constexpr auto _P_SET_SobelDirection = "SET07A";
constexpr auto _P_SET_CannyThre1 = "SET07B";
constexpr auto _P_SET_CannyThre2 = "SET07C";
constexpr auto _P_SET_hcDp = "SET08A";
constexpr auto _P_SET_hcMinDist = "SET08B";
constexpr auto _P_SET_hcParam1 = "SET08C";
constexpr auto _P_SET_hcParam2 = "SET08D";
constexpr auto _P_SET_hlRho = "SET09A";
constexpr auto _P_SET_hlTheta = "SET09B";
constexpr auto _P_SET_hlThreshold = "SET09C";
constexpr auto _P_SET_hlMinLength = "SET09D";
constexpr auto _P_SET_hlMaxGap = "SET09E";
constexpr auto _P_SET_LoopColor = "SET10";
constexpr auto _P_SET_CenterColor = "SET11";
constexpr auto _P_SET_IndColor = "SET12";
constexpr auto _P_SET_Estimate = "SET13";
constexpr auto _P_SET_FixValue = "SET14";
//消息代码
constexpr auto _P_MES_IniStart = "MES01A";
constexpr auto _P_MES_IniFinish = "MES01B";
constexpr auto _P_MES_PreStart = "MES02A";
constexpr auto _P_MES_PreFinish = "MES02B";
constexpr auto _P_MES_BinStart = "MES03A";
constexpr auto _P_MES_BinFinish = "MES03B";
constexpr auto _P_MES_ThinStart = "MES04A";
constexpr auto _P_MES_ThinFinish = "MES04B";
constexpr auto _P_MES_OpenStart = "MES05A";
constexpr auto _P_MES_OpenFinish = "MES05B";
constexpr auto _P_MES_EdgeStart = "MES06A";
constexpr auto _P_MES_EdgeFinish = "MES06B";
constexpr auto _P_MES_HCStart = "MES07A";
constexpr auto _P_MES_HCFinish = "MES07B";
constexpr auto _P_MES_HLStart = "MES08A";
constexpr auto _P_MES_HLFinish = "MES08B";
constexpr auto _P_MES_DialStart = "MES09A";
constexpr auto _P_MES_DialFinish = "MES09B";
constexpr auto _P_MES_IndStart = "MES10A";
constexpr auto _P_MES_IndFinish = "MES10B";
constexpr auto _P_MES_CalStart = "MES11A";
constexpr auto _P_MES_CalFinish = "MES11B";

#endif // !SWI_PROTOCOL_H
/*
|SET01|设置工作路径|设置图片等文件所在目录|
|SET02|设置秒表型号|默认：505<br>可选：504/505|
|SET03|设置是否滤波处理|默认：是|
|SET03A|设置滤波方式|默认：双边滤波<br>可选：均值滤波/中指滤波/双边滤波|
|SET04|设置二值化处理方式|默认：OSTU算法<br>可选：手动设定阈值/OSTU算法|
|SET04A|设置二值化处理阈值|默认：127<br>OSTU算法不可手动设置|
|SET05|设置检测指针时是否使用细化算法|默认：是|
|SET05A|设置细化运算迭代次数|默认：12|
|SET06|设置是否使用开运算减少噪声|默认：否|
|SET07|设置边缘检测方式|默认：拉普拉斯算子<br>可选：Sobel算子/拉普拉斯算子/Canny算法|
|SET07A|设置Sobel算子检测方向|默认：水平+垂直<br>可选：水平/垂直/水平+垂直|
|SET07B|设置Canny算法阈值1|默认：5|
|SET07C|设置Canny算法阈值2|默认：20|
|SET08A|设置霍夫圆检测累加器分辨率|默认：1<br>数值越大，检测到的圆越多|
|SET08B|设置霍夫圆检测最小圆心距离|默认：200<br>小于此距离认为是一个圆|
|SET08C|设置霍夫圆检测中边缘检测步骤的高阈值|默认：100.0|
|SET08D|设置霍夫圆检测圆心的累加器阈值|默认：200.0<br>数值越小，检测出的圆越多|
|SET09A|设置霍夫直线检测累加器像素分辨率|默认：1|
|SET09B|设置霍夫直线检测累加器角度分辨率|默认：π/180|
|SET09C|设置霍夫直线检测累加器阈值|默认：100<br>数值越小，检测到的直线越多|
|SET09D|设置霍夫直线检测最小直线长度|默认：50<br>数值越小，检测到的直线越多|
|SET09E|设置霍夫直线检测最大直线间隙|默认：10<br>数值越大，检测到的直线越多|
|SET10|设置圆环绘制颜色|默认：#EE82EE（紫色）|
|SET11|设置圆心绘制颜色|默认：#FF0000（红色）|
|SET12|设置指针绘制颜色|默认：#00FF00（绿色）|
|SET13|是否估读|默认：是|
|SET14|设置修正值|默认：0.0（秒）|
||||
|MES01A|初始化-开始||
|MES01B|初始化-完成||
|MES02A|预处理-开始||
|MES02B|预处理-完成||
|MES03A|二值化-开始||
|MES03B|二值化-完成||
|MES04A|图像细化-开始||
|MES04B|图像细化-完成||
|MES05A|开运算-开始||
|MES05B|开运算-完成||
|MES06A|边缘检测-开始||
|MES06B|边缘检测-完成||
|MES07A|霍夫圆检测-开始||
|MES07B|霍夫圆检测-完成||
|MES08A|霍夫直线检测-开始||
|MES08B|霍夫直线检测-完成||
|MES09A|表盘定位-开始||
|MES09B|表盘定位-完成||
|MES10A|指针定位-开始||
|MES10B|指针定位-完成||
|MES11A|读数计算-开始||
|MES11B|读数计算-完成||
*/