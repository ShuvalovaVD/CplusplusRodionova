// Курсовая по C++. Шувалова Валерия, ПМбд-21. Вариант-7. Программная реализация матричных операций


#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>
#include <string>

using namespace std;


class Matrix {
protected:
	int rows, columns;  // размеры матрицы
	int matrix[10][10];  // матрица (максимальный размер - 10x10)

public:
	Matrix(int rows, int columns) {  // конструктор: генерирует рандомную матрицу указанных размеров
		Matrix::rows = rows;
		Matrix::columns = columns;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] = 1 + rand() % 20;  // 1 - 20
			}
		}
	}

	void multiply_by_number(int number) {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] *= number;
			}
		}
	}

	bool check_symmetry() {
		if (rows != columns) {
			return false;
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] != matrix[j][i]) {
					return false;
				}
			}
		}
		return true;
	}

	void add_matrix(Matrix other_matrix) {  // предполагается, что сложение матриц определено
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] += other_matrix.matrix[i][j];
			}
		}
	}

	void subtract_matrix(Matrix other_matrix) {  // предполагается, что вычитание матриц определено
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] -= other_matrix.matrix[i][j];
			}
		}
	}

	void show() {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				cout << setw(4) << matrix[i][j];
			}
			cout << "\n";
		}
	}

	~Matrix() {  // деструктор: обнуляет матрицу
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				matrix[i][j] = 0;
			}
		}
	}

	// дружественные функции, к-рые будут изменять элементы матрицы, имея доступ к массиву matrix
	friend Matrix get_matrix();
	friend Matrix transpone_matrix(Matrix & old_matrix);
	// дружественные функции, к-рые имеют доступ к размерам rows и columns
	friend bool check_addition_of_matrices(Matrix & matrix_1, Matrix & matrix_2);
	friend bool check_multiplication_of_matrices(Matrix & matrix_1, Matrix & matrix_2);
	// дружественная функция, к-рая имеет доступ к размерам rows и columns, а также к массиву matrix
	friend Matrix multiply_matrices(Matrix & matrix_1, Matrix & matrix_2);
};


void show_options_menu() {
	cout << "Выберите опцию (введите номер 1-7):\n";
	cout << "1. Умножение матрицы на число\n";
	cout << "2. Транспонирование матрицы\n";
	cout << "3. Проверка матрицы на симметричность\n";
	cout << "4. Сложение двух матриц\n";
	cout << "5. Вычитание двух матриц\n";
	cout << "6. Умножение двух матриц\n";
	cout << "7. Выход\n\n";
}


Matrix get_matrix() {
	int rows, columns;
	cout << "Введите размеры матрицы:\n";
	cout << "Количество строк: ";
	cin >> rows;
	cout << "Количество столбцов: ";
	cin >> columns;
	Matrix matrix = Matrix(rows, columns);  // пока сгенерируем рандомную матрицу указанных размеров
	cout << "Сгенерировать рандомную матрицу указанных размеров (1) или задать вручную (2)? (1/2):\n";
	string answer;
	cin >> answer;
	if (answer == "1") {
		cout << "Сгенерированная матрица:\n";
		matrix.show();
		return matrix;
	}
	// else: заполняем матрицу указанными числами
	cout << "Введите матрицу:\n";
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			cin >> matrix.matrix[i][j];
		}
	}
	return matrix;
}


Matrix transpone_matrix(Matrix & old_matrix) {
	Matrix new_matrix = Matrix(old_matrix.columns, old_matrix.rows);  // создаем транспонированную матрицу с размерами наоборот
	for (int i = 0; i < old_matrix.rows; ++i) {
		for (int j = 0; j < old_matrix.columns; ++j) {
			new_matrix.matrix[j][i] = old_matrix.matrix[i][j];  // изменяем её элементы
		}
	}
	return new_matrix;
}


