
namespace SWIdentification
{
    partial class SWIMainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.pbPic = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnPhoto = new System.Windows.Forms.Button();
            this.btnInputFile = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.cbEstimate = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tbFix = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.cbSWType = new System.Windows.Forms.ComboBox();
            this.btnIdentify = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tbResultSec = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.tbResultMin = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.tbLog = new System.Windows.Forms.TextBox();
            this.lbOut1 = new System.Windows.Forms.Label();
            this.lbOut2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pbPic)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // pbPic
            // 
            this.pbPic.BackColor = System.Drawing.Color.MediumSeaGreen;
            this.pbPic.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pbPic.Location = new System.Drawing.Point(26, 53);
            this.pbPic.Name = "pbPic";
            this.pbPic.Size = new System.Drawing.Size(960, 750);
            this.pbPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pbPic.TabIndex = 0;
            this.pbPic.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnPhoto);
            this.groupBox1.Controls.Add(this.btnInputFile);
            this.groupBox1.Controls.Add(this.pbPic);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1023, 937);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "秒表图像";
            // 
            // btnPhoto
            // 
            this.btnPhoto.Enabled = false;
            this.btnPhoto.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnPhoto.Location = new System.Drawing.Point(623, 845);
            this.btnPhoto.Name = "btnPhoto";
            this.btnPhoto.Size = new System.Drawing.Size(244, 74);
            this.btnPhoto.TabIndex = 2;
            this.btnPhoto.Text = "在线拍摄";
            this.btnPhoto.UseVisualStyleBackColor = true;
            // 
            // btnInputFile
            // 
            this.btnInputFile.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnInputFile.Location = new System.Drawing.Point(136, 845);
            this.btnInputFile.Name = "btnInputFile";
            this.btnInputFile.Size = new System.Drawing.Size(244, 74);
            this.btnInputFile.TabIndex = 1;
            this.btnInputFile.Text = "导入图像文件";
            this.btnInputFile.UseVisualStyleBackColor = true;
            this.btnInputFile.Click += new System.EventHandler(this.btnInputFile_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.cbEstimate);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.tbFix);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.cbSWType);
            this.groupBox2.Location = new System.Drawing.Point(1065, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(556, 291);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "识别设置";
            // 
            // cbEstimate
            // 
            this.cbEstimate.AutoSize = true;
            this.cbEstimate.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbEstimate.Location = new System.Drawing.Point(221, 221);
            this.cbEstimate.Name = "cbEstimate";
            this.cbEstimate.Size = new System.Drawing.Size(111, 37);
            this.cbEstimate.TabIndex = 11;
            this.cbEstimate.Text = "估读";
            this.cbEstimate.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(329, 144);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(47, 33);
            this.label7.TabIndex = 10;
            this.label7.Text = "秒";
            // 
            // tbFix
            // 
            this.tbFix.BackColor = System.Drawing.SystemColors.Window;
            this.tbFix.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbFix.Location = new System.Drawing.Point(221, 141);
            this.tbFix.Name = "tbFix";
            this.tbFix.ReadOnly = true;
            this.tbFix.Size = new System.Drawing.Size(101, 44);
            this.tbFix.TabIndex = 9;
            this.tbFix.Text = "0.0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(65, 144);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(111, 33);
            this.label3.TabIndex = 2;
            this.label3.Text = "修正值";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(33, 67);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(143, 33);
            this.label1.TabIndex = 1;
            this.label1.Text = "秒表型号";
            // 
            // cbSWType
            // 
            this.cbSWType.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbSWType.FormattingEnabled = true;
            this.cbSWType.Items.AddRange(new object[] {
            "504",
            "505"});
            this.cbSWType.Location = new System.Drawing.Point(221, 67);
            this.cbSWType.Name = "cbSWType";
            this.cbSWType.Size = new System.Drawing.Size(224, 41);
            this.cbSWType.TabIndex = 0;
            // 
            // btnIdentify
            // 
            this.btnIdentify.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnIdentify.Location = new System.Drawing.Point(1065, 585);
            this.btnIdentify.Name = "btnIdentify";
            this.btnIdentify.Size = new System.Drawing.Size(176, 79);
            this.btnIdentify.TabIndex = 2;
            this.btnIdentify.Text = "识别";
            this.btnIdentify.UseVisualStyleBackColor = true;
            this.btnIdentify.Click += new System.EventHandler(this.btnIdentify_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.tbResultSec);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.tbResultMin);
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Location = new System.Drawing.Point(1065, 342);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(546, 222);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "识别结果";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(425, 143);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(57, 40);
            this.label5.TabIndex = 8;
            this.label5.Text = "秒";
            // 
            // tbResultSec
            // 
            this.tbResultSec.BackColor = System.Drawing.SystemColors.Window;
            this.tbResultSec.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbResultSec.Location = new System.Drawing.Point(163, 140);
            this.tbResultSec.Name = "tbResultSec";
            this.tbResultSec.ReadOnly = true;
            this.tbResultSec.Size = new System.Drawing.Size(256, 53);
            this.tbResultSec.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(425, 59);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(57, 40);
            this.label4.TabIndex = 6;
            this.label4.Text = "分";
            // 
            // tbResultMin
            // 
            this.tbResultMin.BackColor = System.Drawing.SystemColors.Window;
            this.tbResultMin.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.tbResultMin.Location = new System.Drawing.Point(163, 56);
            this.tbResultMin.Name = "tbResultMin";
            this.tbResultMin.ReadOnly = true;
            this.tbResultMin.Size = new System.Drawing.Size(256, 53);
            this.tbResultMin.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(40, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(97, 40);
            this.label2.TabIndex = 2;
            this.label2.Text = "读数";
            // 
            // btnReset
            // 
            this.btnReset.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnReset.Location = new System.Drawing.Point(1258, 585);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(169, 79);
            this.btnReset.TabIndex = 4;
            this.btnReset.Text = "重置";
            this.btnReset.UseVisualStyleBackColor = true;
            // 
            // btnSave
            // 
            this.btnSave.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnSave.Location = new System.Drawing.Point(1443, 585);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(168, 79);
            this.btnSave.TabIndex = 5;
            this.btnSave.Text = "保存";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.ForeColor = System.Drawing.Color.OrangeRed;
            this.label6.Location = new System.Drawing.Point(12, 967);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(670, 24);
            this.label6.TabIndex = 6;
            this.label6.Text = "哈尔滨理工大学 测控技术与通信工程学院 测控18-5班 贾亦祺";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(1065, 781);
            this.progressBar1.Maximum = 130;
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(546, 34);
            this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar1.TabIndex = 7;
            // 
            // tbLog
            // 
            this.tbLog.BackColor = System.Drawing.SystemColors.Window;
            this.tbLog.Location = new System.Drawing.Point(1065, 850);
            this.tbLog.Multiline = true;
            this.tbLog.Name = "tbLog";
            this.tbLog.ReadOnly = true;
            this.tbLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tbLog.Size = new System.Drawing.Size(546, 99);
            this.tbLog.TabIndex = 8;
            // 
            // lbOut1
            // 
            this.lbOut1.AutoSize = true;
            this.lbOut1.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbOut1.ForeColor = System.Drawing.SystemColors.Highlight;
            this.lbOut1.Location = new System.Drawing.Point(1060, 750);
            this.lbOut1.Name = "lbOut1";
            this.lbOut1.Size = new System.Drawing.Size(96, 28);
            this.lbOut1.TabIndex = 9;
            this.lbOut1.Text = "label8";
            // 
            // lbOut2
            // 
            this.lbOut2.AutoSize = true;
            this.lbOut2.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbOut2.ForeColor = System.Drawing.Color.BlueViolet;
            this.lbOut2.Location = new System.Drawing.Point(1060, 718);
            this.lbOut2.Name = "lbOut2";
            this.lbOut2.Size = new System.Drawing.Size(96, 28);
            this.lbOut2.TabIndex = 10;
            this.lbOut2.Text = "label8";
            // 
            // SWIMainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1633, 1000);
            this.Controls.Add(this.lbOut2);
            this.Controls.Add(this.lbOut1);
            this.Controls.Add(this.tbLog);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnReset);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.btnIdentify);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "SWIMainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "机械秒表自动读数软件";
            this.Load += new System.EventHandler(this.SWIMainForm_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pbPic)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pbPic;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnPhoto;
        private System.Windows.Forms.Button btnInputFile;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbSWType;
        private System.Windows.Forms.Button btnIdentify;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tbResultSec;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tbResultMin;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox tbFix;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TextBox tbLog;
        private System.Windows.Forms.CheckBox cbEstimate;
        private System.Windows.Forms.Label lbOut1;
        private System.Windows.Forms.Label lbOut2;
    }
}

