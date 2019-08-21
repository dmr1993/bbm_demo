 
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using EarmarkProduceTerminalBLL;

namespace LKT5103_Test
{
    

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
            button1.Enabled = true;
            this.button1.BackgroundImage = global::LKT5103_Test.Properties.Resources.OK_R;
            this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom; 

            button3.Enabled = false;
            this.button3.BackgroundImage = global::LKT5103_Test.Properties.Resources.SEN_E;
            this.button3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

            button4.Enabled = false;
            this.button4.BackgroundImage = global::LKT5103_Test.Properties.Resources.ER_E;
            this.button4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

            button5.Enabled = false;
            this.button5.BackgroundImage = global::LKT5103_Test.Properties.Resources.RST_E;
            this.button5.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

            button6.Enabled = false;
            this.button6.BackgroundImage = global::LKT5103_Test.Properties.Resources.CLR_E;
            this.button6.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

        }

        private void button1_Click(object sender, EventArgs e)
        {
            LCS_Reader lcs_Reader  = new LCS_Reader();


            if (lcs_Reader.ConnectReader() == 1)
            {
                button1.Enabled = false;
                this.button1.BackgroundImage = global::LKT5103_Test.Properties.Resources.OK_E;
                this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

                button3.Enabled = true;
                this.button3.BackgroundImage = global::LKT5103_Test.Properties.Resources.SEN_R;
                this.button3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

                button4.Enabled = true;
                this.button4.BackgroundImage = global::LKT5103_Test.Properties.Resources.ER_R;
                this.button4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

                button5.Enabled = true;
                this.button5.BackgroundImage = global::LKT5103_Test.Properties.Resources.RST_R;
                this.button5.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

                button6.Enabled = true;
                this.button6.BackgroundImage = global::LKT5103_Test.Properties.Resources.CLR_R;
                this.button6.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;


            }
            else
            {
                Set_E();
            }
           
        }             

        private void  button3_Click(object sender, EventArgs e)
        {
            LCS_Reader lcs_Reader = new LCS_Reader();
            string Sendcmd = null;
            int r;
            Sendcmd = textBox1.Text;  //读取输入数据的内容
            if (Sendcmd == "")
                listBox2.Items.Add("Please input APDU !");
            else
            {
                string strtemp = "";                             //去掉空格
                for (int i = 0; i < Sendcmd.Length; i++)
                    if (Sendcmd[i] != ' ')
                        strtemp += Sendcmd[i].ToString();
                byte[] temp = new byte[256];
                int Send_lenth = 0x00;
                Send_lenth = lcs_Reader.Ascii2Hex(strtemp, temp);   //获取strtemp即APDU指令长度
                byte[] cmd = new byte[256];
                Array.Copy(temp, 0, cmd, 0, Send_lenth);

                int CmdLen;
                int[] reslen = new int[2];
                byte[] res = new byte[256];
                CmdLen = Send_lenth;//Send_lenth;
                byte[] res_hex = new byte[256];
                r = lcs_Reader.SendCommand(CmdLen, cmd, res, reslen);   //发送APDU指令
                if (0 != r)
                {
                    listBox2.Items.Add("Send APDU failed，the res is： " + r);
                }
                else
                {
                    byte[] v_res = new byte[reslen[0] + reslen[1]];
                    Array.Copy(res, 0, v_res, 0, reslen[0] + reslen[1]);
                    string str = " ";
                    str = lcs_Reader.Hex2Ascii(v_res);
                    listBox2.Items.Add("-> " + Sendcmd);
                    listBox2.Items.Add("<- " + str);
                    listBox2.SetSelected(listBox2.Items.Count - 1, true);
                }
            } 
        }

        private void button5_Click(object sender, EventArgs e)
        {
            LCS_Reader lcs_Reader = new LCS_Reader();
            byte[] temp = new byte[256];
            int Read_lenth = 0;
            int res;
            res = lcs_Reader.ConnectReader();   //每次复位的时候都先做连接操作
            if ( res!= 1)
                listBox2.Items.Add("***********Please connect LKT5103***********");
            else
            {
                Read_lenth = lcs_Reader.ResetReader(temp);  //进行复位操作
                if (Read_lenth != 0x00)
                {
                    byte[] Read = new byte[Read_lenth];
                    Array.Copy(temp, 0, Read, 0, Read_lenth);
                    string str = " ";
                    str = lcs_Reader.Hex2Ascii(Read);
                    listBox2.Items.Add("<- " + str);
                }
                else
                {
                    Set_E();
                    listBox2.Items.Add("***********Rest Error***********");
                }
            }
         }


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            int res;
            LCS_Reader lcs_Reader = new LCS_Reader();

            res = lcs_Reader.DisConnect();//进行断开连接操作
            if (0 != res)
            {
                listBox2.Items.Add("************Has been disconnected !***********");
            }
            else
            listBox2.Items.Add("************Successful disconnected !***********");
        }
        private void Set_E() 
        {
             button1.Enabled = false;
             this.button1.BackgroundImage = global::LKT5103_Test.Properties.Resources.OK_E;
             this.button1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

             button3.Enabled = false;
             this.button3.BackgroundImage = global::LKT5103_Test.Properties.Resources.SEN_E;
             this.button3.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

             button4.Enabled = false;
             this.button4.BackgroundImage = global::LKT5103_Test.Properties.Resources.ER_E;
             this.button4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

             button5.Enabled = false;
             this.button5.BackgroundImage = global::LKT5103_Test.Properties.Resources.RST_E;
             this.button5.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;

             button6.Enabled = false;
             this.button6.BackgroundImage = global::LKT5103_Test.Properties.Resources.CLR_E;
             this.button6.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
        }



        private void button6_Click(object sender, EventArgs e)
        {
            listBox2.Items.Clear();
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void listBox2_SelectedIndexChanged_1(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }



    }
}