bool check_addition_of_matrices(Matrix & matrix_1, Matrix & matrix_2) {  // проверяет возможность сложения (вычитания) матриц
	if (matrix_1.rows == matrix_2.rows && matrix_1.columns == matrix_2.columns) {
		return true;
	}
	return false;
}


bool check_multiplication_of_matrices(Matrix & matrix_1, Matrix & matrix_2) {  // проверяет возможность умножения матриц
	if (matrix_1.columns == matrix_2.rows) {
		return true;
	}
	return false;
}


Matrix multiply_matrices(Matrix & matrix_1, Matrix & matrix_2) {  // предполагается, что умножение матриц определено
	int rows_result, columns_result;
	rows_result = matrix_1.rows;
	columns_result = matrix_2.columns;
	Matrix matrix_result = Matrix(rows_result, columns_result);  // создаем итоговую матрицу с новыми размерами
	// теперь перезапишем её значения
	for (int i = 0; i < rows_result; ++i) {
		for (int j = 0; j < columns_result; ++j) {
			// ячейка[i][j] matrix_result - это i - ая строка matrix_1, умноженная покоординатно на j - ый столбец matrix_2
			matrix_result.matrix[i][j] = 0;
			for (int k = 0; k < matrix_1.columns; ++k) {
				matrix_result.matrix[i][j] += matrix_1.matrix[i][k] * matrix_2.matrix[k][j];
			}
		}
	}
	return matrix_result;
}


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	cout << "Программная реализация матричных операций\n\n";
	while (true) {
		show_options_menu();
		string answer;
		cin >> answer;
		if (answer == "1") {
			Matrix matrix = get_matrix();
			cout << "Введите число: ";
			int number;
			cin >> number;
			matrix.multiply_by_number(number);
			cout << "Итоговая матрица:\n";
			matrix.show();
		}
		else if (answer == "2") {
			Matrix matrix = get_matrix();
			Matrix transponed_matrix = transpone_matrix(matrix);
			cout << "Транспонированная матрица:\n";
			transponed_matrix.show();
		}
		else if (answer == "3") {
			Matrix matrix = get_matrix();
			bool flag_verdict = matrix.check_symmetry();
			if (flag_verdict) {
				cout << "Матрица симметрична\n";
			}
			else {
				cout << "Матрица несимметрична\n";
			}
		}
		else if (answer == "4") {
			cout << "Первая матрица:\n";
			Matrix matrix_1 = get_matrix();
			cout << "Вторая матрица:\n";
			Matrix matrix_2 = get_matrix();
			if (check_addition_of_matrices(matrix_1, matrix_2)) {
				matrix_1.add_matrix(matrix_2);
				cout << "Итоговая матрица:\n";
				matrix_1.show();
			}
			else {
				cout << "Сложение матриц не определено\n";
			}
		}
		else if (answer == "5") {
			cout << "Первая матрица:\n";
			Matrix matrix_1 = get_matrix();
			cout << "Вторая матрица:\n";
			Matrix matrix_2 = get_matrix();
			if (check_addition_of_matrices(matrix_1, matrix_2)) {
				matrix_1.subtract_matrix(matrix_2);
				cout << "Итоговая матрица:\n";
				matrix_1.show();
			}
			else {
				cout << "Вычитание матриц не определено\n";
			}
		}
		else if (answer == "6") {
			cout << "Первая матрица:\n";
			Matrix matrix_1 = get_matrix();
			cout << "Вторая матрица:\n";
			Matrix matrix_2 = get_matrix();
			if (check_multiplication_of_matrices(matrix_1, matrix_2)) {
				Matrix matrix_result = multiply_matrices(matrix_1, matrix_2);
				cout << "Итоговая матрица:\n";
				matrix_result.show();
			}
			else {
				cout << "Умножение матриц не определено\n";
			}
		}
		else {
			cout << "\n";
			break;
		}
		cout << "\n";
	}
	cout << "Завершение работы программы";

	return 0;
}
