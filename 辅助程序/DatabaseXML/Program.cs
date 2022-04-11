using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Xml;
using System.Xml.Serialization;
using SWIdentification;

namespace DatabaseXML
{
    class Program
    {
        static void Main(string[] args)
        {
            SWIdentification.StopWatch[] sw = new StopWatch[2];
            sw[0] = new StopWatch("504", 0.1f, 15, 30);
            sw[1] = new StopWatch("505", 0.2f, 30, 60);
            FileStream fs = new FileStream("StopWatches.xml", FileMode.Append);
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Encoding = Encoding.UTF8;
            XmlWriter writer = XmlWriter.Create(fs, settings);
            XmlSerializer serializer = new XmlSerializer(typeof(SWIdentification.StopWatch[]));
            serializer.Serialize(writer, sw);
            Console.ReadLine();
        }
    }
}
