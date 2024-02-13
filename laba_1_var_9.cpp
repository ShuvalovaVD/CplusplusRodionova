// Лаба 1 Вариант 9

/*
Опишите класс для формирования массива случайных целых чисел в заданном количестве и с заданным распределением.
Функция отбора должна «отфильтровать» (т. е. удалять из массива) все нечетные числа.
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
Конструктор переписывает данные в массив целых чисел. Функция mas_random:: count ( )
возвращающая количество чисел, сумма разрядов у которых больше 10. 
Функция mas_random::print( ) выводит на экран элементы массива. 
Примеры описания объекта и вызова методов класса  приведены ниже
mas_random x( 20, 100); //вызов конструктора
 x.count( ); //подсчет количество чисел, сумма разрядов у которых больше 10
x.print( ); // вывод массива на экран
Программа должна выполнить работу с тремя различными объектами.
*/

#include <iostream>
#include <iomanip>
#include <locale.h>
#include <time.h>

using namespace std;

class MAS_RANDOM {
private:
	int N;
	int* mas;
public:
	MAS_RANDOM(int n, int a) {
		N = n;
		mas = new int[N];
		for (int i = 0; i < N; i++) mas[i] = rand() % (a + 1);
	}
	void myprint() {
		cout << endl;
		for (int i = 0; i < N; i++) cout << setw(5) << mas[i];
		cout << endl;
	}
	void otbor() {
		for (int i = 0; i < N; i++) {
			if (mas[i] % 2 == 1) {  // все нечетные удаляем
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
			int x = mas[i];
			while (x > 0) {
				c += x % 10;
				x = x / 10;
			}
			if (c > 10) {  // кол-во чисел у которых сумма разрядов больше 10
				k += 1;
			}
		}
		return k;
	}
	~MAS_RANDOM(){
		delete[] mas;
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	cout << "Объект 1" << endl;
	MAS_RANDOM m1(10, 500);
	cout << "Исходный" << endl;
	m1.myprint();
	cout << m1.count() << endl;
	m1.otbor();
	cout << "После отбора" << endl;
	m1.myprint();

	cout << "Объект 2" << endl;
	MAS_RANDOM m2(5, 100);
	cout << "Исходный" << endl;
	m2.myprint();
	cout << m2.count() << endl;
	m2.otbor();
	cout << "После отбора" << endl;
	m2.myprint();

	cout << "Объект 3" << endl;
	MAS_RANDOM m3(7, 1000);
	cout << "Исходный" << endl;
	m3.myprint();
	cout << m3.count() << endl;
	m3.otbor();
	cout << "После отбора" << endl;
	m3.myprint();
	
	system("pause");
	return 0;
}
