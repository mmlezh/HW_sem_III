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

#define SHOW 0
#define DEL 1
#define DEL_POINT 2
#define ADD_POINT 3
#define CHECK_POINT 4
#define MIN_MAX 5
#define GET_POINT 6
#define UNION 7
#define INTERSEC 8
#define CHANGE_AREA 9
#define GET_AREA 10
#define EXIT 11


using namespace std;

int interface(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);

void manual_func(FILE *output);
int Show_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int Delfunc(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int DelPoint_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int AddPoint_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int CheckPoint_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int MinMax_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int GetPoint_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int Union_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int Intersec_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int ChangeArea_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);
int GetArea_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets);

int main(int argc, char **argv)
{
	int min_x, min_y, max_x, max_y;
	LineSegment X, Y;
	BitSet *Sets;
	int num_of_sets;
	FILE *input;
	if(argc > 1)
	{
		if((input = fopen(argv[1], "r")) == NULL)
		{
			return ERROR_OUT;
		}

		fprintf(stdout, "\nВведите границы по X: ");
		if(fscanf(input, "%d %d", &min_x, &max_x) != 2)
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}
	
		fprintf(stdout, "\nВведите границы по Y: ");
 		if(fscanf(input, "%d %d", &min_y, &max_y) != 2)
 		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
 			return ERROR_OUT;
 		}
 	
 		if((min_x > max_x)||(min_y > max_y))
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}
	
		X.set_segment(min_x, max_x);
		Y.set_segment(min_y, max_y);

		fprintf(stdout, "\nВведите кол-во подмножеств: ");
		if(fscanf(input, "%d", &num_of_sets) != 1)
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}

		if(num_of_sets <= 0)
		{
			return ERROR_OUT;
		}

		Sets = new BitSet[num_of_sets];

		for(int i = 0 ; i <  num_of_sets; i++)
		{
			if(rBitSet(input, Sets[i], X, Y))
			{
				fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");			
				return ERROR_OUT;
			}		
		}
	
		for(int i = 0; i < num_of_sets; i++)
		{
			fprintf(stdout, "Подмножество №%d: \n", i);
			wBitSet(stdout, Sets[i]);
			fprintf(stdout, "\n");
		}

		if(interface(input, stdout, Sets, num_of_sets))
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}

		fclose(input);	
	}else{
		fprintf(stdout, "\nВведите границы по X: ");
		if(fscanf(stdin, "%d %d", &min_x, &max_x) != 2)
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}
		
		fprintf(stdout, "\nВведите границы по Y: ");
	 	if(fscanf(stdin, "%d %d", &min_y, &max_y) != 2)
	 	{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
	 		return ERROR_OUT;
	 	}
	 	
	 	if((min_x > max_x)||(min_y > max_y))
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}
		
		X.set_segment(min_x, max_x);
		Y.set_segment(min_y, max_y);

		fprintf(stdout, "\nВведите кол-во подмножеств: ");
		if(fscanf(stdin, "%d", &num_of_sets) != 1)
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}

		if(num_of_sets <= 0)
		{
			return ERROR_OUT;
		}

		Sets = new BitSet[num_of_sets];

		for(int i = 0 ; i <  num_of_sets; i++)
		{
			if(rBitSet(stdin, Sets[i], X, Y))
			{
				fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");			
				return ERROR_OUT;
			}		
		}
		
		for(int i = 0; i < num_of_sets; i++)
		{
			fprintf(stdout, "Подмножество №%d: \n", i);
			wBitSet(stdout, Sets[i]);
			fprintf(stdout, "\n");
		}

		if(interface(stdin, stdout, Sets, num_of_sets))
		{
			fprintf(stdout, "\nОШИБКА СЧИТЫВАНИЯ ");
			return ERROR_OUT;
		}
	}

	delete [] Sets;

	return 0;
}

void manual_func(FILE *output)
{
	fprintf(output, 
		"\n Команды:\n 0 - показать множество\n 1 - очистка множества\n 2 - удаление заданного значения\n 3 - добавление заданного значения\n 4 - проверка принадлежности заданного значения множеству\n 5 - получение max и min значений, содержащихся в множестве (огр. прямоуг.)\n 6 - получение точки множества\n 7 - объединение множеств\n 8 - пересечение множеств\n 9 - изменение диапазона допустимых элементов\n 10 - получение границ текущего диапазона множества\n 11 - выход\n");
}

int Show_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int it_set;
	fprintf(output, "Введите номер множества: ");
	if(fscanf(input, "%d", &it_set) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_set >= num_of_sets) || (it_set < 0))
	{
		return ERROR_OUT;
	}

	wBitSet(output, Sets[it_set]);

	return OK_OUT;	
}

