/*

Требуется реализовать хранение и работу с подмножествами пар (x, y)
целых чисел, принадлежащих заданым диапазонам [x1, x2] x [y1,y2].

Идея реализации: сначала паре (x, y) сопоставляется линейный номер 
(как при записи матрицы по строкам в одномерный массив), затем
заводится массив целых чисел, в котором каждому возможному
линейному номеру сопоставляется один бит. Таким образом, работа
сводится к установке или поверке значения отдельного бита в
некотором элементе целочисленного массива. Значения, выходящие из
заданного диапозона, не могут размещаться в множестве (сооб. об ошибке), 
но диапазон можно изменить отдельной функцией.

Реализация должна поддерживать след. возможности:
-создание пустого множества для заданного диапазона чисел;
-очистка всего множества
-добавление/удаление заданного значения
-проверка принадлежности заданного значения множеству
-получение max и min значений, содержащихся в множестве (огр. прямоуг.)
-итератор по множ. (возможность перебора всех элем. из множ.)
-объединение, пересечение и другие операции с аналогичным множ.
-изменение диапазона допустимых элементов
-получение границ текущего диапазона множества

*/
#include "BitSet.hpp"

void LineSegment::set_segment(const int new_min, const int new_max)//работает
{
	min = new_min;
	max = new_max;
}

int LineSegment::get_min()//работает
{
	return min;
}

int LineSegment::get_max()//работает
{
	return max;
}

int LineSegment::get_lenght() //работает
{
	return max - min + 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
BitSet::BitSet() //работает
{
	Ox.set_segment(0, 0);
 	Oy.set_segment(0, 0);
 	values = nullptr;
 	size = 0;
}

BitSet::BitSet(LineSegment X, LineSegment Y)
{
	Ox.set_segment(X.get_min(), X.get_max());
	Oy.set_segment(Y.get_min(), Y.get_max());
	
	size = Ox.get_lenght() * Oy.get_lenght();

	values = new int[size];

	for(int i = 0; i < size; i++)
	{
		values[i] = i + 1;
	}
}

BitSet::BitSet(BitSet &object)//???
{
	Ox.set_segment(object.Ox.get_min(), object.Ox.get_max());
	Oy.set_segment(object.Oy.get_min(), object.Oy.get_max());
	size = object.size;
	values = new int[size];
	for(int i = 0; i < size; i++)
	{
		values[i] = object.values[i];
	}
}

int BitSet::delete_value(const int x, const int y) //работает
{
	if((x < Ox.get_min()) || (x > Ox.get_max()))
	{
		return ERROR_OUT;
	}
	if((y < Oy.get_min()) || (y > Oy.get_max()))
	{
		return ERROR_OUT;
	}

	values[(Oy.get_max() - y) * Ox.get_lenght() + (x - Ox.get_min())] = (Oy.get_max() - y) * Ox.get_lenght() + (x - Ox.get_min());

	return OK_OUT;
}

void BitSet::delete_all()
{
	for(int i = 0; i < size; i++)
	{
		values[i] = i+1;
	}
}


int BitSet::add_value(const int x, const int y)//работает
{
	if((x < Ox.get_min()) || (x > Ox.get_max()))
	{
		return ERROR_OUT;
	}
	if((y < Oy.get_min()) || (y > Oy.get_max()))
	{
		return ERROR_OUT;
	}

	values[(Oy.get_max() - y) * Ox.get_lenght() + (x - Ox.get_min())] = -((Oy.get_max() - y) * Ox.get_lenght() + (x - Ox.get_min()) + 1);

	return OK_OUT;	
}

int BitSet::get_value(const int x, const int y)//работает
{
	if((x < Ox.get_min()) || (x > Ox.get_max()))
	{
		return ERROR_OUT;
	}
	if((y < Oy.get_min()) || (y > Oy.get_max()))
	{
		return ERROR_OUT;
	}
	return values[(Oy.get_max() - y) * Ox.get_lenght() + (x - Ox.get_min())] > 0 ? 2 : -2;
}

int BitSet::get_min(const int mode)//???
{
	int min = 0;
	bool flag = false;
	for(int i = 0; i < size; i++)
	{
		if(values[i] < 0)//проверка на принадлежность значения
		{
			if(mode == 1)//по иксу
			{
				if(!flag)
				{
					flag = true;
					min = (-values[i] - 1) % Ox.get_lenght() + Ox.get_min();
				}

				min = min > (-values[i] - 1) % Ox.get_lenght() + Ox.get_min() ? (-values[i] - 1) % Ox.get_lenght() + Ox.get_min() : min;
			}
			if(mode == 0)//по игреку
			{
				if(!flag)
				{
					flag = true;
					min = -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max());
					//printf("\n-((%d - 1)/%d - %d) = %d\n",values[i], Ox.get_lenght(), Oy.get_max(), -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()));
				}
				min = min > -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()) ? -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()) : min;	
				//printf("\n-((%d - 1)/%d - %d) = %d\n",values[i], Ox.get_lenght(), Oy.get_max(), -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()));

			}
		}
	}	
	return min;
}

