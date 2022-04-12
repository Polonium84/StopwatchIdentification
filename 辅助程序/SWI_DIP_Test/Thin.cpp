#include "SWI_DIP_Test.h"

void ThinSubiteration1(Mat& pSrc, Mat& pDst) {
    int rows = pSrc.rows;
    int cols = pSrc.cols;
    pSrc.copyTo(pDst);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (pSrc.at<float>(i, j) == 1.0f) {
                /// get 8 neighbors
                /// calculate C(p)
                int neighbor0 = (int)pSrc.at<float>(i - 1, j - 1);
                int neighbor1 = (int)pSrc.at<float>(i - 1, j);
                int neighbor2 = (int)pSrc.at<float>(i - 1, j + 1);
                int neighbor3 = (int)pSrc.at<float>(i, j + 1);
                int neighbor4 = (int)pSrc.at<float>(i + 1, j + 1);
                int neighbor5 = (int)pSrc.at<float>(i + 1, j);
                int neighbor6 = (int)pSrc.at<float>(i + 1, j - 1);
                int neighbor7 = (int)pSrc.at<float>(i, j - 1);
                int C = int(~neighbor1 & (neighbor2 | neighbor3)) +
                    int(~neighbor3 & (neighbor4 | neighbor5)) +
                    int(~neighbor5 & (neighbor6 | neighbor7)) +
                    int(~neighbor7 & (neighbor0 | neighbor1));
                if (C == 1) {
                    /// calculate N
                    int N1 = int(neighbor0 | neighbor1) +
                        int(neighbor2 | neighbor3) +
                        int(neighbor4 | neighbor5) +
                        int(neighbor6 | neighbor7);
                    int N2 = int(neighbor1 | neighbor2) +
                        int(neighbor3 | neighbor4) +
                        int(neighbor5 | neighbor6) +
                        int(neighbor7 | neighbor0);
                    int N = min(N1, N2);
                    if ((N == 2) || (N == 3)) {
                        /// calculate criteria 3
                        int c3 = (neighbor1 | neighbor2 | ~neighbor4) & neighbor3;
                        if (c3 == 0) {
                            pDst.at<float>(i, j) = 0.0f;
                        }
                    }
                }
            }
        }
    }
}


void ThinSubiteration2(Mat& pSrc, Mat& pDst) {
    int rows = pSrc.rows;
    int cols = pSrc.cols;
    pSrc.copyTo(pDst);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (pSrc.at<float>(i, j) == 1.0f) {
                /// get 8 neighbors
                /// calculate C(p)
                int neighbor0 = (int)pSrc.at<float>(i - 1, j - 1);
                int neighbor1 = (int)pSrc.at<float>(i - 1, j);
                int neighbor2 = (int)pSrc.at<float>(i - 1, j + 1);
                int neighbor3 = (int)pSrc.at<float>(i, j + 1);
                int neighbor4 = (int)pSrc.at<float>(i + 1, j + 1);
                int neighbor5 = (int)pSrc.at<float>(i + 1, j);
                int neighbor6 = (int)pSrc.at<float>(i + 1, j - 1);
                int neighbor7 = (int)pSrc.at<float>(i, j - 1);
                int C = int(~neighbor1 & (neighbor2 | neighbor3)) +
                    int(~neighbor3 & (neighbor4 | neighbor5)) +
                    int(~neighbor5 & (neighbor6 | neighbor7)) +
                    int(~neighbor7 & (neighbor0 | neighbor1));
                if (C == 1) {
                    /// calculate N
                    int N1 = int(neighbor0 | neighbor1) +
                        int(neighbor2 | neighbor3) +
                        int(neighbor4 | neighbor5) +
                        int(neighbor6 | neighbor7);
                    int N2 = int(neighbor1 | neighbor2) +
                        int(neighbor3 | neighbor4) +
                        int(neighbor5 | neighbor6) +
                        int(neighbor7 | neighbor0);
                    int N = min(N1, N2);
                    if ((N == 2) || (N == 3)) {
                        int E = (neighbor5 | neighbor6 | ~neighbor0) & neighbor7;
                        if (E == 0) {
                            pDst.at<float>(i, j) = 0.0f;
                        }
                    }
                }
            }
        }
    }
}

