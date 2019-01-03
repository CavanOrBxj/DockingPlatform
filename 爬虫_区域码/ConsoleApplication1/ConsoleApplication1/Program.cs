using Ivony.Html.Parser;
using Ivony.Html;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

using System.Text.RegularExpressions;
using System.IO;

namespace ConsoleApplication1
{
    class Program
    {

        static string prefix = "http://www.stats.gov.cn/tjsj/tjbz/tjyqhdmhcxhfdm/2017/";
        static string filepath = "";
        static string tmp = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase + "\\result\\";
        static JumonyParser parser = new JumonyParser();

        static void Main(string[] args)
        {
            string tmp = System.AppDomain.CurrentDomain.SetupInformation.ApplicationBase + "\\result\\";
            if (!Directory.Exists(tmp))//判断是否存在
            {
               
                Directory.CreateDirectory(tmp);//创建新路径
            }
            AllSheng();
            Sheng("11");
            Sheng("12");
            Sheng("13");
            Sheng("14");
            Sheng("15");
            Sheng("21");
            Sheng("22");
            Sheng("23");
            Sheng("31");
            //Sheng("32");
            Sheng("33");
            Sheng("34");
            Sheng("35");
            Sheng("36");
            Sheng("37");
            Sheng("41");
            Sheng("42");
            Sheng("43");
            Sheng("44");
            Sheng("45");
            Sheng("46");
            Sheng("50");
            Sheng("51");
            Sheng("52");
            Sheng("53");
            Sheng("54");
            Sheng("61");
            Sheng("62");
            Sheng("63");
            Sheng("64");
            Sheng("65");

            // Sql();



            Console.WriteLine("ok");
            Console.ReadLine();
        }


      

        private static void Sql()
        {
            string path = tmp;
            string[] names = System.IO.Directory.GetFiles(path);
            Regex reg = new Regex(@"\\\d+\.txt$");

            foreach (var file in names)
            {
                if (reg.IsMatch(file))
                {
                    string sheng = "";
                    string shi = "";
                    string xian = "";
                    string xiang = "";
                    StringBuilder sb = new StringBuilder();
                    string[] lines = System.IO.File.ReadAllLines(file);
                    foreach (var line in lines)
                    {
                        string tmp = line.Trim();
                        if (tmp.IndexOf("#") < 0) continue;
                        var arr = tmp.Split(new char[] { '#' }, StringSplitOptions.RemoveEmptyEntries);
                        string sql = "insert into sysareacode2(areacode,areaname,arealevel,areafullname) values('{0}','{1}',{2},'{3}');";
                        string level = "";
                        string fullname = "";
                        if (line.Length - tmp.Length == 0)
                        {
                            level = "1";
                            sheng = arr[0];
                            fullname = sheng;
                        }
                        else if (line.Length - tmp.Length == 1)
                        {
                            level = "2";
                            shi = arr[0];
                            fullname = sheng + shi;
                        }
                        else if (line.Length - tmp.Length == 2)
                        {
                            level = "3";
                            xian = arr[0];
                            fullname = sheng + shi + xian;
                        }
                        else if (line.Length - tmp.Length == 3)
                        {
                            level = "4";
                            xiang = arr[0];
                            fullname = sheng + shi + xian + xiang;
                        }
                        else if (line.Length - tmp.Length == 4)
                        {
                            level = "5";
                            fullname = sheng + shi + xian + xiang + arr[0];
                        }

                        sql = string.Format(sql, arr[1], arr[0], level, fullname);
                        sb.AppendLine(sql);
                    }
                    System.IO.File.WriteAllLines(file + ".sql", new string[] { sb.ToString() });
                }
            }

        }

       

