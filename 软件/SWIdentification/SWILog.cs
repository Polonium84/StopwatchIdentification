using System;
using System.Text;
using System.IO;

namespace SWIdentification
{
    static class SWILog
    {
        static string logFilePath = @".\log.txt";
        public static void Info(string content)
        {
            string date = DateTime.Now.ToString("G");
            string text = String.Format("[{0}][INFO]:{1}", date, content);
            StreamWriter sw = new StreamWriter(logFilePath, true);
            sw.WriteLine(text);
            sw.Close();
        }
        public static void Warn(string content)
        {
            string date = DateTime.Now.ToString("G");
            string text = String.Format("[{0}][WARN]:{1}", date, content);
            StreamWriter sw = new StreamWriter(logFilePath, true);
            sw.WriteLine(text);
            sw.Close();
        }
        public static void Error(string content)
        {
            string date = DateTime.Now.ToString("G");
            string text = String.Format("[{0}][ERROR]:{1}", date, content);
            StreamWriter sw = new StreamWriter(logFilePath, true);
            sw.WriteLine(text);
            sw.Close();
        }
        public static void Debug(string content)
        {
            string date = DateTime.Now.ToString("G");
            string text = String.Format("[{0}][DEBUG]:{1}", date, content);
            StreamWriter sw = new StreamWriter(logFilePath, true);
            sw.WriteLine(text);
            sw.Close();
        }
    }
}
