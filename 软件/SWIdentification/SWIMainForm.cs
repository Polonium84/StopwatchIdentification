using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.IO.Compression;
using System.Threading;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Serialization;
using System.Text;
using System.Text.RegularExpressions;

namespace SWIdentification
{
    public partial class SWIMainForm : Form
    {
        //*****************全局变量********************
        private StopWatch[] stopWatches;
        private string swdataFilePath = @".\StopWatches.xml";
        private string cacheDirPath = @".\cache";
        private string saveDirPath = @".\save";
        private string logFilePath = @".\log.txt";
        private string csvFilePath = @".\record.csv";
        public string arguments;
        public DateTime time_begin, time_end;
        private delegate void TextOutput(string s);
        private delegate void Out1(string s);
        private delegate void Out2(string s);
        private delegate void MakeProgress();
        private delegate void ShowResultCaller(string result, int index);
        private delegate string GetArgumentsCaller();

        //********************************************
        public SWIMainForm()
        {
            InitializeComponent();
            InitializeLog();
        }

        private void SWIMainForm_Load(object sender, EventArgs e)
        {
            Initialize();
        }

        /// <summary>
        /// 点击导入图片按钮事件
        /// </summary>
        private void btnInputFile_Click(object sender, EventArgs e)
        {
            string newPath = @".\cache\source.jpg";
            if (File.Exists(newPath))
                File.Delete(newPath);
            Bitmap bitmap = null;
            using (OpenFileDialog dialog = new OpenFileDialog())
            {
                dialog.Filter =
                    "图片文件(*.JPG)|*.JPG|所有文件(*.*)|*.*";
                dialog.Title = "请选择秒表图片文件";
                dialog.RestoreDirectory = true;
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    string oriPath = dialog.FileName;
                    SWILog.Info("用户选择图片文件路径: " + oriPath);
                    File.Copy(oriPath, newPath);
                }
            }
            try { bitmap = new Bitmap(newPath); }
            catch (ArgumentException ex) { SWIException.InvalidImageFile(ex); };
            pbPic.Image = (Image)bitmap;
            SWILog.Info("成功加装图片文件");
        }

