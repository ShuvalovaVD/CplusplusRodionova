// Лаба 1 Вариант 11

/*
Опишите класс для формирования матрицы случайных целых чисел заданной размерности (не больше чем 10х10) 
и с заданным распределением. Функция otbor должна «отфильтровывать» (т. е. заменять на ноль) все четные числа.
Общий интерфейс класса может выглядеть так:
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


// Лаба 2 Вариант 11

/*
Класс mass_random дополнительно должен реализовать следующие операции:
(search) поиск минимального элемента;
(poisk) поиск количества элементов расположенных ДО максимума;
(delete) удаление столбца из массива;
Объявите, какие можно, функции дружественными.
Дополнительно переопределите следующие операторы:
Сумма матриц – оператор +
Программа должна выполнить данные операции с несколькими объектами. Результаты всех операций вывести
*/

// Лаба 3 Вариант 11

/*
С помощью наследования создать класс mas_random2. Новый класс  дополнительно хранит сумму и произведение 
четных чисел из исходного класса. Реализовать функцию нахождения индекса минимального четного элемента.
В программу где описаны два класса (базовый и производный) добавить виртуальную функцию и ее вызовы для 
созданных объектов. Функция базового класса должна выводить исходный массив и его размер. 
Функция производного класса должна выводить на экран исходный массив, а также его максимальный и минимальный элементы.
*/


#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>

using namespace std;


class MASS_RANDOM {  // базовый класс
protected:  // право доступа private изменили на protected, чтобы при наследовании сохранился доступ
	int N, M;  // размеры матрицы (кол-во строк и столбцов)
	int massiv[10][10];  // матрица (max - 10x10)
public:
	MASS_RANDOM(int n, int m, int k) {  // конструктор создания матрицы N x M с распределением k
		N = n;
		M = m;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				massiv[i][j] = rand() % (k + 1);  // 0 - k
			}
		}
	}
	void otbor() {  // «отфильтровывает» (т.е. заменет на ноль) все четные числа
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
	void print() {  // выводит матрицу
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cout << setw(5) << massiv[i][j];
			}
			cout << endl;
		}
	}
	void delete_col(int column) {  // удаление столбца из массива
		for (int i = 0; i < N; ++i) {
			for (int j = column - 1; j < M - 1; ++j) {
				massiv[i][j] = massiv[i][j + 1];
			}
		}
		M--;
	}
	virtual void virt() {  // виртуальная функция: выводит матрицу и её размеры
		cout << "Матрица с размерами " << N << " x " << M << ":\n";
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				cout << setw(5) << massiv[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	~MASS_RANDOM() {  // деструктор: можно без него, так как нет выделения динамической памяти
		// но пусть будет обнуление матрицы
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				massiv[i][j] = 0;
			}
		}
	}
	// дружественные функции и переопределение оператора +
	friend int search(MASS_RANDOM& matrix);
	friend int poisk(MASS_RANDOM& matrix);
	friend void operator+(MASS_RANDOM& matrix1, MASS_RANDOM& matrix2);
};


int search(MASS_RANDOM& matrix) {  // ищем значение минимума
	int mn = 10000000;
	for (int i = 0; i < matrix.N; ++i) {
		for (int j = 0; j < matrix.M; ++j) {
			if (matrix.massiv[i][j] < mn) {
				mn = matrix.massiv[i][j];
			}
		}
	}
	return mn;
}


int poisk(MASS_RANDOM& matrix) {  // кол-во элем до max
	int mx = -100000000, mx_i = 0, mx_j = 0;
	// ищем расположение max
	for (int i = 0; i < matrix.N; ++i) {
		for (int j = 0; j < matrix.M; ++j) {
			if (matrix.massiv[i][j] > mx) {
				mx = matrix.massiv[i][j];
				mx_i = i;
				mx_j = j;
			}
		}
	}
	// теперь считаем кол-во элем до него
	int cnt = mx_i * matrix.M + mx_j;
	return cnt;
}

void operator+(MASS_RANDOM& matrix1, MASS_RANDOM& matrix2) {  // переопределяем сложение двух матриц через оператор +
	// предполагается, что складываются матрицы одинаковых размеров
	for (int i = 0; i < matrix1.N; ++i) {
		for (int j = 0; j < matrix1.M; ++j) {
			matrix1.massiv[i][j] += matrix2.massiv[i][j];
		}
	}
}