void gThin(cv::Mat& src, cv::Mat& dst, int intera)
{
    //这里先用判断语句看看图像通道数是否正确，这里必须使用单通道得图像
    if (src.type() != CV_8UC1)
    {
        printf("只能处理二值或灰度图像\n");
        return;
    }
    //非原地操作时候，copy src到dst
    //对图片进行拷贝
    if (dst.data != src.data)
    {
        src.copyTo(dst);
    }

    int i, j, n;/*这里定义三个变量变量n是一个循环迭代的作用,
    变量i、j是遍历像素的判断条件*/
    int width, height;//定义两个变量，接收图片的宽度与高度
    width = src.cols - 1;//这里-1我的理解是为了便于处理矩阵的边缘数值
//之所以减1，是方便处理8邻域，防止越界
    height = src.rows - 1;
    int step = src.step;//这里是Mat的一个属性，叫做step，我会在最下边对他进行讲解
    int  p2, p3, p4, p5, p6, p7, p8, p9;//定义7个变量，接收待会遍历图像矩阵的数值
    uchar* img;//定义一个无符号指针，是为了接收待会Mat图片的地址，这个地方我会放在下边进行讲解
    bool ifEnd;/*定义一个布尔类型的变量，是为了下边判断是否满足循环条件，不满足会
    改变布尔值，供循环条件判断
    */
    int A1;//定义一个变量。是为了统计8邻域中0、1的对数，一对则记为1，两对则记为2，这个变量最后是判断是否满足像素去除条件的
    cv::Mat tmpimg;/*定义一个中间图片模板变量，这里是把dst的值拷贝给temp,然后遍历的是temp的值，找到要删除的值。但是遍历之后是在dst中改的
    */
    //n表示迭代次数
    for (n = 0; n < intera; n++)
    {
        dst.copyTo(tmpimg);
        ifEnd = false;
        img = tmpimg.data;
        for (i = 1; i < height; i++)//开始行扫描
        {
            img += step;//把每次遍历每行step的值记录给指针img,
            for (j = 1; j < width; j++)//开始遍历图片的列，
            {
                uchar* p = img + j;//这里是刚才img的值加上j的值，然后赋值给指针p
                A1 = 0;//对A1变量的值进行初始化
                if (p[0] > 0)//这里是开始zhang并行算法的第一步，判断目标值是否满足执行条件
                {
                    if (p[-step] == 0 && p[-step + 1] > 0) /*p2,p3 01模式，P[-step]表示的是值p[0]上边的一个数值,P[-step+1]表示是P[-step]下一个数值*/
                    {
                        A1++;
                    }
                    if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01模式p[1]表示的是P[0]的下一个数，下边的以此类推，下边的应该都可以理解了吧我感觉
                    {
                        A1++;
                    }
                    if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01模式
                    {
                        A1++;
                    }
                    if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01模式
                    {
                        A1++;
                    }
                    if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01模式
                    {
                        A1++;
                    }
                    if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01模式
                    {
                        A1++;
                    }
                    if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01模式
                    {
                        A1++;
                    }
                    if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01模式
                    {
                        A1++;
                    }
                    //这里是
                    p2 = p[-step] > 0 ? 1 : 0;
                    p3 = p[-step + 1] > 0 ? 1 : 0;
                    p4 = p[1] > 0 ? 1 : 0;
                    p5 = p[step + 1] > 0 ? 1 : 0;
                    p6 = p[step] > 0 ? 1 : 0;
                    p7 = p[step - 1] > 0 ? 1 : 0;
                    p8 = p[-1] > 0 ? 1 : 0;
                    p9 = p[-step - 1] > 0 ? 1 : 0;
                    if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 1 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) < 7 && A1 == 1)
                    {
                        if ((p2 == 0 || p4 == 0 || p6 == 0) && (p4 == 0 || p6 == 0 || p8 == 0)) //p2*p4*p6=0 && p4*p6*p8==0
                        {
                            dst.at<uchar>(i, j) = 0; //满足删除条件，设置当前像素为0
                            ifEnd = true;
                        }
                    }
                }
            }
        }

        dst.copyTo(tmpimg);
        img = tmpimg.data;
        for (i = 1; i < height; i++)
        {
            img += step;
            for (j = 1; j < width; j++)
            {
                A1 = 0;
                uchar* p = img + j;
                if (p[0] > 0)
                {
                    if (p[-step] == 0 && p[-step + 1] > 0) //p2,p3 01模式
                    {
                        A1++;
                    }
                    if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01模式
                    {
                        A1++;
                    }
                    if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01模式
                    {
                        A1++;
                    }
                    if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01模式
                    {
                        A1++;
                    }
                    if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01模式
                    {
                        A1++;
                    }
                    if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01模式
                    {
                        A1++;
                    }
                    if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01模式
                    {
                        A1++;
                    }
                    if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01模式
                    {
                        A1++;
                    }
                    p2 = p[-step] > 0 ? 1 : 0;
                    p3 = p[-step + 1] > 0 ? 1 : 0;
                    p4 = p[1] > 0 ? 1 : 0;
                    p5 = p[step + 1] > 0 ? 1 : 0;
                    p6 = p[step] > 0 ? 1 : 0;
                    p7 = p[step - 1] > 0 ? 1 : 0;
                    p8 = p[-1] > 0 ? 1 : 0;
                    p9 = p[-step - 1] > 0 ? 1 : 0;
                    if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) > 1 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) < 7 && A1 == 1)
                    {
                        if ((p2 == 0 || p4 == 0 || p8 == 0) && (p2 == 0 || p6 == 0 || p8 == 0)) //p2*p4*p8=0 && p2*p6*p8==0
                        {
                            dst.at<uchar>(i, j) = 0; //满足删除条件，设置当前像素为0
                            ifEnd = true;
                        }
                    }
                }
            }
        }

        //如果两个子迭代已经没有可以细化的像素了，则退出迭代
        if (!ifEnd) break;
    }
}
