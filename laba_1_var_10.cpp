#include "stdafx.h"
#include "iostream"
#include "iomanip"
#include "stdlib.h"
#include "locale.h"
#include "time.h"
using namespace std;

class INTMAS
{
	int N;
	int *mas;
public:
	INTMAS(int n, int a)
	{
		N = n;
		mas = new int[N];
		for (int i = 0; i < N; i++) mas[i] = rand() % a;
	}
	void myprint();
	void otbor();
	int count();
	~INTMAS()
	{
		delete[] mas;
	}
};

void INTMAS::myprint()
{
	cout << endl;
	for (int i = 0; i < N; i++) cout << setw(3) << mas[i];
	cout << endl;
}
void INTMAS::otbor()
{
	for (int i = 0; i < N; i++) {
		if (mas[i] % 2 == 0) {
			for (int j = i; j < N - 1; j++) {
				mas[j] = mas[j + 1];
			}
			N--;
			i--;
		}

	}
}
int INTMAS::count() {
	int k = 0;
	for (int i = 0; i < N; i++) {
		int c = 0;
		while (mas[i] > 0) {
			c += mas[i] % 10;
			mas[i] = mas[i] / 10;
		}
		if (c < 8) {
			k += 1;
		}
	}
	return k;
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));
	cout << "Объект 1" << endl;
	INTMAS m1(10, 50);
	m1.myprint();
	m1.otbor();
	cout << "Объект 1 без четных чисел" << endl;
	m1.myprint();
	int r = m1.count();
	cout << "количество чисел, сумма разрядов у которых меньше 8" << endl;
	cout << r << endl;
	INTMAS m1(10, 100);
	m1.myprint();
	m1.otbor();
	cout << "Объект 2 без четных чисел" << endl;
	m1.myprint();
	int r = m1.count();
	cout << "количество чисел, сумма разрядов у которых меньше 8" << endl;
	cout << r << endl;
	INTMAS m1(10, 50);
	m1.myprint();
	m1.otbor();
	cout << "Объект 3 без четных чисел" << endl;
	m1.myprint();
	int r = m1.count();
	cout << "количество чисел, сумма разрядов у которых меньше 8" << endl;
	cout << r << endl;

	system("pause");
	return 0;
}

