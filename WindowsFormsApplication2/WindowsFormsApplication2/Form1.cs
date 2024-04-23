using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int a = Convert.ToInt32(textBox1.Text);
            int b = Convert.ToInt32(textBox2.Text);
            char op = Convert.ToChar(textBox3.Text);
            string res = "None";  // значение по умолчанию
            if (op == '+')
            {
                res = "Результат: " + Convert.ToString(a + b);
            }
            else if (op == '-')
            {
                res = "Результат: " + Convert.ToString(a - b);
            }
            else if (op == '*')
            {
                res = "Результат: " + Convert.ToString(a * b);
            }
            else
            {
                res = "Неизвестная\nоперация";
            }
            label4.Text = res;
        }
    }
}
