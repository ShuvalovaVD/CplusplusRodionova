// Лекция 2. Описание дружественных функций и переопределение операторов

/*
Теория
Оператор :: - оператор расширения области видимости
Применение:
1) Используется при описании метода класса вне класса:
Пусть у нас есть функция класса, но она слишкл большая, тогда в классе ставим прототип, а функцию выносим вне класса
void ODMAS::myprint_extra() {  // показываем, что метод относится к классу ODMAS
	for (int i = 0; i < N; ++i) cout << setw(3) << mas[i];
	cout << endl;
}
:: показывает принадлежность функции к классу
2) Используется для обращения к глобальной переменной, если она закрыта локальной переменной:
int i = 0;  // глобальная переменная
void func(...) {
	int i = 3;  // локальная переменная
	i++;  // компилятор увеличит локальную i
	::i++;  // компилятор увеличит глобальную i
}
То есть в данном случае :: позволил выйти на один уровень выше.
Чтобы обойти данную проблему, можно называть все переменные разными названиями, но это не всегда грамотно,
иногда лучше использовать ::
3) Используется для указания явного различия между именем членов класса и прочими именами:
Пример в коде ниже с N и ODMAS::N
4) Используется для уточнения имени функции:
Есть своя функция, которая называется так же, как библиотечная ф-ция, в итоге она закрывает глобальную ф-цию.
Надо использоать :: перед именем ф-ции, когда вызываем её, чтобы использовать стандартную функцию.

Ссылки:
Ссылка - это видоизмененный указатель, это более простой способ использования адресации.
Ссылка формирует второе имя объекта и связывается с переменной.

int t;  // исходный массив
int& pt = t;  // ссылка
pt = 10;  // меняется переменная t

void swap1(int* x, int* y){  // передаем указатели
	int z = *y;
	*y = *x;
	*x = z;
	// звездочки нужны, чтобы получить значения, иначе будет адрес
}
void swap2(int& x, int& y){
	int z = y;
	y = x;
	x = z;
	// уже не нужны звездочки, этот способ проще
}
для вызова функции swap1 необходимы исходные данные и указатели на них:
int a, b;
int *pa = &a, *pb = &b;
swap1(pa, pb);
для вызова функции swap2 необходимы только исходные данные:
int a, b;
swap2(&a, &b);  // можно, кстати без амперсандов передавать
потом вывести исходные a и b, увидеть, что они поменялись

Дружественные функции:
Дружественная функция - это функция, которая не является методом класса, но имеет доступ к закрытой части класса.
Например, есть два класса Matrix и Vector. И мы хотим умножить матрицу на вектор, логично в даном случае создать
дружественную функцию.
class Matrix {
...
	friend Vector mult(Matrix & m, Vector & v);
	int elem(int i, int j) {
		// возвращает элемент матрицы по индексам i, j
	}
}
class Vector {
...
	friend Vector mult(Matrix & m, Vector & v);
	int elem(int i) {
		// возвращает элемент вектора по индексу i
	}
}
// внутри классов Matrix и Vector надо написать прототип дружественной функции
// также метод elem, который осуществляет доступ к элементам
Vector mult (Matrix & m, Vector & v) {  // результатом умножения матрицы на вектор является вектор
	Vector rez;
	for (int i = 0; i < 3; ++i) {
		rez.elem(i) = 0;
		for (int j = 0; j < 3; ++j) {
			rez.elem(i) += m.elem(i, j) * v.elem(j);
		}
	}
	return rez;
}
Метод одного класса может быть другом другого:
class X {
	void function();
}
class Y {
	friend void X::function();
}
Все методы одного класса могут являются друзьями другого. Для этого есть даже более краткая запись:
class X {
	friend class Y;
	// ...
};
Такое описание делает все методы класса Y друзьями класса X.
*/

#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>

using namespace std;

class ODMAS {
private:
	int N;  // размер массива - имя члена класса
	int* mas;
public:
	ODMAS(int N, int a) {
		// N = N; - такая запись глупая, так как у нас разные N
		ODMAS::N = N;  // поймет, что ODMAS::N - это имя члена класса, а N - это имя переданного в конструктор аргумента
		mas = new int[N];  // здесь уже берет просто N, но в данном случае нам без разницы: значения одинаковые
		for (int i = 0; i < N; i++) mas[i] = a;
	}
	~ODMAS() {
		delete[] mas;
	}
};

int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	return 0;
}
