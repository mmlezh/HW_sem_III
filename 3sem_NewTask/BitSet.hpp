#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define OK_OUT 0
#define ERROR_OUT 1

using namespace std;
/**
 * @class LineSegment
 * @brief класс LineSegment реализует отрезки множества 
 * действительных чисел, впоследствии мы будем брать их декартовы
 * прозведения 
 */
class LineSegment
{
private:
	int min;
	int max;
public:
	/**
     * Перезаписывает private поля min, max
     * @brief Метод изменения отрезка
     * @param new_min The Новая левая граница
     * @param new_max The Новая правая граница 
     */
	void set_segment(const int new_min, const int new_max);
	/**
     * @brief Метод получения левой границы 
     * @return Левая граница отрезка
     */ 
	int get_min();
	/**
     * @brief Метод получения правой границы 
     * @return Правая граница отрезка
     */ 
	int get_max();
	/**
     * @brief Метод получения длины отрезка 
     * @return Длина отрезка
     */ 
	int get_lenght();
};
/**
 * @class BitSet
 * @brief класс BitSet реализует подмножество наперед
 * заданного прямоугольника X*Y 
 */
class BitSet
{
private:
	LineSegment Ox;
	LineSegment Oy;
	int *values;
	int size;
public:
	/**
	 * Конструктор по умолчанию.
     */ 
	BitSet();
	/**
     * Конструирует пустое помножество декартового квадрата X*Y.
     * @brief Конструктор по параметрам
     * @param X первый сомножитель декартового произведения
     * @param Y второй сомножитель декартового произведения
     */
	BitSet(LineSegment X, LineSegment Y);
	/**
     * Конструирует копию элемента класса.
     * @brief Копи-конструктор
     * @param object объект класса, который мы копируем.
     */
	BitSet(BitSet &object);
	/**
     * @brief Метод удаления точки из множества
     * @param x x-овая координата удаляемой точки
     * @param y y-овая координата удаляемой точки
     * @return Возвращает ERROR_OUT если (x, y) непринадлежит X*Y и OK_OUT иначе
     */ 
	int delete_value(const int x, const int y);
	/**
     * @brief Метод очистки множества
     */ 
	void delete_all();
	/**
     * @brief Метод добавления точки в множество
     * @param x x-овая координата добавляемой точки
     * @param y y-овая координата добавляемой точки
     * @return Возвращает ERROR_OUT если (x, y) непринадлежит X*Y и OK_OUT иначе
     */ 
	int add_value(const int x, const int y);
	/**
     * @brief Метод определения принадлежности точки множеству
     * @param x x-овая координата точки, которую мы хотим проверить
     * @param y y-овая координата точки, которую мы хотим проверить 
     * @return Возвращает ERROR_OUT если (x, y) непринадлежит X*Y
     */ 
	int get_value(const int x, const int y);
	/**
     * @brief Метод получения минимальной координаты по X/Y
     * @param mode флаг для определения по какой координате ищем min
     * @return Возвращает значение минимальной координаты точек из множества, если таковых нет, то возвращает 0
     */ 
	int get_min(const int mode);
	/**
     * @brief Метод получения максимальной координаты по X/Y
     * @param mode флаг для определения по какой координате ищем max
     * @return Возвращает значение максимальной координаты точек из множества, если таковых нет, то возвращает 0
     */
	int get_max(const int mode);
	/**
     * @brief Метод получения максимального кол-ва точек в X*Y
     * @return Возвращает максимального кол-ва точек в X*Y
     */
	int get_lenght();
	/**
     * @brief Метод получения X из X*Y
     * @return Возвращает X из X*Y
     */
	LineSegment get_Ox();
	/**
     * @brief Метод получения Y из X*Y
     * @return Возвращает Y из X*Y
     */
	LineSegment get_Oy();
	/**
     * @brief Оператор присваивания
     * @param object Элемент класса, к которому присваиваем
     */
	BitSet &operator=(const BitSet &object);
	/**
     * @brief Оператор объединения
     * @param object Элемент класса, с которым ищем объединение
     * @return Объединение двух ножеств
     */
	BitSet operator+(const BitSet &object)const;
	/**
     * @brief Оператор пересечения
     * @param object Элемент класса, с которым ищем пересечение
     * @return Пересечение двух ножеств
     */
	BitSet operator*(const BitSet &object)const;
	/**
     * @brief Метод изменения области X*Y подмножества которой мы рассматриваем в задаче
     * @param X новая Ox
     * @param Y новая Oy
     * @return ERROR_OUT если не удалось перезаписать точки исходного множества в новое, OK_OUT иначе
     */ 
	int change_area(const LineSegment X, const LineSegment Y);
	/**
     * @brief Метод подсчета точек к множестве
     * @return Кол-во точек в множестве
     */
	int count_points();
	/**
     * @brief Метод получения i-ой точки по счету (в порядке нумерации)
     * @param it номер элемента по порядку
     * @return Номер элемента в массиве, иначе -1
     */
	int get_point(int it);
	/**
     * @brief Деструктор
     */
	~BitSet();

	/**
     * @brief Функция для считывания элемента класса
     * @param input поток из которого мы считываем
     * @param object Элемент класса который мы считываем
     * @param X заранее заданное поле Ox
     * @param Y заранее заданное поле Oy
     * @return ERROR_OUT если ввод некорректный, иначе OK_OUT
     */
	friend int rBitSet(FILE *input, BitSet &object, LineSegment X, LineSegment Y);
	/**
     * @brief Функция для выведения элемента класса
     * @param output поток в который мы выводим
     * @param object Элемент класса который мы выводим
     * @return ERROR_OUT если ввод некорректный, иначе OK_OUT
     */
	friend void wBitSet(FILE *output, BitSet &object);
};