class MASS_RANDOM2 : public MASS_RANDOM {  // производный класс
protected:
	int ch_sum, ch_mult;
public:
	MASS_RANDOM2(int n, int m, int k) : MASS_RANDOM(n, m, k) {  // конструктор для новый переменных ch_sum, ch_mult
		// на основе конструктора базового класса
		ch_sum = 0;
		ch_mult = 1;  // если в матрице не будет четных элементов, то останется = 1
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (massiv[i][j] % 2 == 0) {
					ch_sum += massiv[i][j];
					ch_mult *= massiv[i][j];
				}
			}
		}
	}
	void find_ind_of_min_ch_elem() {  // поиск индексов минимального четного элемента
		int ind_i = -1, ind_j = -1, mn = -1;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				if (massiv[i][j] % 2 == 0) {  // если элемент четный
					if (mn == -1) {  // если ещё не встретилось четного элемента
						mn = massiv[i][j];
						ind_i = i;
						ind_j = j;
					}
					else if (massiv[i][j] < mn) {
						mn = massiv[i][j];
						ind_i = i;
						ind_j = j;
					}
				}
			}
		}
		if (mn == -1) {  // если в матрице не будет четных элементов, то останется = -1
			cout << "В матрице нет четных элементов:\n";
		}
		else {
			// если будет несколько одинаковых минимальных четных элементов, то сохранятся индексы самого левого верхнего
			cout << "Минимальный четный элемент: индекс строки = " << ind_i << "; индекс столбца = " << ind_j << "\n";
		}
	}
	// можно не писать virtual, это обязательно только в базовом классе
	virtual void virt() {  // виртуальная функция: выводит матрицу и её max и min элементы
		int mx = massiv[0][0], mn = massiv[0][0];  // изначально считаем, что max и min это первый элемент
		cout << "Матрица:\n";
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				// постепенно обновляем max и min
				mx = max(mx, massiv[i][j]);
				mn = min(mn, massiv[i][j]);
				cout << setw(5) << massiv[i][j];
			}
			cout << endl;
		}
		cout << "Максимальный элемент = " << mx << "; Минимальный элемент = " << mn << "\n";
	}
	// нет необходимости в деструкторе, так как нет выделения динамической памяти
};


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	// Лаба 1

	/*
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
	*/

	// Лаба 2

	/*
	MASS_RANDOM matrix1(3, 3, 50);
	cout << "Матрица 1\n";
	matrix1.print();
	cout << "Минимум:\n";
	cout << search(matrix1) << "\n";
	cout << "Кол-во элем до max:\n";
	cout << poisk(matrix1) << "\n";
	cout << "Удаление столбца 1:\n";
	matrix1.delete_col(1);
	matrix1.print();

	MASS_RANDOM matrix2(5, 5, 20);
	cout << "Матрица 2\n";
	matrix2.print();
	cout << "Минимум:\n";
	cout << search(matrix2) << "\n";
	cout << "Кол-во элем до max:\n";
	cout << poisk(matrix2) << "\n";
	cout << "Удаление столбца 4:\n";
	matrix2.delete_col(4);
	matrix2.print();

	MASS_RANDOM matrix3(4, 4, 10);
	cout << "Матрица 3\n";
	matrix3.print();
	cout << "Минимум:\n";
	cout << search(matrix3) << "\n";
	cout << "Кол-во элем до max:\n";
	cout << poisk(matrix1) << "\n";
	cout << "Удаление столбца 2:\n";
	matrix3.delete_col(2);
	matrix3.print();

	MASS_RANDOM matrix4(3, 5, 10), matrix5(3, 5, 20);
	cout << "Матрица 4\n";
	matrix4.print();
	cout << "Матрица 5\n";
	matrix5.print();
	cout << "Сложение матрицы 4 и матрицы 5:\n";
	matrix4 + matrix5;  // результат сложения изменяет матрицу 4
	matrix4.print();
	*/

	// Лаба 3

	MASS_RANDOM* p;  // указатель создается для базового класса и может ссылаться на производный

	MASS_RANDOM matrix1(5, 5, 10);
	cout << "Объект matrix1 базового типа:\n";
	matrix1.print();
	p = &matrix1;
	cout << "Виртуальная функция для базового объекта matrix1:\n";
	matrix1.virt();  // можно также: p->virt()
	
	cout << "\n";

	MASS_RANDOM2 matrix2(3, 5, 6);
	cout << "Объект matrix1 производного типа:\n";
	matrix2.print();
	cout << "Поиск индексов минимального четного элемента для matrix2:\n";
	matrix2.find_ind_of_min_ch_elem();
	p = &matrix2;
	cout << "Виртуальная функция для производного объекта matrix2:\n";
	matrix2.virt();

	cout << "\n";

	MASS_RANDOM2 matrix3(4, 4, 20);
	cout << "Объект matrix3 производного типа:\n";
	matrix3.print();
	cout << "Поиск индексов минимального четного элемента для matrix3:\n";
	matrix3.find_ind_of_min_ch_elem();
	p = &matrix3;
	cout << "Виртуальная функция для производного объекта matrix3:\n";
	matrix3.virt();

	return 0;
}
