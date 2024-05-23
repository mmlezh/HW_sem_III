#include "Class_HW3.hpp"

using namespace std;

Area::Area() : nmfpl(0), polys(nullptr){};

Area::Area(const Area &object) : nmfpl(object.nmfpl)
{
	if(polys) 
	{
		for(int i = 0; i < nmfpl; i++)
		{
			delete [] polys[i].vert;
			polys[i].vert = nullptr;
		}
		delete [] polys;
 	}

 	polys = nullptr;
 	polys = new poly[nmfpl];
 	for(int i = 0; i < nmfpl; i++)
 	{
 		polys[i].nmfvrt = object[i].nmfvrt;
 		polys[i].vert = new point[polys[i].nmfvrt];
 		for(int j = 0; j < object[i].nmfvrt; j++)
 		{
 			polys[i].vert[j] = object[i].vert[j];
 		}
 	}
}

Area::Area(int n) : nmfpl(n)
{
	polys = new poly[nmfpl];
	for(int i = 0; i < nmfpl; i++)
	{
		polys[i].nmfvrt = 0;
		polys[i].vert = nullptr;
	}
} 

istream &operator>>(istream &input, Area &object)//ввод
{
	int size;
	input >> object.nmfpl;
	//cout << object.nmfpl;
	object.polys = new poly[object.nmfpl];

	for(int i = 0; i < object.nmfpl; i++)
	{
		input >> size;
		//cout << size << "\n";
		object.polys[i].nmfvrt = size;
		object.polys[i].vert = new point[object.polys[i].nmfvrt];

		for(int j = 0; j < object.polys[i].nmfvrt; j++)
		{
			//double x, y;
			input >> object.polys[i].vert[j].x >> object.polys[i].vert[j].y;
			//cout << j << "\t "<< x << " " <<   y << "\n";
		}
	}
    return input;
}

ostream &operator<<(ostream &output, const Area &object)//вывод
{
    if (object.nmfpl == 0) {

        delete[] object.polys;

        output << "Тут пусто\n";
        return output;
    }
    for (int i = 0; i < object.nmfpl; i++) {
    	output << object.polys[i].nmfvrt << "\t";
        for (int j = 0; j < object.polys[i].nmfvrt; j++) {
           	output << "(" << object.polys[i].vert[j].x << ", " << object.polys[i].vert[j].y << ") ";
        }
        output << "\n";
    }
    return output;
}

poly Area::operator[](int n) const
{
	return polys[n];
}

Area::~Area()
{
	for(int i = 0; i < nmfpl; i++)
	{
		delete [] polys[i].vert;
		polys[i].vert = nullptr;
	}
	delete [] polys;
}