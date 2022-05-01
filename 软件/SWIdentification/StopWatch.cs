namespace SWIdentification
{
    public class StopWatch
    {
        //秒表型号
        public string Type { get; set; }

        //分辨率（秒）
        public float Resolution { get; set; }

        //分针每圈（分）
        public int MinEachLoop { get; set; }

        //秒针每圈（秒）
        public int SecEachLoop { get; set; }

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="Type">秒表型号</param>
        /// <param name="Resolution">分辨率（秒）</param>
        /// <param name="MinEachLoop">分针每圈（分）</param>
        /// <param name="SecEachLoop">秒针每圈（秒）</param>
        public StopWatch(string Type, float Resolution, int MinEachLoop, int SecEachLoop)
        {
            this.Type = Type;
            this.Resolution = Resolution;
            this.MinEachLoop = MinEachLoop;
            this.SecEachLoop = SecEachLoop;
        }

        public StopWatch()
        {
        }

        public override string ToString()
        {
            return this.Type;
        }
    }
}