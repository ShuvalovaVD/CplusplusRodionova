// Лаба 2 Вариант 10

/*
Вариант 10. Kласс mas_random дополнительно должен реализовать следующие операции:
(search) поиск количества элементов масива меньше 50;
(insert) включение нового элемента в начало массив;
(delete) удаление первого элемента из массива;
Дополнительно переопределите следующий оператор:
(оператор+) нахождение суммы двух массивов.
Объявите, какие можно, функции дружественными.
Программа должна выполнить данные операции с несколькими объектами. Результаты всех операций вывести
*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

using namespace std;

class INTMAS {
private:
	int N;
	int* mas;
public:
	INTMAS(int n, int a) {
		N = n;
		mas = new int[N];
		for (int i = 0; i < N; i++) mas[i] = rand() % (a + 1);
	}
	void myprint() {
		cout << endl;
		for (int i = 0; i < N; i++) cout << setw(4) << mas[i];
		cout << endl;
	}
	void otbor() {
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
	int count() {
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
	void delete_first_elem() {
		for (int i = 0; i < N; ++i) {
			mas[i] = mas[i + 1];
		}
		N--;
	}
	void insert_first_elem(int a) {
		int* mas_tmp = new int[N + 1];
		mas_tmp[0] = a;
		for (int i = 1; i <= N; ++i) {
			mas_tmp[i] = mas[i - 1];
		}
		delete[] mas;
		mas = &mas_tmp[0];
		N++;
	}
	~INTMAS() {
		delete[] mas;
	}
	friend int search(INTMAS& m);
};

int search(INTMAS& m) {
	int cnt = 0;
	for (int i = 0; i < m.N; ++i) {
		if (m.mas[i] < 50) {
			cnt++;
		}
	}
	return cnt;
}


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	INTMAS m1(5, 70);
	cout << "Объект 1:\n";
	m1.myprint();
	cout << "Удаляем 1-ый:\n";
	m1.delete_first_elem();
	m1.myprint();
	cout << "Вставляем 1-ый =15:\n";
	m1.insert_first_elem(15);
	m1.myprint();
	cout << "Кол-во элем < 50:\n";
	cout << search(m1) << "\n";

	cout << "\n";

	INTMAS m2(7, 100);
	cout << "Объект 2:\n";
	m2.myprint();
	cout << "Удаляем 1-ый:\n";
	m2.delete_first_elem();
	m2.myprint();
	cout << "Вставляем 1-ый =67:\n";
	m2.insert_first_elem(67);
	m2.myprint();
	cout << "Кол-во элем < 50:\n";
	cout << search(m2) << "\n";

	cout << "\n";

	INTMAS m3(3, 130);
	cout << "Объект 3:\n";
	m3.myprint();
	cout << "Удаляем 1-ый:\n";
	m3.delete_first_elem();
	m3.myprint();
	cout << "Вставляем 1-ый =80:\n";
	m3.insert_first_elem(80);
	m3.myprint();
	cout << "Кол-во элем < 50:\n";
	cout << search(m3) << "\n";


	system("pause");
	return 0;
}
