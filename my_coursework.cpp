// Курсовая по C++. Шувалова Валерия, ПМбд-21. Вариант-7. Программная реализация матричных операций


#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>
#include <string>
#include <fstream>

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

	int check_square() {
		if (rows != columns) {
			return -1;
		}
		return rows;
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
	friend Matrix transpone_matrix(Matrix& old_matrix);
	// дружественные функции, к-рые имеют доступ к размерам rows и columns
	friend bool check_addition_of_matrices(Matrix& matrix_1, Matrix& matrix_2);
	friend bool check_multiplication_of_matrices(Matrix& matrix_1, Matrix& matrix_2);
	// дружественные функции, к-рые имеют доступ к размерам rows и columns, а также к массиву matrix
	friend Matrix multiply_matrices(Matrix& matrix_1, Matrix& matrix_2);
	friend void put_if_file_matrix_result(Matrix& matrix);
	friend int** create_array(Matrix matrix);
};


void show_options_menu() {
	cout << "Выберите опцию (введите номер 1-7):\n";
	cout << "1. Ввод новой матрицы\n";
	cout << "2. Умножение матрицы на число\n";
	cout << "3. Транспонирование матрицы\n";
	cout << "4. Проверка матрицы на симметричность\n";
	cout << "5. Сложение двух матриц\n";
	cout << "6. Вычитание двух матриц\n";
	cout << "7. Умножение двух матриц\n";
	cout << "8. Найти определитель матрицы\n";
	cout << "9. Выход\n\n";
}


Matrix get_matrix() {
	int rows, columns;
	cout << "Введите размеры матрицы:\n";
	cout << "Количество строк: ";
	cin >> rows;
	cout << "Количество столбцов: ";
	cin >> columns;
	Matrix matrix = Matrix(rows, columns);  // пока сгенерируем рандомную матрицу указанных размеров
	cout << "Сгенерировать рандомную матрицу указанных размеров (1) или считать из файла input.txt (2)? (1/2):\n";
	string answer;
	cin >> answer;
	if (answer == "1") {
		cout << "Сгенерированная матрица:\n";
		matrix.show();
		cout << "\n";
		return matrix;
	}
	// else: считываем из файла input.txt
	cout << "Введите матрицу в файл input.txt и введите +: ";
	cin >> answer;
	cout << "\n";
	ifstream input_file("input.txt");
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			input_file >> matrix.matrix[i][j];
		}
	}
	input_file.close();
	return matrix;
}


void put_if_file_matrix_result(Matrix& matrix) {
	ofstream output_file("output.txt");
	for (int i = 0; i < matrix.rows; ++i) {
		for (int j = 0; j < matrix.columns; ++j) {
			output_file << setw(4) << matrix.matrix[i][j];
		}
		output_file << "\n";
	}
	output_file.close();
}


Matrix transpone_matrix(Matrix& old_matrix) {
	Matrix new_matrix = Matrix(old_matrix.columns, old_matrix.rows);  // создаем транспонированную матрицу с размерами наоборот
	for (int i = 0; i < old_matrix.rows; ++i) {
		for (int j = 0; j < old_matrix.columns; ++j) {
			new_matrix.matrix[j][i] = old_matrix.matrix[i][j];  // изменяем её элементы
		}
	}
	return new_matrix;
}


bool check_addition_of_matrices(Matrix& matrix_1, Matrix& matrix_2) {  // проверяет возможность сложения (вычитания) матриц
	if (matrix_1.rows == matrix_2.rows && matrix_1.columns == matrix_2.columns) {
		return true;
	}
	return false;
}


bool check_multiplication_of_matrices(Matrix& matrix_1, Matrix& matrix_2) {  // проверяет возможность умножения матриц
	if (matrix_1.columns == matrix_2.rows) {
		return true;
	}
	return false;
}


Matrix multiply_matrices(Matrix& matrix_1, Matrix& matrix_2) {  // предполагается, что умножение матриц определено
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


int** create_array(Matrix matrix) {
	int n = matrix.rows;
	int** a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = matrix.matrix[i][j]; // заполняем элементами матрицы matrix
		}
	}
	return a;
}


int find_determinant(int** a, int n) { // рекурсивная функция вычисления определителя матрицы; предполагается, что матрица квадратная
	if (n == 1)
		return a[0][0];
	else if (n == 2)
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
	else {
		int d = 0;
		for (int k = 0; k < n; k++) {
			int** m = new int* [n - 1];
			for (int i = 0; i < n - 1; i++) {
				m[i] = new int[n - 1];
			}
			for (int i = 1; i < n; i++) {
				int t = 0;
				for (int j = 0; j < n; j++) {
					if (j == k)
						continue;
					m[i - 1][t] = a[i][j];
					t++;
				}
			}
			d += pow(-1, k + 2) * a[0][k] * find_determinant(m, n - 1);
		}
		return d;
	}
}


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	cout << "Программная реализация матричных операций\n\n";
	Matrix matrix = get_matrix();
	while (true) {
		show_options_menu();
		string answer;
		cin >> answer;
		if (answer == "1") {
			matrix = get_matrix();
		}
		else if (answer == "2") {
			cout << "Введите число: ";
			int number;
			cin >> number;
			matrix.multiply_by_number(number);
			cout << "Итоговая матрица:\n";
			matrix.show();
			put_if_file_matrix_result(matrix);
		}
		else if (answer == "3") {
			matrix = transpone_matrix(matrix);
			cout << "Транспонированная матрица:\n";
			matrix.show();
			put_if_file_matrix_result(matrix);
		}
		else if (answer == "4") {
			if (matrix.check_symmetry()) {
				cout << "Матрица симметрична\n";
			}
			else {
				cout << "Матрица несимметрична\n";
			}
		}
		else if (answer == "5") {
			cout << "Введите ещё одну матрицу:\n";
			Matrix matrix_other = get_matrix();
			if (check_addition_of_matrices(matrix, matrix_other)) {
				matrix.add_matrix(matrix_other);
				cout << "Итоговая матрица:\n";
				matrix.show();
				put_if_file_matrix_result(matrix);
			}
			else {
				cout << "Сложение матриц не определено\n";
			}
		}
		else if (answer == "6") {
			cout << "Введите ещё одну матрицу:\n";
			Matrix matrix_other = get_matrix();
			if (check_addition_of_matrices(matrix, matrix_other)) {
				matrix.subtract_matrix(matrix_other);
				cout << "Итоговая матрица:\n";
				matrix.show();
				put_if_file_matrix_result(matrix);
			}
			else {
				cout << "Вычитание матриц не определено\n";
			}
		}
		else if (answer == "7") {
			cout << "Введите ещё одну матрицу:\n";
			Matrix matrix_other = get_matrix();
			if (check_multiplication_of_matrices(matrix, matrix_other)) {
				matrix = multiply_matrices(matrix, matrix_other);
				cout << "Итоговая матрица:\n";
				matrix.show();
				put_if_file_matrix_result(matrix);
			}
			else {
				cout << "Умножение матриц не определено\n";
			}
		}
		else if (answer == "8") {
			int n = matrix.check_square();
			if (n != -1) {
				int** a = create_array(matrix);
				int d = find_determinant(a, n);
				cout << "Детерминант: " << d << "\n";
			}
			else {
				cout << "Определитель существует только для квадратной матрицы\n";
			}
		}
		else {  // answer == 9
			cout << "\n";
			break;
		}
		cout << "\n";
		cout << "Желаете продолжить? (+/-): ";
		cin >> answer;
		if (answer != "+") {
			break;
		}
		cout << "\n";
	}
	cout << "Завершение работы программы";

	return 0;
}
