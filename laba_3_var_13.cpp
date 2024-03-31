// Лаба 1 Вариант 13

/*
  Вариант 13. Определите класс для формирования случайного двоичного вектора заданной длины (данный вектор это 
  одномерный массив, значениями которого могут быть только числа 0 и 1).
  После генерации вектора осуществляется его кодирование, т.е. к вектору добавляется один контрольный разряд
  – такой, чтобы общее число единичных разрядов в коде было четным.
  Общий интерфейс класса может выглядеть так:
class kod_chet
{int *pvect; // описание указателя на массив
					  // пусть нулевой элемент массива будет контрольным разрядом
int N; // переменная которая хранит размер массива
//…
public:
	kod_chet (int); // конструктор класса
	void kod( ); // кодирование вектора
	void print ( ); // вывод вектора
};
Конструктор kod_chet:: kod_chet(int) генерирует с помощью датчика случайных чисел массив заданного размера
(например, kod_chet(10) должен создать массив из 10 чисел, в 0-й разряд записываем 0, остальные 9 значений 
генерируем случайно). Метод kod() проверяет вектор на четность (количество единиц в массиве - четное) 
и в зависимости от результата проверки дописывает в контрольный разряд 0 или 1.
Общий интерфейс класса может выглядеть так:
kod_chet x(20); // вызов конструктора
x.kod( ); // вызов метода для проверки на четность
x.print( );// вывод вектора на экран
Программа должна выполнить работу с тремя различными объектами.
*/

// Лаба 2 Вариант 13

/*
Вариант 13. Класс kod_chet дополнительно должен реализовать следующие операции:
(ort) проверка взаимной ортогональности двух векторов;
(invert) инвертирование вектора (замена значения 0 на 1 и наоборот);
(decod) перевод двоичного числа в десятичную систему счисления;
Объявите, какие можно, функции дружественными.
Дополнительно переопределите следующие операторы:
Сумма векторов в двоичной системе счисления – оператор +
Программа должна выполнить данные операции с несколькими объектами. Результаты всех операций вывести
*/

// Лаба 3 Вариант 13

/*
С помощью наследования создать класс kod_chet2. Новый класс дополнительно хранит количество нулей
и количество единиц в векторе (массиве). Реализовать функцию нахождения обратного вектора для заданного
(т.е. замена 0 на 1, а 1 на 0). В программу где описаны два класса (базовый и производный) добавить
виртуальную функцию и ее вызовы для созданных объектов. Функция базового класса должна выводить
исходный массив и его размер. Функция производного класса должна выводить на экран исходный массив,
а также его ранг (количество 1 в векторе).
*/


#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>

using namespace std;


class KOD_CHET {  // базовый класс
protected:  // изменили право доступа с private на protected, чтобы при наследовании был доступ
	int N;  // размер массива
	int* pvect;  // динамическое выделение памяти
public:
	KOD_CHET(int n) {  // конструктор двоичного вектора заданной длины
		N = n;
		pvect = new int[N];
		pvect[0] = 0;  // нулевой элемент будет контрольным разрядом, изначально там 0
		for (int i = 1; i < N; i++) {
			pvect[i] = rand() % 2;
		}
	}
	void kod() {  // проверяет вектор на четность (количество единиц в массиве - четное)
		// и в зависимости от результата проверки дописывает в контрольный разряд 0 или 1
		int cnt_1 = 0;
		for (int i = 1; i < N; ++i) {
			if (pvect[i] == 1) {
				cnt_1++;
			}
		}
		if (cnt_1 % 2 == 1) {  // если нечетное количество, изменяем контрольный разряд
			pvect[0] = 1;
		}
	}
	void print() {  // выводит вектор
		for (int i = 0; i < N; ++i) {
			cout << setw(3) << pvect[i];
		}
		cout << endl;
	}
	void invert() {  // инвертирование вектора (замена значения 0 на 1 и наоборот)
		for (int i = 0; i < N; ++i) {
			if (pvect[i] == 0) {
				pvect[i] = 1;
			}
			else {
				pvect[i] = 0;
			}
		}
	}
	virtual void virt() {  // виртуальная функция: выводит массив и его размер
		cout << "Массив с размером " << N << ":\n";
		for (int i = 0; i < N; ++i) {
			cout << setw(3) << pvect[i];
		}
		cout << endl;
	}
	~KOD_CHET() {  // деструктор
		delete[] pvect;
	}
	// дружественные функции и переопределение оператора +
	friend bool ort(KOD_CHET& v1, KOD_CHET& v2);
	friend int decod(KOD_CHET& v);
	friend void operator+(KOD_CHET& v1, KOD_CHET& v2);
};


bool ort(KOD_CHET& v1, KOD_CHET& v2) {  // проверка взаимной ортогональности двух векторов
	// два вектора ортогональны, если их скалярное произведение равно 0
	// скалярное произведение: x1*x2 + y1*y2 + z1*z2
	int skal_mult = 0;
	int v_size = v1.N;  // предполагаем, что размеры двух векторов одинаковые
	for (int i = 0; i < v_size; ++i) {
		skal_mult += v1.pvect[i] * v2.pvect[i];
	}
	if (skal_mult == 0) {
		return true;
	}
	return false;
}


