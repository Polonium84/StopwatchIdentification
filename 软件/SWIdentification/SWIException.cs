using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace SWIdentification
{
    public static class SWIException
    {
        public static void SWDataNotFound()
        {
            string exText = "未找到秒表数据库文件";
            SWILog.Error(exText);
            MessageBox.Show(exText, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            throw new FileNotFoundException(exText, "StopWatches.xml");
        }
        public static void InvalidImageFile(ArgumentException e)
        {
            string exText = "无效的图片文件";
            SWILog.Error(exText);
            MessageBox.Show(exText, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            throw new InvalidOperationException(exText, e);
        }
    }
}
