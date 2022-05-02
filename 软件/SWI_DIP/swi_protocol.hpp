#ifndef SWI_PROTOCOL_HPP
#define SWI_PROTOCOL_HPP
//���ô���
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
//��Ϣ����
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
|SET01|���ù���·��|����ͼƬ���ļ�����Ŀ¼|
|SET02|��������ͺ�|Ĭ�ϣ�505<br>��ѡ��504/505|
|SET03|�����Ƿ��˲�����|Ĭ�ϣ���|
|SET03A|�����˲���ʽ|Ĭ�ϣ�˫���˲�<br>��ѡ����ֵ�˲�/��ָ�˲�/˫���˲�|
|SET04|���ö�ֵ������ʽ|Ĭ�ϣ�OSTU�㷨<br>��ѡ���ֶ��趨��ֵ/OSTU�㷨|
|SET04A|���ö�ֵ��������ֵ|Ĭ�ϣ�127<br>OSTU�㷨�����ֶ�����|
|SET05|���ü��ָ��ʱ�Ƿ�ʹ��ϸ���㷨|Ĭ�ϣ���|
|SET05A|����ϸ�������������|Ĭ�ϣ�12|
|SET06|�����Ƿ�ʹ�ÿ������������|Ĭ�ϣ���|
|SET07|���ñ�Ե��ⷽʽ|Ĭ�ϣ�������˹����<br>��ѡ��Sobel����/������˹����/Canny�㷨|
|SET07A|����Sobel���Ӽ�ⷽ��|Ĭ�ϣ�ˮƽ+��ֱ<br>��ѡ��ˮƽ/��ֱ/ˮƽ+��ֱ|
|SET07B|����Canny�㷨��ֵ1|Ĭ�ϣ�5|
|SET07C|����Canny�㷨��ֵ2|Ĭ�ϣ�20|
|SET08A|���û���Բ����ۼ����ֱ���|Ĭ�ϣ�1<br>��ֵԽ�󣬼�⵽��ԲԽ��|
|SET08B|���û���Բ�����СԲ�ľ���|Ĭ�ϣ�200<br>С�ڴ˾�����Ϊ��һ��Բ|
|SET08C|���û���Բ����б�Ե��ⲽ��ĸ���ֵ|Ĭ�ϣ�100.0|
|SET08D|���û���Բ���Բ�ĵ��ۼ�����ֵ|Ĭ�ϣ�200.0<br>��ֵԽС��������ԲԽ��|
|SET09A|���û���ֱ�߼���ۼ������طֱ���|Ĭ�ϣ�1|
|SET09B|���û���ֱ�߼���ۼ����Ƕȷֱ���|Ĭ�ϣ���/180|
|SET09C|���û���ֱ�߼���ۼ�����ֵ|Ĭ�ϣ�100<br>��ֵԽС����⵽��ֱ��Խ��|
|SET09D|���û���ֱ�߼����Сֱ�߳���|Ĭ�ϣ�50<br>��ֵԽС����⵽��ֱ��Խ��|
|SET09E|���û���ֱ�߼�����ֱ�߼�϶|Ĭ�ϣ�10<br>��ֵԽ�󣬼�⵽��ֱ��Խ��|
|SET10|����Բ��������ɫ|Ĭ�ϣ�#EE82EE����ɫ��|
|SET11|����Բ�Ļ�����ɫ|Ĭ�ϣ�#FF0000����ɫ��|
|SET12|����ָ�������ɫ|Ĭ�ϣ�#00FF00����ɫ��|
|SET13|�Ƿ����|Ĭ�ϣ���|
|SET14|��������ֵ|Ĭ�ϣ�0.0���룩|
||||
|MES01A|��ʼ��-��ʼ||
|MES01B|��ʼ��-���||
|MES02A|Ԥ����-��ʼ||
|MES02B|Ԥ����-���||
|MES03A|��ֵ��-��ʼ||
|MES03B|��ֵ��-���||
|MES04A|ͼ��ϸ��-��ʼ||
|MES04B|ͼ��ϸ��-���||
|MES05A|������-��ʼ||
|MES05B|������-���||
|MES06A|��Ե���-��ʼ||
|MES06B|��Ե���-���||
|MES07A|����Բ���-��ʼ||
|MES07B|����Բ���-���||
|MES08A|����ֱ�߼��-��ʼ||
|MES08B|����ֱ�߼��-���||
|MES09A|���̶�λ-��ʼ||
|MES09B|���̶�λ-���||
|MES10A|ָ�붨λ-��ʼ||
|MES10B|ָ�붨λ-���||
|MES11A|��������-��ʼ||
|MES11B|��������-���||
*/