// Лекция 1. Описание класса

/*
Теория:

Стили программированию:
1) Стихийное программирование
2) Структурный подход
3) Объективно-ориентированный подход
4) Компонентный подход: разные части программы с разными подходами

Основные принципы ООП:
1) абстрагирование - выделение существенных свойств объекта, которые выделяют его от всех лругих объектов и являются наиболее важными для программиста
2) инкапсуляция - это объединение описания объекта и его свойств в одно понятие
3) модульность - разделение системы на блоки кода, т. е. модули
4) иерархия - упорядоченность существующих объектов

Конструктор - это функция, которая автоматически вызывается при создании объекта, у неё нет возвращаемого значения. Её имя совпадает с именем класса. У конструктора могут быть аргументы:
столько, сколько потребуется. Конструкторов у класса может быть несколько Они должны отличаться количеством и типом аргументов.

*/

#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>

using namespace std;

class ODMAS {
private: // поля закыты
	int N;  // размер массива
	int* mas;  // динамическое выделение памяти
public: // конструктор и методы открыты (можно обращаться из main)
	ODMAS(int n, int a) {  // первый вид конструктора
		N = n;
		mas = new int[N];
		for (int i = 0; i < N; i++) mas[i] = a;
	}
	ODMAS(int n) {  // второй вид конструктора
		N = n;
		mas = new int[N];
		for (int i = 0; i < N; i++) mas[i] = rand() % 100;
	}
	void myprint() {  // метод класса
		for (int i = 0; i < N; ++i) cout << setw(3) << mas[i];
		cout << endl;
	}
	void myprint_extra();  // прототип метода, сам метод напишем вне класса
	~ODMAS() {  // деструктор
		delete [] mas;
	}
};

void ODMAS::myprint_extra() {  // показываем, что метод относится к классу
	for (int i = 0; i < N; ++i) cout << setw(3) << mas[i];
	cout << endl;
}

int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	cout << "Объект 1" << endl;
	ODMAS M1(10, 5);
	M1.myprint();
	cout << "Объект 2" << endl;
	ODMAS M2(10);
	M2.myprint_extra();

	return 0;
}
