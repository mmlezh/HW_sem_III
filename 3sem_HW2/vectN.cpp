#include "vectN.hpp"

using namespace std;

	IntN::IntN() : size(0), data(nullptr) {}//конструктор
	
	IntN::IntN(const IntN &object) : size(object.size), data(nullptr)//копиконструктор
	{
		data = new int[size];
		for(size_t i = 0; i < size; i++)
		{
			data[i] = object.data[i];
		}
	}

	IntN::IntN(size_t size) : size(size), data(nullptr)//конструктор по размеру
	{
		data = new int[size];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = 0
		}
	}

	IntN &IntN::operator=(const IntN &object)//присваивание
	{
		data = nullptr;
		size = object.size;
		data = new int[object.size];
		for(size_t i = 0; i < size; i++)
		{
			data[i] = object.data[i];
		}
		return *this;
	}

	IntN IntN::operator+(const IntN &object) const//оператор суммирования
	{
		IntN result(size);
		for(size_t i = 0; i < size; i++)
		{
			result.data[i] = data[i] + object.data[i];
		}
		return result;
	}

	IntN &IntN::operator+=(const IntN &object)//оператор сумирования
	{
		for(size_t i = 0; i < size; i++)
		{
			data[i] += object.data[i]
		}
		return *this;
	}

	IntN IntN::operator-(const IntN &object) const//оператор разности
	{
		IntN result(size);
		for(size_t i = 0; i < size; i++)
		{
			result.data[i] = data[i] + object.data[i]; 
		}
		return result;
	}

	IntN &IntN::operator-()//оператор разности унарный
	{
		for(size_t i = 0; i < size; i++)
		{
			data[i] = -data[i];
		}
		return *this;
	}

	IntN &IntN::operator-=(const IntN &object)//оператор разности
	{
		for(size_t i = 0; i < size; i++)
		{
			data[i] -= object.data[i];
		}
		return *this;
	}

	//вывод и считывание
	istream &operator>>(istream &input, IntN &object)
	{
		if(object.size == 0)
		{
			delete[] object.data;

			object.data = nullptr;
			return input;
		}

		delete[] object.data;

		object.data = new int[object.size];
		for(size_t i = 0; i < object.size; i++)
		{
			input >> object.data[i];
		}
		return input;
	}

	ostream &operator<<(ostream &output, const IntN &object);
	
	IntN::~IntN();//деструктор