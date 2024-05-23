#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/////////////////////////////////////////////////////////////////
#define INTERSEC -4
#define CROSS -3
#define SAME -2
#define PARALLEL -1
#define EPS 2e-14
#define ERROR_OUT 1
#define ON_POLY 2
#define IN_POLY 3
#define OUT_POLY 4

/////////////////////////////////////////////////////////////////

struct point 
{
	double x;
	double y;

	struct line *l1;
	struct line *l2;
};

struct line
{
	double A;
	double B;
	double C;

	struct point *p1;
	struct point *p2;
};

/////////////////////////////////////////////////////////////////

struct point *polygon_scaning(FILE *input, int *size, struct point *min, struct point *max, struct point *dot); //считывает массив точек(вершин) из открытого файла
struct line *construct_edges(struct point *polygon, int size); //по считанным вершинам строит уравнения прямых(граней многоугольника)
int do_the_lines_cross(struct line *line1, struct line *line2, struct point *cross_point); //по двум прямым определяет их отношение и выводит его, если пересекается перезаписывает точку перечечения
void show_polygon(struct line *polygon, int size); //выводит многогранник по точкам
void initialization_of_main_structures(struct point *min, struct point *max, struct point *base_dot, struct point *main_dot, struct line *cross_line);
int num_of_intersections(struct line *edges, struct line *cross_line, int size);
int check(struct line *edges, struct point *main_dot, struct line *cross_line, struct point *min, struct point *max, int size);

/////////////////////////////////////////////////////////////////

int main(int argc, char *argv[argc])
{
	FILE *input;
	int size = 0;
	int cross_num = 0;

	struct point *polygon = NULL;
	struct point main_dot;
	struct point base_dot;

	struct point min;
	struct point max;

	struct line *edges = NULL;
	struct line cross_line;

	if((input = fopen(argv[1], "r")) == NULL)
	{
		printf("\n ОШИБКА ФАЙЛА: Неудалось открыть файл. \n");
		return ERROR_OUT;
	}

	if((polygon = polygon_scaning(input, &size, &min, &max, &main_dot)) == NULL)
		return ERROR_OUT;

	edges = construct_edges(polygon, size);

	show_polygon(edges, size);

	printf("\n Многоугольник заключен в прямоугольник: y_max=(%.2lf) x_max=(%.2lf) y_min=(%.2lf) x_min=(%.2lf)\n", max.y, max.x, min.y, min.x);

	initialization_of_main_structures(&min, &max, &base_dot, &main_dot, &cross_line);

	printf("Точка для проверки: (%.2lf, %.2lf) и опорная точка: (%.2lf, %.2lf)\n", main_dot.x, main_dot.y, base_dot.x, base_dot.y);	\

	printf("(%.2lf)*x + (%.2lf)*y + (%.2lf) = 0", cross_line.A, cross_line.B, cross_line.C);

	cross_num = num_of_intersections(edges, &cross_line, size);

	printf("\nКол-во пересечений базисной линии с многоугольником: %d\n", cross_num);

	printf("\nВердикт: ");

	cross_num = check(edges, &main_dot, &cross_line, &min, &max, size);
	if(cross_num == ON_POLY)
		printf("точка принадлежит границе\n");
	if(cross_num == IN_POLY)
		printf("точка принадлежит внутренности многоугольника\n");
	if(cross_num == OUT_POLY)
		printf("точка лежит вне многоугольника\n");
	free(polygon);
	free(edges);

	fclose(input);

	return 0;
}

/////////////////////////////////////////////////////////////////

struct point *polygon_scaning(FILE *input, int *size, struct point *min, struct point *max, struct point *dot) 
{
	int cnum = 0;
	double temp;

	struct point *polygon = NULL;

	while(fscanf(input, "%lf ", &temp) == 1)
	{
		if(cnum == 0)
		{
			min->x = temp;
			max->x = temp;
		}
		if(cnum == 1)
		{
			min->y = temp;
			max->y = temp;
		}
		cnum++;
	}	