int decod(KOD_CHET& v) {  // перевод двоичного числа в десятичную систему счисления
	int res = 0, p = 0;
	for (int i = v.N - 1; i >= 0; --i) {
		res += v.pvect[i] * pow(2, p);
		p++;
	}
	return res;
}


void operator+(KOD_CHET& v1, KOD_CHET& v2) {  // переопределяем сложение двух векторов через оператор +
	// предполагается, что размер одинаковый
	for (int i = 0; i < v1.N; ++i) {
		v1.pvect[i] += v2.pvect[i];
	}
}


class KOD_CHET2 : public KOD_CHET {  // производный класс
protected:
	int cnt_0, cnt_1;
public:
	KOD_CHET2(int n) : KOD_CHET(n) {  // конструктор для новых переменных cnt_0, cnt_1 на основе конструктора базового класса
		cnt_0 = 0;
		cnt_1 = 0;
		for (int i = 0; i < N; ++i) {
			if (pvect[i] % 2 == 1) {
				cnt_1++;
			}
			else {
				cnt_0++;
			}
		}
	}
	void find_inverse_vector() {  // нахождения обратного вектора для заданного (т.е.замена 0 на 1, а 1 на 0)
		for (int i = 0; i < N; ++i) {
			cout << setw(3) << !pvect[i];
		}
		cout << endl;
	}
	// можно не писать virtual, это обязательно только в базовом классе
	virtual void virt() {  // виртуальная функция: выводит массив и его ранг
		cout << "Массив с рангом " << cnt_1 << ":\n";
		for (int i = 0; i < N; ++i) {
			cout << setw(3) << pvect[i];
		}
		cout << endl;
	}
	// нет необходимости в деструкторе, так как нет выделения динамической памяти
};


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

	// Лаба 1

	/*
	KOD_CHET k1(10);
	cout << "Исходный объект 1:\n";
	k1.print();
	k1.kod();
	cout << "После проверки:\n";
	k1.print();

	KOD_CHET k2(5);
	cout << "Исходный объект 2:\n";
	k2.print();
	k2.kod();
	cout << "После проверки:\n";
	k2.print();

	KOD_CHET k3(15);
	cout << "Исходный объект 3:\n";
	k3.print();
	k3.kod();
	cout << "После проверки:\n";
	k3.print();
	*/

	// Лаба 2
	
	/*
	KOD_CHET v1(8), v2(8), v3(5), v4(5);

	cout << "Создание объектов:\n";
	cout << "Объект 1:\n";
	v1.print();
	cout << "Его перевод в 10 сс:\n";
	int v1_10 = decod(v1);
	cout << v1_10 << "\n";
	cout << "Объект 2:\n";
	v2.print();
	cout << "Его перевод в 10 сс:\n";
	int v2_10 = decod(v2);
	cout << v2_10 << "\n";
	cout << "Объект 3:\n";
	v3.print();
	cout << "Его перевод в 10 сс:\n";
	int v3_10 = decod(v3);
	cout << v3_10 << "\n";
	cout << "Объект 4:\n";
	v4.print();
	cout << "Его перевод в 10 сс:\n";
	int v4_10 = decod(v4);
	cout << v4_10 << "\n";

	cout << "\n";

	cout << "Проверка на ортогональность двух векторов:\n";
	cout << "Векторы 1 и 2:\n";
	string ans_1_2 = ort(v1, v2) == true ? "да" : "нет";
	cout << ans_1_2 << "\n";
	cout << "Векторы 3 и 4:\n";
	string ans_3_4 = ort(v3, v4) == true ? "да" : "нет";
	cout << ans_3_4 << "\n";

	cout << "\n";

	cout << "Инвертирование векторов:\n";
	cout << "Вектор 1:\n";
	v1.invert();
	v1.print();
	cout << "Вектор 2:\n";
	v2.invert();
	v2.print();
	cout << "Вектор 3:\n";
	v3.invert();
	v3.print();
	cout << "Вектор 4:\n";
	v4.invert();
	v4.print();

	cout << "\n";

	cout << "Сложение векторов:\n";
	cout << "Вектор 1 + вектор 2:\n";
	v1 + v2;  // результат сложения изменяет вектор v1
	v1.print();
	cout << "Вектор 3 + вектор 4:\n";
	v3 + v4;  // результат сложения изменяет вектор v3
	v3.print();
	*/

	// Лаба 3

	KOD_CHET* p;  // указатель создается для базового класса и может ссылаться на производный

	KOD_CHET v1(10);
	cout << "Объект v1 базового класса:\n";
	v1.print();
	p = &v1;
	cout << "Виртуальная функция для базового объекта v1:\n";
	v1.virt();  // можно также: p->virt()

	cout << "\n";

	KOD_CHET2 v2(6);
	cout << "Объект v2 производного класса:\n";
	v2.print();
	cout << "Обратный вектор для вектора v2:\n";
	v2.find_inverse_vector();
	p = &v2;
	cout << "Виртуальная функция для производного объекта v2:\n";
	v2.virt();

	cout << "\n";

	KOD_CHET2 v3(8);
	cout << "Объект v3 производного класса:\n";
	v3.print();
	cout << "Обратный вектор для вектора v3:\n";
	v3.find_inverse_vector();
	p = &v3;
	cout << "Виртуальная функция для производного объекта v3:\n";
	v3.virt();

	return 0;
}
