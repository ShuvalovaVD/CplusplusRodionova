using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            listBox1.Hide();
            label2.Hide();
            label3.Hide();
            label4.Hide();
            listBox2.Hide();
            label7.Hide();
            listBox3.Hide();
        }

        // прописываем переменные на глобальном уровне
        int N;  // размер массива
        int[] mas;  // массив: пока не знаем, сколько будет элементов

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox1.Hide();
            listBox1.Items.Clear();
            label2.Hide();
            label3.Hide();
            label4.Hide();
            listBox2.Hide();
            listBox2.Items.Clear();
            label7.Hide();
            listBox3.Hide();
            listBox3.Items.Clear();
            try
            {
                N = Convert.ToInt32(textBox1.Text);
                mas = new int[N];  // теперь выделяем память под N элементов
            }
            catch (FormatException)
            {
                MessageBox.Show("Вы ввели не число");
            }
            catch (OverflowException)
            {
                MessageBox.Show("Число должно быть положительным");
            }
            Random rnd = new Random();  // создаём экземпляр класса Random
            for (int i = 0; i < N; ++i)
            {
                mas[i] = rnd.Next(100);  // 0 - 100
                listBox1.Items.Add(mas[i]);
            }
            listBox1.Show();
        }
        public void mysum()
        {
            int s = 0;
            for (int i = 0; i < N; ++i)
            {
                s += mas[i];
            }
            label2.Text = "Сумма элементов=" + Convert.ToString(s);

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            mysum();
            label2.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            listBox2.Items.Clear();
            try
            {
                int mx = mas[0];
                int mx_ind = 0;
                for (int i = 0; i < N; ++i)
                {
                    if (mas[i] > mx)
                    {
                        mx = mas[i];
                        mx_ind = i;
                    }
                }
                label3.Text = "Максимум=" + Convert.ToString(mx);
                label3.Show();
                label4.Show();

                int[] mas_mx = new int[N];
                mas_mx[0] = mx;
                listBox2.Items.Add(mas_mx[0]);
                for (int i = 1; i < N; ++i)
                {
                    if (i == mx_ind)
                    {
                        mas_mx[i] = mas[0];
                    }
                    else
                    {
                        mas_mx[i] = mas[i];
                    }
                    listBox2.Items.Add(mas_mx[i]);
                }
            }
            catch (System.NullReferenceException)
            {
                MessageBox.Show("Массив не был сформирован");
            }
            
            listBox2.Show();
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox3.Items.Clear();
            try
            {
                int ind_del = Convert.ToInt32(textBox2.Text);
                int[] mas_del = new int[N - 1];
                int j = 0;
                for (int i = 0; i < N; ++i)
                {
                    if (i != ind_del)
                    {
                        mas_del[j] = mas[i];
                        listBox3.Items.Add(mas_del[j]);
                        j++;
                    }
                }
            }
            catch (System.IndexOutOfRangeException)
            {
                MessageBox.Show("Вы индекс вне размеров массива");
            }
            catch (System.FormatException)
            {
                MessageBox.Show("Вы ввели не число");
            }
            catch (System.OverflowException)
            {
                MessageBox.Show("Массив не был сформирован");
            }
            listBox3.Show();
        }
    }
}