	if((!feof(input)) || ((cnum % 2 != 0) && (cnum < 8))) {
		printf("Некорректный ввод\n");
		return NULL;
	}

	if(cnum < 8) 
	{
		printf("Вырожденый многоугольник.\n");
	}

	*size = (cnum/2)-1; 
	polygon = malloc(*size * sizeof(struct point));

	rewind(input);

	for(int i = 0; i < *size; i++)
	{
		fscanf(input, "%lf %lf ", &polygon[i].x, &polygon[i].y);
		
		if(min->x >= polygon[i].x)
			min->x = polygon[i].x;

		if(max->x <= polygon[i].x) 
			max->x = polygon[i].x;

		if(min->y >= polygon[i].y)
			min->y = polygon[i].y;
		
	 	if(max->y <= polygon[i].y)
			max->y = polygon[i].y;

		polygon[i].l1 = NULL;
		polygon[i].l2 =	NULL;
	}
	
	fscanf(input, "%lf %lf ", &dot->x, &dot->y);

	return polygon;
}

struct line *construct_edges(struct point *polygon, int size)
{
	struct line *edges = NULL;
	edges = malloc(size * sizeof(struct line));
	for(int i = 0; i < size; i++)
	{
		edges[i].A = (polygon[(i+1) % size].y - polygon[i].y);
		edges[i].B = (polygon[(i)].x - polygon[(i+1) % size].x);
		edges[i].C = polygon[i].y * (polygon[(i+1) % size].x - polygon[i].x) + polygon[i].x * (polygon[i].y - polygon[(i+1) % size].y); 

		edges[i].p1 = &polygon[i];
		edges[i].p2 = &polygon[(i+1) % size];
	}
	return edges;
} 

void show_polygon(struct line *edges, int size) 
{
	for(int i = 0; i < size; i++)
	{
		printf("точка %d: %.2lf %.2lf\n", i, edges[i].p1->x, edges[i].p1->y);
		printf("\t (%.2lf)*x + (%.2lf)*y + (%.2lf) = 0\n", edges[i].A, edges[i].B, edges[i].C);
	}
}

int do_the_lines_cross(struct line *line, struct line *cross_line, struct point *cross_point)
{
	double det = 0;
	double det_x = 0;
	double det_y = 0;

	double temp_min_x;
	double temp_max_x;

	det = line->A * cross_line->B - cross_line->A * line->B;
	det_x = (-line->C) * cross_line->B - (-cross_line->C) * line->B;
	det_y = line->A * (-cross_line->C) - cross_line->A * (-line->C);

	temp_max_x = (line->p1->x > line->p2->x) ? line->p1->x : line->p2->x;
	temp_min_x = (line->p1->x < line->p2->x) ? line->p1->x : line->p2->x;

	if(det)
	{
		//printf("\n \n (%.2lf, %.2lf) (%.2lf, %.2lf) (%.2lf, %.2lf)\n%d\n%d\n", line->p1->x , line->p2->x , temp_max_x, temp_min_x, det_x/det, det_y/det, (temp_max_x >= det_x/det),(temp_min_x <= det_x/det) );
		if((temp_max_x >= det_x/det) && (temp_min_x <= det_x/det))
		{
			cross_point->x = det_x/det;
			cross_point->y = det_y/det;
			cross_point->l1 = line;
			cross_point->l2 = cross_line;
			return CROSS;
		}
		cross_point->x = 0;
		cross_point->y = 0;
		cross_point->l1 = NULL;
		cross_point->l2 = NULL;
		return INTERSEC;
	} else {
		if(det_y || det_x) 
		{
			cross_point->x = 0;
			cross_point->y = 0;
			cross_point->l1 = NULL;
			cross_point->l2 = NULL;
			return PARALLEL;
		} else {
			cross_point->x = 0;
			cross_point->y = 0;
			cross_point->l1 = NULL;
			cross_point->l2 = NULL;
			return SAME;
		}
	}
}

