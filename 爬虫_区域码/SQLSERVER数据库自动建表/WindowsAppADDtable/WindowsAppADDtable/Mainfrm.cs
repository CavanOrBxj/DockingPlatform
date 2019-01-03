using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Configuration;
using System.Collections;
using System.Xml;
using System.IO;
using System.Data.SqlClient;
using System.Data.Sql;
using System.Runtime.InteropServices;
using System.Reflection;

namespace WindowsAppADDtable
{
    public partial class Mainfrm : Form
    {
        public Mainfrm()
        {
            InitializeComponent();
        }

        #region 事件集合
        public OpenFileDialog openfiledialog;
        private void btn_liulan_Click(object sender, EventArgs e)
        {
            System.Windows.Forms.OpenFileDialog folder = new OpenFileDialog();
            folder.Filter = "文本文件(*.txt)|*.txt|doc(*.doc) |*.doc";
            string path = "";
            if (folder.ShowDialog() == DialogResult.OK)
            {
                txt_wblj.Text = folder.FileName;
            }
        }
        List<string> lstYSZD = null;
        private void btn_load_Click(object sender, EventArgs e)
        {
            lstbYSzd.Items.Clear();
            if (txt_wblj.Text.Trim() != "")
            {

                lstYSZD = new List<string>();
                System.IO.StreamReader M_streamRead = new System.IO.StreamReader(this.txt_wblj.Text.Trim(), System.Text.Encoding.Default);
                string strLine = M_streamRead.ReadLine();
                while (strLine != null)
                {
                    lstbYSzd.Items.Add(strLine);
                    lstYSZD.Add(strLine.Trim());
                    strLine = M_streamRead.ReadLine();
                }
            }
            else
            {
                MessageBox.Show("加载文本路径不能为空");
            }
        }
        string Table = "";
        List<string> BZD = null;
        List<string> BZBZd = null;
        private void btn_zh_Click(object sender, EventArgs e)
        {
            if (lstbYSzd.Items.Count != 0)
            {
                lstBZD.Items.Clear();
                Table = WindowsAppADDtable.Utils.StringUtils.GetPinYinCode(textBox1.Text.Trim()).ToLower().Trim();
                BZD = new List<string>();
                foreach (string ss in lstYSZD)
                {
                    BZD.Add(WindowsAppADDtable.Utils.StringUtils.GetPinYinCode(ss.Trim()).ToLower().Trim());
                }
                BZBZd = BZD;
                int bbjj = 0;
                string Frist = "";
                for (int ss = 1; ss < BZBZd.Count; ss++)
                {
                    Frist = BZBZd[ss].Trim();

                    for (int bb = 0; bb < ss; bb++)
                    {
                        if (Frist == BZBZd[bb].Trim())
                        {
                            bbjj++;
                        }
                    }
                    if (bbjj != 0)
                    {
                        BZD[ss] = Frist + bbjj.ToString().Trim();
                    }
                }
                foreach (string ss in BZD)
                {
                    lstBZD.Items.Add(WindowsAppADDtable.Utils.StringUtils.GetPinYinCode(textBox1.Text.Trim()).ToLower().Trim() + "_" + ss);
                }
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ss = GetLocalSqlServerNamesWithSqlClientFactory();
            for (int a = 0; a < ss.Length; a++)
            {
                cmbDataServices.Items.Add(ss[a].ToString().Trim());
            }
        }

        private void txtUser_TextChanged(object sender, EventArgs e)
        {
            if (txtUser.Text.Trim() != "")
            {
                txtUserPass.Enabled = true;
            }
            if (txtUser.Text.Trim() == "")
            {
                txtUserPass.Enabled = false;
                txtUserPass.Text = "";
            }
        }

        private void txtUserPass_TextChanged(object sender, EventArgs e)
        {
            if (txtUserPass.Text.Trim() != "")
            {
                cmbDataBase.Enabled = true;
            }
            if (txtUserPass.Text.Trim() == "")
            {
                cmbDataBase.Enabled = false;
                cmbDataBase.Text = "";
                cmbDataBase.Items.Clear();
            }
        }

        private void cmbDataServices_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbDataServices.SelectedIndex != -1)
            {
                txtUser.Enabled = true;
            }
        }

