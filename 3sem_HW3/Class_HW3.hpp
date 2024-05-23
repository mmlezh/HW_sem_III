#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define ERROR_OUT 1
#define OK 0

using namespace std;

typedef struct
{
	double x;
	double y;
}point;

typedef struct //односвязная область без самопересечений
{
	int nmfvrt;
	point *vert;
}poly;

class Area
{
	private:
		int nmfpl;
		poly *polys;
	public:
		Area();//конструктор пустой области | вроде работает

		Area(const Area &object);//копиконструктор

		Area(int n);//конструктор по размеру

		Area operator+(const Area &odject);//оператор объединение

		void set_vert(int n, int m, double nx, double ny) const;//изменение координат точки nm 

		void add_vert(int n, int m, double nx, double my) const;//добавление точки

		void delete_vect(int n, int m);

		int get_nmfpl() const;//получение кол-ва связных компонент

		int get_nmfvrt(int n) const;//получение кол-ва вершин в связной компоненте n

		int position(point dot);//положение точки относительно области

		Area &operator=(const Area &object);//присваивание

		poly operator[](int n) const;// | вроде работает

		~Area();//деструктор | вроде работает

		friend istream &operator>>(istream &input, Area &object);//ввод | вроде работает

		friend ostream &operator<<(ostream &output, const Area &object);//вывод | вроде работает
};