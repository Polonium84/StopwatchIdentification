using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace CsControl
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        delegate void AddTest(string s);
        void NewProcess()
        {
            using (Process exe = new Process())
            {
                exe.StartInfo.FileName = @"F:\毕业设计\程序\测试程序\CppConsole\x64\Release\CppConsole.exe";
                exe.StartInfo.UseShellExecute = false;
                //exe.StartInfo.CreateNoWindow = true;
                exe.StartInfo.RedirectStandardOutput = true;
                exe.StartInfo.RedirectStandardInput = true;
                exe.OutputDataReceived += new DataReceivedEventHandler(Exe_OutputDataReceived);
                string s = null;
                exe.Start();
                StreamWriter sw = exe.StandardInput;
                exe.BeginOutputReadLine();
                sw.WriteLine(3);
                exe.WaitForExit();
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            ThreadStart ts = new ThreadStart(NewProcess);
            Thread thread = new Thread(ts);
            thread.Start();
        }
        public void Show(string s)
        {
            if(textBox1.InvokeRequired)
            {
                AddTest d = new AddTest(Show);
                Invoke(d, new object[] { s });
            }
            else
                textBox1.Text += s + "\r\n";
        }
        private void Exe_OutputDataReceived(object sender, DataReceivedEventArgs e)
        {
            
            string s = e.Data;
            //MessageBox.Show(s);
            //Show(s);
            if(!backgroundWorker1.IsBusy)
                backgroundWorker1.RunWorkerAsync(s);
            //throw new NotImplementedException();
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            textBox1.Text += e.Argument.ToString()+'\n';
        }
    }
}