        private void cmbDataBase_DropDown(object sender, EventArgs e)
        {
            cmbDataBase.Items.Clear();
            if (GetDbList(cmbDataServices.Text.Trim(), txtUser.Text.Trim(), txtUserPass.Text.Trim()).Count != 0)
            {
                for (int b = 0; b < GetDbList(cmbDataServices.Text.Trim(), txtUser.Text.Trim(), txtUserPass.Text.Trim()).Count; b++)
                {
                    cmbDataBase.Items.Add(GetDbList(cmbDataServices.Text.Trim(), txtUser.Text.Trim(), txtUserPass.Text.Trim())[b].ToString().Trim());
                }
            }
        }

        private void btn_close_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void btn_creatTable_Click(object sender, EventArgs e)
        {
            if (lstBZD.Items.Count == 0)
            {
                MessageBox.Show("表字段不能为空值集合");
            }
            else if (textBox1.Text.Trim() == "")
            {
                MessageBox.Show("数据库地址配置信息录入不全");
            }
            else
            {
                SqlConnection conn = new SqlConnection("Data Source=" + cmbDataServices.Text.Trim() + ";Initial Catalog=" + cmbDataBase.Text.Trim() + ";User ID=" + txtUser.Text.Trim() + ";Password=" + txtUserPass.Text.Trim());
                conn.Open();
                SqlCommand comm = new SqlCommand();

                comm.Connection = conn;
                string StrCmd = "CREATE TABLE " + Table.Trim() + "(" + Table + "_ID" + " int IDENTITY (1,1) PRIMARY KEY,";
                int s = 1;
                for (int i = 1; i < lstBZD.Items.Count; i++)
                {
                    ++s;
                    if (s != BZD.Count)
                    {
                        StrCmd = StrCmd + lstBZD.Items[i].ToString().Trim() + " varchar(50) ,";
                    }
                    else
                    {
                        StrCmd = StrCmd + lstBZD.Items[i].ToString().Trim() + " varchar(50) ";
                    }

                }

                StrCmd += ")";

                comm.CommandText = StrCmd;

                comm.ExecuteNonQuery();
                MessageBox.Show("添加表成功！！！");

            }
        }