int BitSet::get_max(const int mode)//???
{
	int max = 0;
	bool flag = false;
	for(int i = 0; i < size; i++)
	{
		if(values[i] < 0)//проверка на принадлежность значения
		{
			if(mode == 1)//по иксу
			{
				if(!flag)
				{
					flag = true;
					max = (-values[i] - 1) % Ox.get_lenght() + Ox.get_min();
				}

				max = max < (-values[i] - 1) % Ox.get_lenght() + Ox.get_min() ? (-values[i] - 1) % Ox.get_lenght() + Ox.get_min() : max;
			}
			if(mode == 0)//по игреку
			{
				if(!flag)
				{
					flag = true;
					max = -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max());
					//printf("\n-((%d - 1)/%d - %d) = %d\n",values[i], Ox.get_lenght(), Oy.get_max(), -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()));

				}
				max = max < -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()) ? -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()) : max;	
				//printf("\n-((%d - 1)/%d - %d) = %d\n",values[i], Ox.get_lenght(), Oy.get_max(), -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()));
			}
		}
	}	
	return max;
}

int BitSet::get_lenght()
{
	return size;
}


LineSegment BitSet::get_Ox()//???
{
	return Ox;
}

LineSegment BitSet::get_Oy()//???
{
	return Oy;
}

BitSet &BitSet::operator=(const BitSet &object)//???
{
	if(values)
	{
		delete [] values;
	}
	values = nullptr;

	Ox = object.Ox;
	Oy = object.Oy;
	size = object.size;
	values = new int[size];
	for(int i = 0; i < size; i++)
	{
		values[i] = object.values[i];		
	}
	return *this;
}

BitSet BitSet::operator+(const BitSet &object)const //???
{
	BitSet result(Ox, Oy);
	
	for(int i = 0; i < result.size; i++)
	{
		if((values[i] < 0) || (object.values[i] < 0))
		{
			result.values[i] = -(i+1);
		}
	}
	return result;
}

BitSet BitSet::operator*(const BitSet &object)const //???
{
	BitSet result(Ox, Oy);

	for(int i = 0; i < result.size; i++)
	{
		if((values[i] < 0) && (object.values[i] < 0))
		{
			result.values[i] = -(i+1);
		}
	}
	return result;
}

