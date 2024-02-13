// Лаба 1 Вариант 10

/*
	Опишите класс для формирования массива случайных целых чисел в заданном количестве и с заданным распределением.
	Функция отбора должна «отфильтровать» (т. е. удалять из массива) все четные числа. 
	Общий интерфейс класса может выглядеть так: 
class mas_random
{int *pmas // описание указателя на массив 
   int N, D; // переменные для хранения размера массива чисел и диапазона
//…
public:
	mas_random (int, int);
void print( );
void otbor();
int count( );
void print( );
};
Конструктор mas_random:: mas_random ( ) имеет два параметра - целых числа. 
Первое число задает количество чисел в массиве, второе – максимальное число для диапазона генерации 
(например, mas_random(10,50) означает что генерируется 10 чисел в диапазоне от 0 до 50).  
Конструктор переписывает данные в массив целых чисел.
Функция mas_random:: count ( )  возвращающая количество чисел, сумма разрядов у которых меньше 8. 
Функция mas_random::print( ) выводит на экран элементы массива.
Примеры описания объекта и вызова методов класса  приведены ниже
mas_random x( 20, 100); //вызов конструктора
 x.count( ); //подсчет количество чисел, сумма разрядов у которых меньше 8
x.print( ); // вывод массива на экран
Программа должна выполнить работу с тремя различными объектами.
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
	~INTMAS() {
		delete[] mas;
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	cout << "Объект 1" << endl;
	INTMAS m1(10, 50);
	m1.myprint();
	m1.otbor();
	cout << "Объект 1 без четных чисел" << endl;
	m1.myprint();
	int r1 = m1.count();
	cout << "количество чисел, сумма разрядов у которых меньше 8" << endl;
	cout << r1 << endl;

	INTMAS m2(10, 100);
	m2.myprint();
	m2.otbor();
	cout << "Объект 2 без четных чисел" << endl;
	m2.myprint();
	int r2 = m2.count();
	cout << "количество чисел, сумма разрядов у которых меньше 8" << endl;
	cout << r2 << endl;

	INTMAS m3(10, 50);
	m3.myprint();
	m3.otbor();
	cout << "Объект 3 без четных чисел" << endl;
	m3.myprint();
	int r3 = m3.count();
	cout << "количество чисел, сумма разрядов у которых меньше 8" << endl;
	cout << r3 << endl;

	system("pause");
	return 0;
}