        static void AllSheng()
        {
            JumonyParser parser = new JumonyParser();
            IEnumerable<IHtmlElement> list = load(prefix + "index.html").Find("tr.provincetr td a");
            foreach (var ele in list)
            {
                //遍历所有的省
                Sheng sheng = new Sheng();
                sheng.name = ele.InnerText().Trim();
                sheng.url = ele.Attribute("href").Value().Trim();
                sheng.code = sheng.url.Split(new char[] { '.' }, StringSplitOptions.RemoveEmptyEntries)[0];
                string path = tmp+ "allprovince.txt";
                System.IO.File.AppendAllLines(path, new string[] { sheng.name + "#" + sheng.code + "#" + sheng.url });
            }
        }
        static void Sheng(string code)
        {
            String[] lines = System.IO.File.ReadAllLines(tmp+"\\allprovince.txt");
            List<Sheng> shengs = new List<Sheng>();
            foreach (var line in lines)
            {
                Sheng t = new Sheng();
                t.code = line.Split(new char[] { '#' }, StringSplitOptions.RemoveEmptyEntries)[1];
                t.name = line.Split(new char[] { '#' }, StringSplitOptions.RemoveEmptyEntries)[0];
                t.url = line.Split(new char[] { '#' }, StringSplitOptions.RemoveEmptyEntries)[2];
                shengs.Add(t);
            }
            Sheng sheng = null;
            foreach (var i in shengs)
            {
                if (i.code == code)
                {
                    sheng = i;
                    break;
                }
            }
            if (sheng == null) return;
            IEnumerable<IHtmlElement> citys = parser.LoadDocument(prefix + sheng.url).Find("tr.citytr");
            filepath = tmp + sheng.name + ".txt";
            Console.WriteLine(sheng.name + "---" + sheng.code.PadRight(12,'0') + "---" + sheng.url);
            System.IO.File.AppendAllLines(filepath, new string[] { sheng.name + "#" + sheng.code.PadRight(12,'0') + "#" + sheng.url });
            foreach (var city in citys)
            {
                //遍历所有的市
                IEnumerable<IHtmlElement> a = city.Find("td a");
                Shi shi = new Shi();
                shi.url = a.ToList<IHtmlElement>()[1].Attribute("href").Value().Trim();
                shi.code = shi.url.Replace(sheng.code + "/", "").Split(new char[] { '.' }, StringSplitOptions.RemoveEmptyEntries)[0].PadRight(12,'0');
                shi.name = a.ToList<IHtmlElement>()[1].InnerText().Trim();
                sheng.shis.Add(shi);
                Console.WriteLine(shi.name + "---" + shi.code + "---" + shi.url);
                System.IO.File.AppendAllLines(filepath, new string[] { "\t" + shi.name + "#" + shi.code + "#" + shi.url });
                IEnumerable<IHtmlElement> li = load(prefix + shi.url).Find("tr.countytr");
                foreach (var tr in li)
                {
                    //遍历所有的县
                    IEnumerable<IHtmlElement> td = tr.Find("td");
                    Xian xian = new Xian();
                    if (td.Find("a").Count() > 0)
                    {
                        xian.url = td.ToList<IHtmlElement>()[0].Find("a").First<IHtmlElement>().Attribute("href").Value().Trim();
                        xian.code = td.ToList<IHtmlElement>()[0].Find("a").First<IHtmlElement>().InnerText().Trim();
                        xian.name = td.ToList<IHtmlElement>()[1].Find("a").First<IHtmlElement>().InnerText().Trim();
                        shi.xians.Add(xian);
                        Console.WriteLine("\t" + xian.name + "---" + xian.code + "---" + xian.url);
                        System.IO.File.AppendAllLines(filepath, new string[] { "\t\t" + xian.name + "#" + xian.code + "#" + xian.url });

                        IEnumerable<IHtmlElement> xiangs = load(prefix + sheng.code + "/" + xian.url).Find("tr.towntr");
                        foreach (var j in xiangs)
                        {
                            //遍历所有的乡
                            Xiang xiang = new Xiang();
                            xiang.code = j.Find("a").ToList<IHtmlElement>()[0].InnerText().Trim();
                            xiang.name = j.Find("a").ToList<IHtmlElement>()[1].InnerText().Trim();
                            xiang.url = j.Find("a").ToList<IHtmlElement>()[0].Attribute("href").Value().Trim();
                            xian.xiangs.Add(xiang);
                            Console.WriteLine("\t\t" + xiang.name + "---" + xiang.code + "---" + xiang.url);
                            System.IO.File.AppendAllLines(filepath, new string[] { "\t\t\t" + xiang.name + "#" + xiang.code + "#" + xiang.url });
                            string url = prefix + sheng.code + "/" + xian.url;
                            url = url.Substring(0, url.LastIndexOf("/")) + "/" + xiang.url;
                            IEnumerable<IHtmlElement> cuns = null;
                            cuns = load(url).Find("tr.villagetr");
                            foreach (var ko in cuns)
                            {
                                //遍历所有的村
                                Cun cun = new Cun();
                                cun.code = ko.Find("td").ToList<IHtmlElement>()[0].InnerText().Trim();
                                cun.name = ko.Find("td").ToList<IHtmlElement>()[2].InnerText().Trim();
                                xiang.cuns.Add(cun);
                                Console.WriteLine("\t\t\t\t" + cun.name + "---" + cun.code);
                                System.IO.File.AppendAllLines(filepath, new string[] { "\t\t\t\t" + cun.name + "#" + cun.code });
                            }
                            System.Threading.Thread.Sleep(1000);
                        }
                    }
                    else
                    {
                        xian.code = td.ToList<IHtmlElement>()[0].InnerText().Trim();
                        xian.name = td.ToList<IHtmlElement>()[1].InnerText().Trim();
                        shi.xians.Add(xian);
                        Console.WriteLine("\t" + xian.name + "---" + xian.code + "---" + xian.url);
                        System.IO.File.AppendAllLines(filepath, new string[] { "\t\t" + xian.name + "#" + xian.code + "#" + xian.url });
                    }
                }
                System.Threading.Thread.Sleep(3000);
            }


        }
        static IHtmlDocument load(string url)
        {
            IHtmlDocument res = null;
            int count = 0;
            do
            {
                try
                {
                    res = parser.LoadDocument(url);
                }
                catch (Exception ex)
                {
                    if (count > 5)
                    {
                        throw ex;
                    }
                    System.Threading.Thread.Sleep(3000);
                    count++;
                    continue;
                }

            } while (res == null);
            return res;
        }
    }

    public class Sheng
    {
        public string name { set; get; }
        public string url { set; get; }
        public string code { set; get; }
        public List<Shi> shis = new List<Shi>();
    }

    public class Shi
    {
        public string name { set; get; }
        public string code { set; get; }
        public string url { set; get; }
        public List<Xian> xians = new List<Xian>();

    }

    public class Xian
    {
        public string name { set; get; }
        public string code { set; get; }
        public string url { set; get; }
        public List<Xiang> xiangs = new List<Xiang>();
    }

    public class Xiang
    {
        public string name { set; get; }
        public string code { set; get; }
        public string url { set; get; }
        public List<Cun> cuns = new List<Cun>();
    }

    public class Cun
    {
        public string name { set; get; }
        public string code { set; get; }
    }
}
