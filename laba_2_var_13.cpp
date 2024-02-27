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

#include <iostream>
#include <math.h>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <time.h>

using namespace std;

class KOD_CHET {
private:
	int N;  // размер массива
	int* pvect;  // динамическое выделение памяти
public:
	KOD_CHET(int n) {
		N = n;
		pvect = new int[N];
		pvect[0] = 0;  // нулевой элемент будет контрольным разрядом, изначально там 0
		for (int i = 1; i < N; i++) {
			pvect[i] = rand() % 2;
		}
	}
	void kod() {
		int cnt_1 = 0;
		for (int i = 1; i < N; ++i) {
			if (pvect[i] == 1) {
				cnt_1++;
			}
		}
		if (cnt_1 % 2 == 1) {  // если нечетное количество 
			pvect[0] = 1;
		}
	}
	void print() {
		for (int i = 0; i < N; ++i) {
			cout << setw(3) << pvect[i];
		}
		cout << endl;
	}
	void invert() {  // инвертирование
		for (int i = 0; i < N; ++i) {
			if (pvect[i] == 0) {
				pvect[i] = 1;
			}
			else {
				pvect[i] = 0;
			}
		}
	}
	~KOD_CHET() {  // деструктор
		delete[] pvect;
	}
	friend bool ort(KOD_CHET& v1, KOD_CHET& v2);
	friend int decod(KOD_CHET& v);
};


bool ort(KOD_CHET & v1, KOD_CHET & v2) {
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


int decod(KOD_CHET& v) {
	int res = 0, p = 0;
	for (int i = v.N - 1; i >= 0; --i) {
		res += v.pvect[i] * pow(2, p);
		p++;
	}
	return res;
}


int main() {
	setlocale(LC_ALL, "ru");
	srand((unsigned)time(NULL));

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

	return 0;
}