        /// <summary>
        /// 初始化
        /// </summary>
        private void Initialize()
        {
            //检查并导入秒表数据库文件
            if (!File.Exists(swdataFilePath))
                SWIException.SWDataNotFound();
            XmlSerializer xmlSerializer = new XmlSerializer(typeof(StopWatch[]));
            XmlReader xmlReader = XmlReader.Create(swdataFilePath);
            stopWatches = (StopWatch[])xmlSerializer.Deserialize(xmlReader);
            cbSWType.Items.Clear();
            cbSWType.Items.AddRange(stopWatches);
            cbSWType.SelectedIndex = 0;
            //创建或清空缓存文件夹
            pbPic.Image = null;
            if (Directory.Exists(cacheDirPath))
                Directory.Delete("cache", true);
            Directory.CreateDirectory("cache");
            //创建储存文件夹
            if (!Directory.Exists(saveDirPath))
                Directory.CreateDirectory(saveDirPath);
            //初始化窗口控件
            pbPic.Image = null;
            tbResultMin.Text = String.Empty;
            tbResultSec.Text = String.Empty;
            lbOut1.Text = String.Empty;
            lbOut2.Text = String.Empty;
            progressBar1.Value = 0;
            //记录日志
            SWILog.Info("主窗口初始化成功");
        }
        /// <summary>
        /// 日志初始化
        /// </summary>
        private void InitializeLog()
        {
            if (!File.Exists(logFilePath))
                File.Create(logFilePath).Close();
        }
        /// <summary>
        /// 保存识别结果
        /// </summary>
        private void Save()
        {
            DateTime time = DateTime.Now;
            string header = "记录时间,秒表型号,识别结果(分),识别结果(秒)\n";
            string content =$"{time.ToString("G")},{cbSWType.SelectedItem.ToString()}," +
                $"{tbResultMin.Text},{tbResultSec.Text}";
            File.AppendAllText(csvFilePath, '\n' + content);
            string csvPath = Path.Combine(cacheDirPath, "result.csv");
            File.WriteAllText(csvPath, header + content);
            string zipname = time.ToString("yyMMdd_HHmmss") + ".zip";
            ZipFile.CreateFromDirectory(cacheDirPath, Path.Combine(saveDirPath, zipname));
            Output("保存成功");
        }
        /// <summary>
        /// 输出调试信息
        /// </summary>
        /// <param name="text">内容</param>
        private void Output(string text)
        {
            if (tbLog.InvokeRequired)
            {
                TextOutput d = new TextOutput(Output);
                this.Invoke(d, new object[] { text });
            }
            else
                this.tbLog.Text += text + "\r\n";
        }
        /// <summary>
        /// 更新状态显示1
        /// </summary>
        /// <param name="text">内容</param>
        private void Output1(string text)
        {
            if (lbOut1.InvokeRequired)
            {
                Out1 out1 = new Out1(Output1);
                this.Invoke(out1, new object[] { text });
            }
            else
                this.lbOut1.Text = text;
        }
        /// <summary>
        /// 更新状态显示2
        /// </summary>
        /// <param name="text">内容</param>
        private void Output2(string text)
        {
            if (lbOut2.InvokeRequired)
            {
                Out2 out2 = new Out2(Output2);
                this.Invoke(out2, new object[] { text });
            }
            else
                this.lbOut2.Text = text;
        }
        /// <summary>
        /// 进度条前进
        /// </summary>
        private void GoAhead()
        {
            if (progressBar1.InvokeRequired)
            {
                MakeProgress makeProgress = new MakeProgress(GoAhead);
                this.Invoke(makeProgress);
            }
            else
                this.progressBar1.PerformStep();
        }
        /// <summary>
        /// 显示计算结果
        /// </summary>
        /// <param name="result">结果数值</param>
        /// <param name="index">分/秒</param>
        private void ShowResult(string result,int index)
        {
            if (tbResultMin.InvokeRequired || tbResultSec.InvokeRequired)
            {
                ShowResultCaller caller = new ShowResultCaller(ShowResult);
                this.Invoke(caller, new object[] { result, index });
            }
            else
            {
                if (index == 1)
                    this.tbResultMin.Text = Double.Parse(result).ToString("F0");
                else
                {
                    if (this.cbEstimate.Checked)
                        this.tbResultSec.Text = Double.Parse(result).ToString("F2");
                    else
                        this.tbResultSec.Text = Double.Parse(result).ToString("F1");
                }
            }
        }
        /// <summary>
        /// 调用数字图像处理陈故乡
        /// </summary>
        private void DIP()
        {
            Process dip = new Process();
            dip.StartInfo.FileName =
                @"F:\毕业设计\程序\软件\SWIdentification\x64\Release\SWI_DIP.exe";
            //  @"F:\毕业设计\程序\辅助程序\SWI_DIP_Test\x64\Release\SWI_DIP_Test.exe";
            dip.StartInfo.Arguments = arguments;
            dip.StartInfo.UseShellExecute = false;
            dip.StartInfo.CreateNoWindow = true;
            dip.StartInfo.RedirectStandardOutput = true;
            dip.StartInfo.RedirectStandardInput = true;
            dip.OutputDataReceived += new DataReceivedEventHandler(Dip_OutputDataReceived);
            dip.Start();
            dip.BeginOutputReadLine();
            dip.WaitForExit();
        }
        /// <summary>
        /// 获取设置参数
        /// </summary>
        /// <returns>调用程序的传递参数</returns>
        private string GetArgruments()
        {
            StringBuilder builder = new StringBuilder();
            if (this.InvokeRequired)
            {
                GetArgumentsCaller getArgumentsCaller = new GetArgumentsCaller(GetArgruments);
                this.Invoke(getArgumentsCaller);
            }
            else
            {   
                builder.Append("dependent ");
                builder.Append(Path.GetFullPath(cacheDirPath) + ' ');
                if (cbSWType.SelectedItem.ToString().Contains("504"))
                    builder.Append("504 ");
                else
                    builder.Append("505 ");
                if (cbEstimate.Checked)
                    builder.Append("1 ");
                else
                    builder.Append("0 ");
                builder.Append(tbFix.Text);
            }
            return builder.ToString();
        }
        /// <summary>
        /// 接收输出事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Dip_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            string s = e.Data;
            Output(s);
            ParseMessage(s);
        }
        /// <summary>
        /// 点击识别按钮事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnIdentify_Click(object sender, EventArgs e)
        {
            arguments = GetArgruments();
            ThreadStart dipThreadStart = new ThreadStart(DIP);
            Thread dipProcess = new Thread(dipThreadStart);
            dipProcess.IsBackground = true;
            dipProcess.Start();
            time_begin = DateTime.Now;
        }
        /// <summary>
        /// 解析消息内容
        /// </summary>
        /// <param name="mes">消息内容</param>
        void ParseMessage(string mes)
        {
            if (mes == null)
                return;
            Regex re_type = new Regex("\\[(.*?)\\]");
            Regex re_code = new Regex("\\{(.*?)\\}");
            Regex re_content = new Regex("\\((.*?)\\)");
            string type = String.Empty;
            string code = String.Empty;
            string content = String.Empty;
            if (re_type.IsMatch(mes))
                type = re_type.Match(mes).Groups[1].Value;
            if (re_code.IsMatch(mes))
                code = re_code.Match(mes).Groups[1].Value;
            if (re_content.IsMatch(mes))
                content = re_content.Match(mes).Groups[1].Value;
            HandleMessage(type, code, content);
        }
        /// <summary>
        /// 处理消息
        /// </summary>
        /// <param name="type">消息类型</param>
        /// <param name="code">消息代码</param>
        /// <param name="content">消息数据内容</param>
        void HandleMessage(string type,string code,string content)
        {
            if (type != "SEND")
                return;
            switch (code)
            {
                case "SET01":
                    Output1("正在设置参数");
                    break;
                case "SET02":
                    break;
                case "SET13":
                    break;
                case "SET14":
                    GoAhead();
                    break;
                case "MES02A":
                    Output1("正在预处理图像");
                    break;
                case "MES02B":
                    GoAhead();
                    break;
                case "MES03A":
                    Output1("正在二值化图像");
                    break;
                case "MES03B":
                    GoAhead();
                    break;
                case "MES04A":
                    Output1("正在细化图像");
                    break;
                case "MES04B":
                    GoAhead();
                    break;
                case "MES06A":
                    Output1("正在边缘检测");
                    break;
                case "MES06B":
                    GoAhead();
                    break;
                case "MES07A":
                    Output1("正在霍夫圆检测");
                    break;
                case "MES07B":
                    GoAhead();
                    break;
                case "MES08A":
                    Output1("正在霍夫直线检测");
                    break;
                case "MES08B":
                    GoAhead();
                    break;
                case "MES09A":
                    Output2("定位表盘中...");
                    break;
                case "MES09B":
                    Output2("");
                    GoAhead();
                    break;
                case "MES10A":
                    Output2("定位指针中...");
                    break;
                case "MES10B":
                    Output2("");
                    GoAhead();
                    break;
                case "MES11A":
                    Output1("正在计算读数结果");
                    break;
                case "MES11B":
                    GoAhead();
                    break;
                case "OUT01":
                    Output1("正在接收读数结果");
                    ShowResult(content, 1);
                    break;
                case "OUT02":
                    ShowResult(content, 2);
                    time_end = DateTime.Now;
                    TimeSpan span = time_end - time_begin;
                    Output1($"任务完成，用时{span.TotalSeconds}秒");
                    GoAhead();
                    break;
            }
        }
        /// <summary>
        /// 结果（秒）文本框内容改变事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tbResultSec_TextChanged(object sender, EventArgs e)
        {
            if ((sender as TextBox).Text == String.Empty)
                return;
            string finalImgPath = Path.Combine(cacheDirPath, "finish.jpg");
            if (File.Exists(finalImgPath))
            {
                Bitmap finalImg = new Bitmap(finalImgPath);
                pbPic.Image = (Image)finalImg;
            }
        }
        /// <summary>
        /// 点击重置按钮事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnReset_Click(object sender, EventArgs e)
        {
            Initialize();
        }
        /// <summary>
        /// 点击保存按钮事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSave_Click(object sender, EventArgs e)
        {
            Save();
            Output2("保存成功");
        }
    }
}