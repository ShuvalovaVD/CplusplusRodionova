using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            long a, b;
            a = Int64.MinValue;
            b = Int64.MaxValue;
            label2.Text = "min = " + Convert.ToString(a);
            label3.Text = "max = " + Convert.ToString(b);
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            ushort a, b;
            a = UInt16.MinValue;
            b = UInt16.MaxValue;
            label6.Text = "min = " + Convert.ToString(a);
            label7.Text = "max = " + Convert.ToString(b);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            float a, b;
            a = Single.MinValue;
            b = Single.MaxValue;
            label9.Text = "min = " + Convert.ToString(a);
            label10.Text = "max = " + Convert.ToString(b);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            double a, b;
            a = Double.MinValue;
            b = Double.MaxValue;
            label12.Text = "min = " + Convert.ToString(a);
            label13.Text = "max = " + Convert.ToString(b);
        }
    }
}
