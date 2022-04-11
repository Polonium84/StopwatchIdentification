using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

namespace SWIdentification
{
    public partial class SWIMainForm : Form
    {
        //*****************全局变量********************
        Image originalImg;
        StopWatch[] stopWatches;
        string swdataFilePath = @".\StopWatches.xml";
        string cacheDirPath = @".\cache";
        string logFilePath = @".\log.txt";
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
            string newPath = @".\cache\originImage.jpg";
            Bitmap bitmap = null;
            using (OpenFileDialog dialog=new OpenFileDialog())
            {
                dialog.Filter =
                    "图片文件(*.JPG)|*.JPG|所有文件(*.*)|*.*";
                dialog.Title = "请选择秒表图片文件";
                dialog.RestoreDirectory = true;
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    string oriPath = dialog.FileName;
                    SWILog.Info("用户选择图片文件路径: " + oriPath);
                    File.Copy(oriPath,newPath);
                }
            }
            try { bitmap = new Bitmap(newPath); }
            catch(ArgumentException ex) { SWIException.InvalidImageFile(ex); };
            pbPic.Image = (Image)bitmap;
            SWILog.Info("成功加装图片文件");
        }
        /// <summary>
        /// 初始化
        /// </summary>
        void Initialize()
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
            if (Directory.Exists(cacheDirPath))
                Directory.Delete("cache", true);
            Directory.CreateDirectory("cache");
            //初始化窗口控件
            pbPic.Image = null;
            tbResultMin.Text = String.Empty;
            tbResultSec.Text = String.Empty;
            tbReliability.Text = String.Empty;
            //记录日志
            SWILog.Info("主窗口初始化成功");
        }
        void InitializeLog()
        {
            if (!File.Exists(logFilePath))
                File.Create(logFilePath).Close();
        }
    }
}
