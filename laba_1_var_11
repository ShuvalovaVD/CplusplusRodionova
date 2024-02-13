// Лаба 1 Вариант 11

/*
Опишите класс для формирования матрицы случайных целых чисел заданной размерности (не больше чем 10х10) и с заданным распределением.
Функция otbor должна «отфильтровывать» (т. е. заменять на ноль) все четные числа. Общий интерфейс класса может выглядеть так:
class mass_random
{ int massiv[10][10]; // описание матрицы для хранения целых чисел
   int N,M; // переменные для хранения размера матрицы чисел
//…
public:
	mass_random (int, int, int);
	int count( );
void otbor( );
void print( );
};
Конструктор mass_random:: mass_random ( ) имеет три параметра - целых числа.
Первые два числа задают количество строк и столбцов в массиве, третье – максимальное число для диапазона генерации 
(например, mass_random(5,5,50) означает что генерируется матрица размером 5 на 5 с диапазоном значений от 0 до 50). 
Конструктор переписывает данные в матрицу целых чисел. Функция mass_random:: count ( )  возвращающая количество строк в матрице у которых сумма больше 100. 
Функция mas_random::print( ) выводит на экран элементы массива. Примеры описания объекта и вызова методов класса  приведены ниже
matr_random x( 5, 5, 100); //вызов конструктора
 x.count( ); // вызов метода для подсчета количества строк с суммой больше 100
x.print( );  // вызов метода для вывода матрицы на экран
Программа должна выполнить работу с тремя различными объектами.
*/

#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>

using namespace std;

class MASS_RANDOM {  // класс
private:
	int N, M;  // размеры матрицы
	int massiv[10][10];  // матрица (max - 10x10)
public:
	MASS_RANDOM(int n, int m, int k) {
		N = n;
		M = m;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				massiv[i][j] = rand() % (k + 1);  // 0 - k
			}
		}
	}
	void otbor() {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (massiv[i][j] % 2 == 0) {  // четные элементы заменяем на ноль
					massiv[i][j] = 0;
				}
			}
		}
	}
	int count() {  // считаем кол-во строк, в к-рых сумма элементов больше 100
		int cnt = 0;
		for (int i = 0; i < N; ++i) {
			int s = 0;
			for (int j = 0; j < M; ++j) {
				s += massiv[i][j];
			}
			if (s > 100) {
				cnt++;
			}
		}
		return cnt;
	}
	void print() {
		cout << endl;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cout << setw(5) << massiv[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	~MASS_RANDOM() {  // деструктор
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				massiv[i][j] = 0;
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	MASS_RANDOM matrix1(10, 10, 50);
	cout << "Матрица 1\n";
	matrix1.print();
	cout << matrix1.count() << endl;
	matrix1.otbor();
	matrix1.print();

	MASS_RANDOM matrix2(3, 5, 100);
	cout << "Матрица 2\n";
	matrix2.print();
	cout << matrix2.count() << endl;
	matrix2.otbor();
	matrix2.print();

	MASS_RANDOM matrix3(5, 10, 20);
	cout << "Матрица 3\n";
	matrix3.print();
	cout << matrix3.count() << endl;
	matrix3.otbor();
	matrix3.print();

	return 0;
}
