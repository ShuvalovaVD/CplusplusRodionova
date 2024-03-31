// Лекция 4. Наследование

/*
Теория
Наследование - это повторное использование уже созданных классов. Создаём на основе существующих классов новые.
Родительский класс - базовый, дочерний - производный.
class [имя производного класса] : [право наследование] [имя базового класса]
Перед именем базового класса указывается право наследования. Право наследования влияет на право доступа к компонентам класса.
Производный класс наследует всё, что есть в базовом классе (всё, что разрешено). Не наследуются конструкторы, деструкторы и переопределённый оператор "=".

Права наследования (базовый класс -> производный класс):
public:
public -> public
protected -> protected
private -> недоступно

protected:
public -> protected
protected -> protected
private -> недоступно

private:
public -> private
protected -> private
private -> недоступно

Лучше испольщоваться наследование с правом private, предварительно в базовом классе изменив все private на protected, чтобы иметь доступ ко всем компонентам.

При создании объекта производного класса сначала вызываются конструкторы базового класса, а затем конструкторы производного класса. При разрушении объекта 
сначала вызываются деструкторы производного класса, а затем базового.
*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

using namespace std;

class INTMAS
{
protected:
	int N;
	int* mas;
public:
	INTMAS(int n)
	{
		N = n;
		mas = new int[N];
		for (int i = 0; i < N; i++) mas[i] = rand() % 100;
	}
	void myprint()
	{
		cout << endl;
		for (int i = 0; i < N; i++) cout << setw(3) << mas[i];
		cout << endl;
	}
	int search()
	{
		int mn = mas[0];
		for (int i = 1; i < N; i++) {
			if (mas[i] < mn) {
				mn = mas[i];
			}
		}
		return mn;
	}
	virtual void vir() {
		cout << "Размер массива: " << N << endl;
		cout << "Элементы массива: ";
		for (int i = 0; i < N; i++) cout << setw(3) << mas[i];
		cout << endl;
	}
	friend void delet(INTMAS& mas, int nd);
	friend void ins(INTMAS& mas, int a, int ind);
	~INTMAS()
	{
		delete[] mas;
	}
};


void delet(INTMAS& mas, int nd)
{
	nd--;
	for (int i = nd; i < mas.N - 1; i++) {
		mas.mas[i] = mas.mas[i + 1];
	}
	mas.mas[mas.N - 1] = 0;
	for (int i = 0; i < mas.N - 1; i++) cout << setw(3) << mas.mas[i];
	cout << endl;
}
void ins(INTMAS& mas, int a, int ind)
{
	int* nmas;
	nmas = new int[mas.N + 1];
	for (int i = 0; i < ind; i++) {
		nmas[i] = mas.mas[i];
	}
	nmas[ind] = a;
	for (int i = ind; i < mas.N; i++) {
		nmas[i + 1] = mas.mas[i];
	}
	for (int i = 0; i < mas.N + 1; i++) {
		cout << setw(3) << nmas[i];
	}
	cout << endl;
}


class INTMAS2 : public INTMAS {
	int summ, pr;
public:
	INTMAS2(int n) :INTMAS(n) {
		summ = 0;
		pr = 1;
	}
	void mysum() {
		for (int i = 0; i < N; i++) summ += mas[i];
		cout << "Сумма элементов массива: " << summ << endl;
	}
	void mypr() {
		for (int i = 0; i < N; i++) pr *= mas[i];
		cout << "Произведение элементов массива: " << pr << endl;
	}
	void search2()
	{
		int mx = mas[0];
		for (int i = 1; i < N; i++) {
			if (mas[i] > mx && mas[i] % 2 == 0) {
				mx = mas[i];
			}
		}
		cout << "Максимальный четный элемент массива: " << mx << endl;
	}
	void vir() {
		cout << "Элементы массива: ";
		for (int i = 0; i < N; i++) cout << setw(3) << mas[i];
		cout << endl;
		int maxx = mas[0], minn = mas[0];
		for (int i = 1; i < N; i++) {
			if (mas[i] > maxx) {
				maxx = mas[i];
			}
			if (mas[i] < minn) {
				minn = mas[i];
			}
		}
		cout << "Максимальный элемент массива: " << maxx << endl;
		cout << "Минимальный элемент массива: " << minn << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));
	cout << "Объект 1" << endl;
	INTMAS m1(10);
	m1.myprint();
	int s;
	cout << "Какой элемент удалить?  ";
	cin >> s;
	cout << "Из массива удалён элемент под номером " << s << endl;
	delet(m1, s);

	cout << "Объект 2" << endl;
	INTMAS m2(10);
	m2.myprint();
	int a, b;
	cout << "Какой элемент добавить?  ";
	cin >> a;
	cout << "На какое место?  ";
	cin >> b;
	b--;
	cout << "В массив добавлен элемент " << a << endl;
	ins(m2, a, b);

	cout << "Объект 3" << endl;
	INTMAS m3(10);
	m3.myprint();
	cout << "Минимальный элемент массива: " << m3.search() << endl;

	cout << "------------------------------------------------" << endl;

	// лабораторная 3
	INTMAS* p;

	cout << "Производный объект: " << endl;
	INTMAS2 m5(10);
	m5.myprint();
	m5.mysum();
	m5.mypr();
	p = &m5;
	cout << "Работа виртуальной функции производного объекта: " << endl;
	m5.vir();
	cout << endl;
	cout << "Базовый объект: " << endl;
	INTMAS m7(10);
	m7.myprint();
	p = &m7;
	cout << "Работа виртуальной функции базового объекта: " << endl;
	m7.vir();
	system("pause");
	return 0;
}