int num_of_intersections(struct line *edges, struct line *cross_line, int size)
{
	int flag = 0;
	int cross_num = 0;

	int x_direction = 0;
	int y_direction = 0;

	if(cross_line->p2->x - cross_line->p1->x > 0)
		x_direction = 1;
	if(cross_line->p2->x - cross_line->p1->x < 0)
		x_direction = -1;

	if(cross_line->p2->y - cross_line->p1->y > 0)
		y_direction = 1;
	if(cross_line->p2->y - cross_line->p1->y < 0)
		y_direction = -1;

	for(int i = 0; i < size; i++)
	{
		struct point temp_cross_point;
		int temp_x_direction = 0;
		int temp_y_direction = 0;

		flag = do_the_lines_cross(&edges[i], cross_line, &temp_cross_point);
		//printf("%d\n", flag);

		if(temp_cross_point.x - cross_line->p1->x > 0)
			temp_x_direction = 1;
		if(temp_cross_point.x - cross_line->p1->x < 0)
			temp_x_direction = -1;

		if(temp_cross_point.y - cross_line->p1->y > 0)
			temp_y_direction = 1;
		if(temp_cross_point.y - cross_line->p1->y < 0)
			temp_y_direction = -1;

		if((flag == CROSS) && ((fabs(temp_cross_point.x - edges[i].p2->x) > EPS) || (fabs(temp_cross_point.y - edges[i].p2->y) > EPS)))
		{
			if((temp_x_direction == x_direction)&&(temp_y_direction == y_direction))
			{
				cross_num++;
			}
		}
	}
	return cross_num;
}

void initialization_of_main_structures(struct point *min, struct point *max, struct point *base_dot, struct point *main_dot, struct line *cross_line)
{
	base_dot->x = (max->x + min->x)/2;
	base_dot->y = (max->y + min->y)/2;

	cross_line->A = (base_dot->y - main_dot->y);
	cross_line->B = (main_dot->x - base_dot->x);
	cross_line->C = main_dot->y * (base_dot->x - main_dot->x) + main_dot->x * (main_dot->y - base_dot->y);
	cross_line->p1 = main_dot;
	cross_line->p2 = base_dot;
}

int check(struct line *edges, struct point *main_dot, struct line *cross_line, struct point *min, struct point *max, int size)
{
	int cross_num = 0;

	if((main_dot->x < min->x ) || (main_dot->x > max->x) || (main_dot->y < min->y) || (main_dot->y > max->y)) 
		return OUT_POLY;
	//проверка принадлежности границе
	for(int i = 0; i < size; i++) 
	{
		double temp_max_x, temp_min_x, temp_max_y, temp_min_y;
		//temp_max_X = (polygon[i].X > polygon[(i+1)%size].X) ? polygon[i].X : polygon[(i+1)%size].X;
		temp_max_x = (edges[i].p1->x > edges[i].p2->x) ? edges[i].p1->x : edges[i].p2->x;
		
		//temp_min_X = (polygon[i].X < polygon[(i+1)%size].X) ? polygon[i].X : polygon[(i+1)%size].X; 
		temp_min_x = (edges[i].p1->x < edges[i].p2->x) ? edges[i].p1->x : edges[i].p2->x;
 		
 		if(fabs(edges[i].A * main_dot->x + edges[i].B * main_dot->y + edges[i].C) < EPS)//принадлежит ли точка прямой?
 		{
			if((main_dot->x >= temp_min_x) && (main_dot->x <= temp_max_x))//проверка навыход из рамки
			{
				return ON_POLY; 
			}
		} 
	}

	cross_num = num_of_intersections(edges, cross_line, size);

	if(cross_num%2)
	{
		return IN_POLY; 
	}

	return OUT_POLY;
}