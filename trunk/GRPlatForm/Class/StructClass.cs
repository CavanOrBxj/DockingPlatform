using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GRPlatForm
{

    public class timestrategies
    {
        /// <summary>
        /// 策略ID
        /// </summary>
        public string ID { get; set; }
        /// <summary>
        /// 策略开始时间
        /// </summary>
        public string StartTime { get; set; }
        /// <summary>
        /// 策略结束时间
        /// </summary>
        public string EndTime { get; set; }
        /// <summary>
        /// 事件类型
        /// </summary>
        public string EvenType { get; set; }
    }


    public class strategytactics
    {
        public List<timestrategies> TimeList; 
    }


}
