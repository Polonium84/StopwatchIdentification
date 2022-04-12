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
    //���������ж���俴��ͼ��ͨ�����Ƿ���ȷ���������ʹ�õ�ͨ����ͼ��
    if (src.type() != CV_8UC1)
    {
        printf("ֻ�ܴ����ֵ��Ҷ�ͼ��\n");
        return;
    }
    //��ԭ�ز���ʱ��copy src��dst
    //��ͼƬ���п���
    if (dst.data != src.data)
    {
        src.copyTo(dst);
    }

    int i, j, n;/*���ﶨ��������������n��һ��ѭ������������,
    ����i��j�Ǳ������ص��ж�����*/
    int width, height;//������������������ͼƬ�Ŀ����߶�
    width = src.cols - 1;//����-1�ҵ������Ϊ�˱��ڴ������ı�Ե��ֵ
//֮���Լ�1���Ƿ��㴦��8���򣬷�ֹԽ��
    height = src.rows - 1;
    int step = src.step;//������Mat��һ�����ԣ�����step���һ������±߶������н���
    int  p2, p3, p4, p5, p6, p7, p8, p9;//����7�����������մ������ͼ��������ֵ
    uchar* img;//����һ���޷���ָ�룬��Ϊ�˽��մ���MatͼƬ�ĵ�ַ������ط��һ�����±߽��н���
    bool ifEnd;/*����һ���������͵ı�������Ϊ���±��ж��Ƿ�����ѭ���������������
    �ı䲼��ֵ����ѭ�������ж�
    */
    int A1;//����һ����������Ϊ��ͳ��8������0��1�Ķ�����һ�����Ϊ1���������Ϊ2���������������ж��Ƿ���������ȥ��������
    cv::Mat tmpimg;/*����һ���м�ͼƬģ������������ǰ�dst��ֵ������temp,Ȼ���������temp��ֵ���ҵ�Ҫɾ����ֵ�����Ǳ���֮������dst�иĵ�
    */
    //n��ʾ��������
    for (n = 0; n < intera; n++)
    {
        dst.copyTo(tmpimg);
        ifEnd = false;
        img = tmpimg.data;
        for (i = 1; i < height; i++)//��ʼ��ɨ��
        {
            img += step;//��ÿ�α���ÿ��step��ֵ��¼��ָ��img,
            for (j = 1; j < width; j++)//��ʼ����ͼƬ���У�
            {
                uchar* p = img + j;//�����Ǹղ�img��ֵ����j��ֵ��Ȼ��ֵ��ָ��p
                A1 = 0;//��A1������ֵ���г�ʼ��
                if (p[0] > 0)//�����ǿ�ʼzhang�����㷨�ĵ�һ�����ж�Ŀ��ֵ�Ƿ�����ִ������
                {
                    if (p[-step] == 0 && p[-step + 1] > 0) /*p2,p3 01ģʽ��P[-step]��ʾ����ֵp[0]�ϱߵ�һ����ֵ,P[-step+1]��ʾ��P[-step]��һ����ֵ*/
                    {
                        A1++;
                    }
                    if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01ģʽp[1]��ʾ����P[0]����һ�������±ߵ��Դ����ƣ��±ߵ�Ӧ�ö���������˰��Ҹо�
                    {
                        A1++;
                    }
                    if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01ģʽ
                    {
                        A1++;
                    }
                    if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01ģʽ
                    {
                        A1++;
                    }
                    if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01ģʽ
                    {
                        A1++;
                    }
                    if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01ģʽ
                    {
                        A1++;
                    }
                    if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01ģʽ
                    {
                        A1++;
                    }
                    if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01ģʽ
                    {
                        A1++;
                    }
                    //������
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
                            dst.at<uchar>(i, j) = 0; //����ɾ�����������õ�ǰ����Ϊ0
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
                    if (p[-step] == 0 && p[-step + 1] > 0) //p2,p3 01ģʽ
                    {
                        A1++;
                    }
                    if (p[-step + 1] == 0 && p[1] > 0) //p3,p4 01ģʽ
                    {
                        A1++;
                    }
                    if (p[1] == 0 && p[step + 1] > 0) //p4,p5 01ģʽ
                    {
                        A1++;
                    }
                    if (p[step + 1] == 0 && p[step] > 0) //p5,p6 01ģʽ
                    {
                        A1++;
                    }
                    if (p[step] == 0 && p[step - 1] > 0) //p6,p7 01ģʽ
                    {
                        A1++;
                    }
                    if (p[step - 1] == 0 && p[-1] > 0) //p7,p8 01ģʽ
                    {
                        A1++;
                    }
                    if (p[-1] == 0 && p[-step - 1] > 0) //p8,p9 01ģʽ
                    {
                        A1++;
                    }
                    if (p[-step - 1] == 0 && p[-step] > 0) //p9,p2 01ģʽ
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
                            dst.at<uchar>(i, j) = 0; //����ɾ�����������õ�ǰ����Ϊ0
                            ifEnd = true;
                        }
                    }
                }
            }
        }

        //��������ӵ����Ѿ�û�п���ϸ���������ˣ����˳�����
        if (!ifEnd) break;
    }
}