int Del_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int it_set;
	if(fscanf(input, "%d", &it_set) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_set >= num_of_sets) || (it_set < 0))
	{
		return ERROR_OUT;
	}

	Sets[it_set].delete_all();

	return OK_OUT;
}

int DelPoint_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int it_set;
	int x_pt, y_pt;
	fprintf(output, "\nВведите номер множества: ");
	if(fscanf(input, "%d", &it_set) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_set >= num_of_sets) || (it_set < 0))
	{
		return ERROR_OUT;
	}
	fprintf(output, "\nВведите координаты точки: ");
	if(fscanf(input, "%d %d", &x_pt, &y_pt) != 2)
	{
		return ERROR_OUT;
	}

	printf("\n%d %d\n", x_pt, y_pt);
	if(Sets[it_set].delete_value(x_pt, y_pt))
	{
		return ERROR_OUT;
	}
	return OK_OUT;
}

int AddPoint_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int it_set;
	int x_pt, y_pt;
	fprintf(output, "\nВведите номер множества: ");
	if(fscanf(input, "%d", &it_set) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_set >= num_of_sets) || (it_set < 0))
	{
		return ERROR_OUT;
	}
	fprintf(output, "\nВведите координаты точки: ");	
	if(fscanf(input, "%d %d", &x_pt, &y_pt) != 2)
	{	
		return ERROR_OUT;
	}

	if(Sets[it_set].add_value(x_pt, y_pt))
	{
		return ERROR_OUT;
	}
	return OK_OUT;
}

int CheckPoint_func(FILE *input, FILE* output, BitSet *Sets, int num_of_sets)
{
	int it_set;
	int x_pt, y_pt;
	fprintf(output, "\nВведите номер множества: ");
	if(fscanf(input, "%d", &it_set) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_set >= num_of_sets) || (it_set < 0))
	{
		return ERROR_OUT;
	}
	fprintf(output, "\nВведите координаты точки: ");
	if(fscanf(input, "%d %d", &x_pt, &y_pt) != 2)
	{
		return ERROR_OUT;
	}
	if(Sets[it_set].get_value(x_pt, y_pt) == -2)
	{
		fprintf(output,"Принадлежит");
	}
	if(Sets[it_set].get_value(x_pt, y_pt) == 2)
	{
		fprintf(output,"Не принадлежит");
	}
	if(Sets[it_set].get_value(x_pt, y_pt) == ERROR_OUT)
	{
		return ERROR_OUT;
	}
	return OK_OUT;
}

int MinMax_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int min, max;
	int it_set;
	fprintf(output, "\nВведите номер множества: ");
	if(fscanf(input, "%d", &it_set) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_set >= num_of_sets) || (it_set < 0))
	{
		return ERROR_OUT;
	}
	fprintf(output, "\nМножество лежит в прямоугольнике: [%d, %d] x [%d, %d]", Sets[it_set].get_min(1), Sets[it_set].get_max(1), Sets[it_set].get_min(0), Sets[it_set].get_max(0));
	return OK_OUT;
}

int GetPoint_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int it_set;
	int it_pt;
	int it_val;
	int num_of_points;

	fprintf(output, "\nВведите номер множества: ");
	if(fscanf(input, "%d", &it_set) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_set >= num_of_sets) || (it_set < 0))
	{
		return ERROR_OUT;
	}

	num_of_points = Sets[it_set].count_points();
	fprintf(output, "\nВведите номер точки: ");
	if(fscanf(input, "%d", &it_pt) != 1)
	{	
		return ERROR_OUT;
	}
	if((it_pt >= num_of_points) || (it_pt < 0))
	{
		return ERROR_OUT;
	}

	it_val = Sets[it_set].get_point(it_pt);

	if(it_val == -1)
	{
		return ERROR_OUT;
	}

	//fprintf(output, " (%d, %d) ", (it_val - 1) % Sets[it_set].get_Ox().get_lenght() + Sets[it_set].get_Ox().get_min(), -((it_val - 1) / Sets[it_set].get_Ox().get_lenght() - Sets[it_set].get_Oy().get_max()));
	fprintf(output, " (%d, %d) ", it_val % Sets[it_set].get_Ox().get_lenght() + Sets[it_set].get_Ox().get_min(), -(it_val / Sets[it_set].get_Ox().get_lenght() - Sets[it_set].get_Oy().get_max()));
	return OK_OUT;
}


