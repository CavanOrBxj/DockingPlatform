using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LoadAeraDataTool
{
    public partial class Form1 : Form
    {

        string filepath = "";

        public static dbAccess dba;

        public Dictionary<string, string> GB_CODE_Dic;
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                txtfilename.Text = openFileDialog1.FileName;
            }
           
        }


        //获取数据库连接字符串
        private String GetConnectString()
        {
            string sReturn;
            string sPass;
            sPass = txtDbPass.Text.Trim();
            if (sPass == "")
                sPass = "tuners2012";
            sReturn = "server = " + txtServer.Text.Trim() +
                   ";UID = " + txtDbuser.Text.Trim() +
                    ";Password = " + sPass +
                     ";DataBase = " + txtDb.Text.Trim() + ";"
                     + "MultipleActiveResultSets=True";

            return sReturn;
        }

        

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                if (txtServer.Text!="" || txtDb.Text!="" || txtDbuser.Text!="" || txtDbPass.Text!="")
                {


                    dba = new dbAccess();
                    dba.conn.ConnectionString = GetConnectString();

                    if (dba.OpenConn())
                    {
                        //先判断有误表 AeraCodeNation  没有的话先创建
                        String tableNameStr = "select count(1) from sysobjects where name = 'AeraCodeNation'";

                        SqlCommand cmd = new SqlCommand(tableNameStr, dba.conn);
                        int result = Convert.ToInt32(cmd.ExecuteScalar());
                        if (result == 0)
                        {
                            //未创建  开始创建表 AeraCodeNation
                            if (dba.conn.State==ConnectionState.Open)
                            {
                                dba.conn.Close();
                            }
                            dba.OpenConn();
                            string sql222 = "CREATE TABLE AeraCodeNation([Code][varchar](50) COLLATE Chinese_PRC_CI_AS NOT NULL,[Name] [varchar] (50) COLLATE Chinese_PRC_CI_AS NULL,CONSTRAINT[PK_AeraCodeNation] PRIMARY KEY CLUSTERED([Code] ASC)WITH(IGNORE_DUP_KEY = OFF) ON[PRIMARY]) ON[PRIMARY]";
                            cmd = new SqlCommand(sql222,dba.conn);
                            cmd.ExecuteNonQuery();
                        }
                    }

                }
                else
                {
                    MessageBox.Show("数据库信息不能为空！");
                    return;
                }


                if (txtfilename.Text!="")
                {
                    string[] lines = System.IO.File.ReadAllLines(txtfilename.Text);

                    if (lines.Length>0)
                    {
                        foreach (var item in lines)
                        {
                            string[] tmp = item.Split('#');
                            string code = tmp[1];
                            string name = tmp[0];
                            string InfoValueStr = "insert into AeraCodeNation values('" + code + "','" + name + "')";
                            dba.UpdateDbBySQL(InfoValueStr);
                        }
                    }
                }
                else
                {
                    MessageBox.Show("文件名不能为空！");
                }

                MessageBox.Show("数据导入完成");
              
            }
            catch (Exception)
            {

                throw;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                if (txtServer.Text != "" || txtDb.Text != "" || txtDbuser.Text != "" || txtDbPass.Text != "")
                {


                    dba = new dbAccess();
                    dba.conn.ConnectionString = GetConnectString();

                    if (dba.OpenConn())
                    {
                        //判断表中有无数据列GB_CODE
                        string sql223 = "select* from   syscolumns where   id = object_id('Organization')   and name = 'GB_CODE'";
                        SqlCommand cmd = new SqlCommand(sql223, dba.conn);
                       object pp= cmd.ExecuteScalar();
                        if (pp == null)
                        {
                            //没有数据列，往表中Organization插入列 GB_CODE
                            string SQL11 = "ALTER TABLE Organization ADD GB_CODE [varchar](255) COLLATE Chinese_PRC_CI_AS NULL";
                            cmd = new SqlCommand(SQL11, dba.conn);
                            cmd.ExecuteNonQuery();
                        }
                        else
                        {
                            //已经有数据列
                            Console.WriteLine("GB_CODE已经存在");
                        }
                    }

                }
                else
                {
                    MessageBox.Show("数据库信息不能为空！");
                    return;
                }


                if (txtfilename.Text != "")
                {
                    string[] lines = System.IO.File.ReadAllLines(txtfilename.Text);

                  string   MediaSql = "select  ORG_ID,ORG_DETAIL,ORG_CODEA from Organization";
                   DataTable dtMedia = dba.getQueryInfoBySQL(MediaSql);


                    if (lines.Length > 0)
                    {
                        foreach (var item in lines)
                        {
                            string[] tmp = item.Split('#');
                            string code = tmp[1];
                            string name = tmp[0].Trim();
                            string selectString = "";
                            if (code.Substring(2, 10) == "0000000000" || code.Substring(4, 8) == "00000000")
                            {
                                //省或者市
                                selectString = string.Format("ORG_DETAIL='{0}'", name);
                            }
                            else
                            {
                                string tunerscode = "P" + code .Substring(0,2)+ "Q"+ code.Substring(2,2) + "C"+ code.Substring(4,2);
                                selectString = string.Format("ORG_DETAIL='{0}' and ORG_CODEA like '{1}%'", name, tunerscode);
                            }

                           

                         
                            DataRow[] dr = dtMedia.Select(selectString);
                            if (dr!=null && dr.Length>0)
                            {
                                if (dr.Length == 1)
                                {
                                    string InfoValueStr = "UPDATE Organization set GB_CODE ='" + code + "' where ORG_ID='" + dr[0][0].ToString() + "'";
                                    dba.UpdateDbBySQL(InfoValueStr);
                                }
                            }
                           
                        }
                    }
                }
                else
                {
                    MessageBox.Show("文件名不能为空！");
                }

                MessageBox.Show("数据导入完成");

            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.ToString());
            }
        }
    }
}
