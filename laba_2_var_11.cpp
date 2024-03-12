// Лаба 2 Вариант 11

/*
Вариант 11. Класс mass_random дополнительно должен реализовать следующие операции:
(search) поиск минимального элемента;
(poisk) поиск количества элементов расположенных ДО максимума;
(delete) удаление столбца из массива;
Объявите, какие можно, функции дружественными.
Дополнительно переопределите следующие операторы:
Сумма матриц – оператор +
Программа должна выполнить данные операции с несколькими объектами. Результаты всех операций вывести
*/

#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>

using namespace std;

class MASS_RANDOM {
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
	void delete_col(int column) {  // удаление столбца из массива
		for (int i = 0; i < N; ++i) {
			for (int j = column - 1; j < M - 1; ++j) {
				massiv[i][j] = massiv[i][j + 1];
			}
		}
		M--;
	}
	~MASS_RANDOM() {  // деструктор
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				massiv[i][j] = 0;
			}
		}
	}
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

void operator+(MASS_RANDOM& matrix1, MASS_RANDOM& matrix2) {
	// предполагается, что складываются матрицы одинаковых размеров
	for (int i = 0; i < matrix1.N; ++i) {
		for (int j = 0; j < matrix1.M; ++j) {
			matrix1.massiv[i][j] += matrix2.massiv[i][j];
		}
	}
}


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

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

	return 0;
}