int Union_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int it_set1, it_set2;
	BitSet Res;
	fprintf(output, "\nВведите номера множеств: ");
	if(fscanf(input, "%d %d", &it_set1, &it_set2) != 2)
	{	
		return ERROR_OUT;
	}
	if((it_set1 >= num_of_sets) || (it_set1 < 0))
	{
		return ERROR_OUT;
	}
	if((it_set2 >= num_of_sets) || (it_set2 < 0))
	{
		return ERROR_OUT;
	}

	Res = Sets[it_set1] + Sets[it_set2];
	wBitSet(output, Res);
	return OK_OUT;
}

int Intersec_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int it_set1, it_set2;
	BitSet Res;
	fprintf(output, "\nВведите номера множеств: ");
	if(fscanf(input, "%d %d", &it_set1, &it_set2) != 2)
	{	
		return ERROR_OUT;
	}
	if((it_set1 >= num_of_sets) || (it_set1 < 0))
	{
		return ERROR_OUT;
	}
	if((it_set2 >= num_of_sets) || (it_set2 < 0))
	{
		return ERROR_OUT;
	}

	Res = Sets[it_set1] * Sets[it_set2];
	wBitSet(output, Res);
	return OK_OUT;
}

int ChangeArea_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	int min_x, max_x;
	int min_y, max_y;
	LineSegment newX, newY;
	fprintf(output, "Введите новые границы по X: ");
	if(fscanf(input, "%d %d", &min_x, &max_x) != 2)
	{	
		return ERROR_OUT;
	}
	fprintf(output, "Введите новые границы по Y: ");
	if(fscanf(input, "%d %d", &min_y, &max_y) != 2)
	{	
		return ERROR_OUT;
	}

	newX.set_segment(min_x, max_x);
	newY.set_segment(min_y, max_y);

	// if((Sets[0].get_Ox().get_min() < min_x)||(Sets[0].get_Ox().get_max() > max_x) || (Sets[0].get_Oy().get_min() < min_y) || (Sets[0].get_Oy().get_min() > max_y))
	// {
	// 	return ERROR_OUT;
	// }

	for(int i = 0; i < num_of_sets; i++)
	{
		if(Sets[i].change_area(newX, newY))
		{
			return ERROR_OUT;
		}
	}
	return OK_OUT;
}

int GetArea_func(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	fprintf(output, "\nМножество является подмножеством: [%d, %d] x [%d, %d]", Sets[0].get_Ox().get_min(), Sets[0].get_Ox().get_max(), Sets[0].get_Oy().get_min(), Sets[0].get_Oy().get_max());
	return OK_OUT;
}

int interface(FILE *input, FILE *output, BitSet *Sets, int num_of_sets)
{
	bool flag = true;
	int com;
	fprintf(output,"\n Задайте команду: ");
	while(flag)
	{
		manual_func(output);
		if(fscanf(input, "%d", &com) != 1)
		{
			return ERROR_OUT;
		}
		fprintf(output, "\nВы ввели: %d\n", com);
		switch(com)
		{
			case SHOW: //работает
				if(Show_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}	
				break;
			case DEL: //работает
				fprintf(output, "DEL\n");
				if(Del_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}
				break;
			case DEL_POINT: //работает
				fprintf(output, "DEL POINT\n");
				if(DelPoint_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}
				break;
			case ADD_POINT: //работает
				fprintf(output, "ADD POINT\n");
				if(AddPoint_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}
				break;
			case CHECK_POINT: //работает
				fprintf(output, "CHECK POINT\n");
				if(CheckPoint_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}
				break;
			case MIN_MAX: //работает
				fprintf(output, "MIN MAX\n");
				if(MinMax_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}
				break;
			case GET_POINT:
				fprintf(output, "GET POINT");
				if(GetPoint_func(input, output, Sets, num_of_sets))
				{
					fprintf(output, "Некорректный ввод");
				}
				break;
			case UNION: //работает
				fprintf(output, "UNION\n");
				if(Union_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}
				break;
			case INTERSEC: //работает
				fprintf(output, "INTERSEC\n");
				if(Intersec_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
				}
				break;
			case CHANGE_AREA: //работает
				fprintf(output, "CHANGE AREA\n");
				if(ChangeArea_func(input, output, Sets, num_of_sets))
				{
					fprintf(output,"Некорректный ввод");
					return ERROR_OUT;
				}
				break;
			case GET_AREA: //работает
				fprintf(output, "GET AREA\n");
				if(GetArea_func(input, output, Sets, num_of_sets))
				{
				 	fprintf(output,"Некорректный ввод");
				}
				break;
			case EXIT:
				flag = false;
				break;
			default:
				fprintf(output,"\nТакой команды нет\n");
				break;
		}
		fprintf(output, "\nЗадайте команду: ");
	}
	return OK_OUT;
}