        private void cmbDataBase_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cmbDataBase.Text.Trim() == "")
            {
                textBox1.Enabled = false;
                textBox1.Text = "";
            }
            else
            {
                textBox1.Enabled = true;
            }
        }
        #endregion

        #region 供使用API方式时使用
        [System.Runtime.InteropServices.DllImport("odbc32.dll")]
        private static extern short SQLAllocHandle(short hType, IntPtr inputHandle, out IntPtr outputHandle);

        [System.Runtime.InteropServices.DllImport("odbc32.dll")]
        private static extern short SQLSetEnvAttr(IntPtr henv, int attribute, IntPtr valuePtr, int strLength);

        [System.Runtime.InteropServices.DllImport("odbc32.dll")]
        private static extern short SQLFreeHandle(short hType, IntPtr handle);

        [System.Runtime.InteropServices.DllImport("odbc32.dll", CharSet = System.Runtime.InteropServices.CharSet.Ansi)]

        private static extern short SQLBrowseConnect(IntPtr hconn, System.Text.StringBuilder inString,
            short inStringLength, System.Text.StringBuilder outString, short outStringLength,
            out short outLengthNeeded);

        private const short SQL_HANDLE_ENV = 1;
        private const short SQL_HANDLE_DBC = 2;
        private const int SQL_ATTR_ODBC_VERSION = 200;
        private const int SQL_OV_ODBC3 = 3;
        private const short SQL_SUCCESS = 0;
        private const short SQL_NEED_DATA = 99;
        private const short DEFAULT_RESULT_SIZE = 1024;

        private const string SQL_DRIVER_STR = "DRIVER=SQL SERVER";

        #endregion

        #region 取得指定数据库服务器的数据库列表
        //取得指定数据库服务器的数据库列表   
        public ArrayList GetDbList(string strServerName, string strUserName, string strPwd)
        {


            ArrayList alDbs = new ArrayList();
            SQLDMO.Application sqlApp = new SQLDMO.ApplicationClass();
            SQLDMO.SQLServer svr = new SQLDMO.SQLServerClass();

            try
            {
                svr.Connect(strServerName, strUserName, strPwd);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString().Trim());
                return alDbs;
            }

            foreach (SQLDMO.Database db in svr.Databases)
            {
                if (db.Name != null)
                {
                    alDbs.Add(db.Name);
                }
            }
            svr.DisConnect();
            sqlApp.Quit();
            return alDbs;
        }
                #endregion

        #region 获取网内的数据库服务器名称以及获取局域网内的所有数据库服务器名称
        /// <summary>
        /// 获取网内的数据库服务器名称
        /// </summary>
        /// <returns>服务器名称数组</returns>
        public static string[] GetLocalSqlServerNamesWithAPI()
        {
            string list = string.Empty;
            IntPtr henv = IntPtr.Zero;
            IntPtr hconn = IntPtr.Zero;
            System.Text.StringBuilder inString = new System.Text.StringBuilder(SQL_DRIVER_STR);
            System.Text.StringBuilder outString = new System.Text.StringBuilder(DEFAULT_RESULT_SIZE);
            short inStringLength = (short)inString.Length;
            short lenNeeded = 0;
            try
            {
                if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_ENV, henv, out henv))
                {
                    if (SQL_SUCCESS == SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (IntPtr)SQL_OV_ODBC3, 0))
                    {
                        if (SQL_SUCCESS == SQLAllocHandle(SQL_HANDLE_DBC, henv, out hconn))
                        {

                            if (SQL_NEED_DATA == SQLBrowseConnect(hconn, inString, inStringLength, outString,
                                 DEFAULT_RESULT_SIZE, out lenNeeded))
                            {
                                if (DEFAULT_RESULT_SIZE < lenNeeded)
                                {
                                    outString.Capacity = lenNeeded;
                                    if (SQL_NEED_DATA != SQLBrowseConnect(hconn, inString, inStringLength, outString,
                                         lenNeeded, out lenNeeded))
                                    {
                                        throw new ApplicationException("Unabled to aquire SQL Servers from ODBC driver.");
                                    }
                                }
                                list = outString.ToString();
                                int start = list.IndexOf("{") ;
                                int len = list.IndexOf("}") - start;
                                if ((start > 0) && (len > 0))
                                {
                                    list = list.Substring(start, len);
                                }
                                else
                                {
                                    list = string.Empty;
                                }
                            }
                        }
                    }
                }
            }
            catch
            {
                list = string.Empty;
            }

            finally
            {
                if (hconn != IntPtr.Zero)
                {
                    SQLFreeHandle(SQL_HANDLE_DBC, hconn);
                }

                if (henv != IntPtr.Zero)
                {
                    SQLFreeHandle(SQL_HANDLE_ENV, hconn);
                }
            }

            string[] array = null;

            if (list.Length > 0)
            {

                array = list.Split(',');

            }
            return array;
        }

        /// <summary>
        /// 获取局域网内的所有数据库服务器名称
        /// </summary>
        /// <returns>服务器名称数组</returns>
        public static string[] GetLocalSqlServerNamesWithSqlClientFactory()
        {
            DataTable dataSources = SqlClientFactory.Instance.CreateDataSourceEnumerator().GetDataSources();
            DataColumn column2 = dataSources.Columns["ServerName"];
            DataColumn column = dataSources.Columns["InstanceName"];
            DataRowCollection rows = dataSources.Rows;
            string[] array = new string[rows.Count];
            for (int i = 0; i < array.Length; i++ )
            {
                string str2 = rows[i][column2] as string;
                string str = rows[i][column] as string;
                if (((str == null) || (str.Length == 0)) || ("MSSQLSERVER" == str))
                {
                    array[i] = str2;
                }
                else
                {
                    array[i] = str2 + @"\" + str;
                }
            }
            Array.Sort<string>(array);
            
            return array;
        }
        #endregion
    }
}