using System.Threading;
using System.Collections.Generic;
using System.Data;
using GRPlatForm;

namespace GRPlatForm
{
    public class SingletonInfo
    {
        private static SingletonInfo _singleton;


        public string Longitude;//经度
        public string Latitude;//纬度
        public string CurrentURL;//当前平台对县平台的url

        public string CheckEBMStatusFlag;

        //   public Dictionary<string, string> AreacodeDic;

        public strategytactics audit;

        private SingletonInfo()                                                                 
        {
            Longitude = "";
            Latitude = "";
            CurrentURL = "";
            CheckEBMStatusFlag = "";
            audit = new strategytactics();
            audit.TimeList = new List<timestrategies>();
        }
        public static SingletonInfo GetInstance()
        {
            if (_singleton == null)
            {
                Interlocked.CompareExchange(ref _singleton, new SingletonInfo(), null);
            }
            return _singleton;
        }
    }
}