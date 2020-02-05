using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace WindowsFormsApp1  
{
    public partial class Form1 : Form
    {
        DateTime date = new DateTime();
        private SerialPort myports;
        string[] ports = SerialPort.GetPortNames();
        List<Label> names = new List<Label>();
        Form2 aboutUs = new Form2();
        public int time = 1000;
        
        
        public Form1()
        {
            
            InitializeComponent();
            execute();
            timer1.Start();

            
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }

        private void execute()
        {
            names.Add(label1);
            names.Add(label2);
            names.Add(label3);
            names.Add(label4);
            for (int i = 0; i < ports.Length; i++)
            {
                //names[i].Text = ports[i];
                //string portq = ports[i];
                comboBox1.Items.Add(ports[i]);
            }
                
                
            myports = new SerialPort();
            myports.BaudRate = 9600;
            myports.PortName = "C";
            
            
        }

        private void label2_Click(object sender, EventArgs e)
        {
            myports.PortName = label2.Text;
            label5.Text = label2.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label8.Text = "";
            try
            {
                myports.Open();
                myports.WriteLine("t");
                myports.Close();
            }
            catch(Exception x)
            {
                label8.Text = x.Message;
            }
            

        }
        
        private void label1_Click(object sender, EventArgs e)
        {
            myports.PortName = label1.Text;
            label5.Text = label1.Text;
        }

        private void label3_Click(object sender, EventArgs e)
        {
            myports.PortName = label3.Text;
            label5.Text = label3.Text;
        }

        private void label4_Click(object sender, EventArgs e)
        {
            myports.PortName = label4.Text;
            label5.Text = label4.Text;
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            myports.PortName = comboBox1.Text;
            label5.Text = comboBox1.Text;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();

            for (int i = 0; i < ports.Length; i++)
            {
                comboBox1.Items.Add(ports[i]);
            }
            ports = SerialPort.GetPortNames();
        }

       

        private void timer1_Tick(object sender, EventArgs e)
        {
            DateTime date = DateTime.Now;
            this.label6.Text = date.ToString();
        }


        private void button3_Click(object sender, EventArgs e)
        {
            //m.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            Hide();
            form2.Show();
        }

        private void button14_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("6");
                myports.Close();
            }
            catch(Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("7");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH1_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("0");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH2_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("1");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH3_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("2");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH4_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("3");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH5_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("4");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH6_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("5");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH9_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("!");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH10_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("@");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH11_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("#");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH12_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("$");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void ALL_Click(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("&");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void textBox1_Click(object sender, EventArgs e)
        {
            
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            //time = Convert.ToInt32(textBox1.Text);
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                try
                {
                    label13.ForeColor = Color.Red;
                }
                catch(Exception)
                {

                }
            }
            if (!checkBox1.Checked)
            {
                try
                {
                    label13.ForeColor = Color.White;
                }
                catch(Exception)
                {

                }
            }
        }

        private void checkBox1_CheckStateChanged(object sender, EventArgs e)
        {
            //label13.ForeColor = Color.White;
        }

        private void checkBox1_KeyDown(object sender, KeyEventArgs e)
        {
            //label13.ForeColor = Color.Red;
        }

        private void button3_Click_2(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                Form3 form3 = new Form3();
                Hide();
                form3.Show();
            }
        }

        private void CH4_Click_1(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("3");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH5_Click_1(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("4");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void CH6_Click_1(object sender, EventArgs e)
        {
            try
            {
                label8.Text = "";
                myports.Open();
                myports.WriteLine("5");
                myports.Close();
            }
            catch (Exception k)
            {
                label8.Text = k.Message;
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            myports.Open();
            myports.WriteLine("B");
            myports.Close();
        }
    }

}