int BitSet::change_area(const LineSegment X, const LineSegment Y)//???
{
	int *temp_x;
	int *temp_y;

	int count = 0;
	int it = 0;


	for(int i = 0; i < size; i++)
	{
		if(values[i] < 0)
		{
			count++;
		}
	}

	temp_x = new int[count];
	temp_y = new int[count];

	for(int i = 0; i < size; i++)
	{
		if(values[i] < 0)
		{
			//printf("\n(%d - 1)mod%d + %d= %d\n",values[i], Ox.get_lenght(), Ox.get_min(), (-values[i] - 1) % Ox.get_lenght() + Ox.get_min());
			temp_x[it] = (-values[i] - 1) % Ox.get_lenght() + Ox.get_min();
			//printf("\n-((%d - 1)/%d - %d) = %d\n",values[i], Ox.get_lenght(), Oy.get_max(), -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max()));
			temp_y[it] = -((-values[i] - 1) / Ox.get_lenght() - Oy.get_max());
			it++;
		}
	}

	Ox = X;
	Oy = Y;

	size = Ox.get_lenght() * Oy.get_lenght();

	delete [] values;
	values = new int[size];

	for(int i = 0; i < size; i++)
	{
		values[i] = i+1;
	} 
	//printf("%d", count);
	for(int i = 0; i < count; i++)
	{
		if((temp_x[i] < Ox.get_min()) || (temp_x[i] > Ox.get_max()))
		{
			delete [] temp_x;
			delete [] temp_y;
			return ERROR_OUT;
		}
		if((temp_y[i] < Oy.get_min()) || (temp_y[i] > Oy.get_max()))
		{
			delete [] temp_x;
			delete [] temp_y;
			return ERROR_OUT;
		}
		values[(Oy.get_max() - temp_y[i]) * Ox.get_lenght() + (temp_x[i] - Ox.get_min())] = -((Oy.get_max() - temp_y[i]) * Ox.get_lenght() + (temp_x[i] - Ox.get_min()) + 1);
	}
	delete [] temp_x;
	delete [] temp_y;
	return OK_OUT;
}

int BitSet::count_points()
{
	int count = 0;
	for(int i = 0; i < size; i++)
	{
		if(values[i] < 0)
		{
			count++;
		}
	}
	return count;
}

int BitSet::get_point(int it)
{
	int count = 0;
	int iter = 0;
	for(int i = 0; i < size; i++)
	{
		if(values[i] < 0)
		{
			count++;
		}
	}

	for(int i = 0; i < size; i++)
	{
		if(values[i] < 0)
		{
			if(iter == it)
			{
				return i;
			}
			iter++;
		}
	}
	return -1;
}


BitSet::~BitSet() //работает
{
	delete [] values;
	size = 0;
	Oy.set_segment(0, 0);
	Ox.set_segment(0, 0);
}

int rBitSet(FILE *input, BitSet &object, LineSegment X, LineSegment Y) //
{
	int size;

	object.Ox = X;
	object.Oy = Y;

	object.size = object.Ox.get_lenght() * object.Oy.get_lenght();
	
	fprintf(stdout, "\nВведите кол-во точек в подмножестве: ");

	if(fscanf(input, "%d", &size) != 1)
	{
		return ERROR_OUT;
	}

	if((size < 0) || (size > object.size))
	{
		return ERROR_OUT;
	} 

	object.values = new int[object.size];

	for(int i = 0; i < object.size; i++)
	{
		object.values[i] = i + 1;
	}

	fprintf(stdout, "\nПоследовательно введите %d точек:\n", size);	

	for(int i = 0; i < size; i++)
	{
		int x, y;
		if(fscanf(input, "%d %d", &x, &y) != 2)
		{
			return ERROR_OUT;
		}
		if(object.add_value(x, y))
		{
			return ERROR_OUT;
		}	
	} 
	return OK_OUT;
}

void wBitSet(FILE *output, BitSet &object) //
{
	for(int i = 0; i < object.Oy.get_lenght(); i++)
	{
		fprintf(output, "\n");
		fprintf(output, "%d ||", object.Oy.get_max() - i);
		for(int j = 0; j < object.Ox.get_lenght(); j++)
		{
			if(object.values[i * object.Ox.get_lenght() + j] > 0)
			{
				fprintf(output, "\t.");
			}
			if(object.values[i * object.Ox.get_lenght() + j] < 0)
			{
				fprintf(output, "\t@");
			}
		}
	}
	fprintf(output, "\n* ||");
	for(int j = 0; j < object.Ox.get_lenght(); j++)
	{
		fprintf(output, "\t=");
	}
	fprintf(output, "\n* ||");
	for(int j = 0; j < object.Ox.get_lenght(); j++)
	{
		fprintf(output, "\t%d", object.Ox.get_min() + j);
	}
	fprintf(output, "\n");
}
