using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form3 : Form
    {
        int x = 0;
        public static Task delay;
        bool go = false;
        bool qwe = false;
        private System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
        
        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_Load(object sender, EventArgs e)
        {
            Random rand = new Random();
            string codeR = "";
            for (int i = 0; i < 4; i++)
            {
                codeR += (char)rand.Next(48, 90);
            }
            code.Text = codeR;
            ready.Hide();
            timer.Interval = 1000;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form1 form1 = new Form1();
            Hide();
            form1.Show();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            textBox1.Text.ToUpper();
            if (textBox1.Text == code.Text)
            {
                qwe = true;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (go)
            {
                if (x == 0)
                {
                    ready.Hide();
                    x = 1;
                }
                else
                {
                    ready.Show();
                    x = 0;
                }
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (checkBox1.Checked && qwe == true)
            {
                go = true;
            }
            else
            {
                go = false;
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            go = false;
            ready.Hide();
        }

        private void CH1_Click(object sender, EventArgs e)
        {
            CH1.BackColor = Color.Red;
        }

        private void CH7_Click(object sender, EventArgs e)
        {
            CH7.BackColor = Color.Red;
        }

        private void CH6_Click(object sender, EventArgs e)
        {
            CH6.BackColor = Color.Red;
        }

        private void CH11_Click(object sender, EventArgs e)
        {
            CH11.BackColor = Color.Red;
        }

        private void CH10_Click(object sender, EventArgs e)
        {
            CH10.BackColor = Color.Red;
        }

        private void CH9_Click(object sender, EventArgs e)
        {
            CH9.BackColor = Color.Red;
        }

        private void CH8_Click(object sender, EventArgs e)
        {
            CH8.BackColor = Color.Red;
        }

        private void CH5_Click(object sender, EventArgs e)
        {
            CH5.BackColor = Color.Red;
        }

        private void CH4_Click(object sender, EventArgs e)
        {
            CH4.BackColor = Color.Red;
        }

        private void CH3_Click(object sender, EventArgs e)
        {
            CH3.BackColor = Color.Red;
        }

        private void CH2_Click(object sender, EventArgs e)
        {
            CH2.BackColor = Color.Red;
        }

        private void CH12_Click(object sender, EventArgs e)
        {
            CH12.BackColor = Color.Red;
        }
    }
}
