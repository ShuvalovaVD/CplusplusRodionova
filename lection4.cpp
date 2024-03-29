// Лекция 4. Наследование

/*
Теория
Наследование - это повторное использование уже созданных классов. Создаём на основе существующих классов новые.
Родительский класс - базовый, дочерний - производный.
class [имя производного класса] : [право наследование] [имя базового класса]
Перед именем базового класса указывается право наследования. Право наследования влияет на право доступа к компонентам класса.
Права наследования:
public:
public -> public
protected -> protected
private -> недоступно


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
	int N;
	int* mas;
public:
	ODMAS(int N, int a) {
		ODMAS::N = N;
		mas = new int[N];
		for (int i = 0; i < N; i++) mas[i] = a;
	}
	void myprint() {
		for (int i = 0; i < N; ++i) {
			cout << mas[i] << " ";
		}
		cout << "\n\n";
	}
	~ODMAS() {
		delete[] mas;
	}
	friend void mult(ODMAS& m, int k);
	friend void operator+(ODMAS& a, int b);
	friend ODMAS operator-(ODMAS& a, int b);
};

void mult(ODMAS& m, int k) {
	for (int i = 0; i < m.N; i++) {
		m.mas[i] = m.mas[i] * k;
	}
}

void operator+(ODMAS& a, int b) {  // оператор + не возвращает значение
	for (int i = 0; i < a.N; ++i) {
		a.mas[i] += b;
	}
}

ODMAS operator-(ODMAS& a, int b) {  // оператор - возвращает значение
	static ODMAS rez(a.N, 10);  // static нужен, чтобы правильно сработало
	for (int i = 0; i < a.N; ++i) {
		rez.mas[i] = a.mas[i] - b;
	}
	return rez;
}


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	ODMAS x1(10, 10);
	x1.myprint();
	int k1 = 5;
	x1 + k1;
	x1.myprint();
	// если хотим, чтобы значение возвращалось
	int k2 = 20;
	ODMAS x2 = x1 - k2;  // уже новый объект x2
	x2.myprint();
	// будет вызываться исключение, но игнорируем его (можно отключить в настройках)

	return 0;
}
