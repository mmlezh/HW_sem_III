#include <iostream>

using namespace std;

class IntN
{	
	private: 
		size_t size;
		int *data;
	public: 
		IntN();//конструктор

		IntN(const IntN &object);//копиконструктор

		IntN(size_t size); //конструктор по размеру

		IntN &operator=(const IntN &object);//присваивание

		IntN operator+(const IntN &object) const;//оператор суммирования

		IntN &operator+=(const IntN &object);//оператор сумирования

		IntN operator-(const IntN &object) const;//оператор разности

		IntN &operator-();//оператор разности унарный

		IntN &operator-=(const IntN &object);//оператор разности

		//вывод и считывание
		friend istream &operator>>(istream &input, IntN &object);
		friend ostream &operator<<(ostream &output, const IntN &object);

		~IntN();//деструктор
};