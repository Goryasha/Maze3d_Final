//// Список всех используемых функций для генерации и отрисовки лабиринта.
#include "gL/gl.h"
#include <map>
#include <vector>
#include <iostream>

#ifndef FRICK_FUNCTION_H
#define FRICK_FUNCTION_H

/**
 * Функция для обраотки вззаимодействия с окном в том числе нахождения курсора.
 * @param HWND - маркер окна Windows, показывающий верхнее открытое окно;
 * @param UNIT - это код сообщения;
 * @param WPARAM - флаг, указывающий, было ли окно свернуто, развернуто или изменено;
 * @param LPARAM - содержит новую ширину и высоту окна при взаимодействии с ним.
 * @return 0.
 */
LRESULT CALLBACK WindowProc(HWND HWND, UINT UNIT, WPARAM WPARAM, LPARAM LPARAM);

/**
 * Разрешение отрисовки GL.
 * @param hwnd - маркер окна Windows, показывающий верхнее открытое окно;
 * @param HDC - содержит сведения об атрибутах рисования устройства;
 * @param HGLRC - содержит контекст воспроизведения OpenGL.
 */
void EnableOpenGL(HWND hwnd, HDC *HDC, HGLRC *HGLRC);

/**
 * Запрет отрисовки GL.
 * @param HWND - маркер окна Windows, показывающий верхнее открытое окно;
 * @param HDC - содержит сведения об атрибутах рисования устройства;
 * @param HGLRC - содержит контекст воспроизведения OpenGL.
 */
void DisableOpenGL(HWND HWND, HDC HDC, HGLRC HGLRC);

/**
 * Замена main для работы с любыми GUI приложениями, используется для явного обращения к Windows и получения данных.
 * @param hInstance - значением аргумента является базовый адрес образа памяти исполняемого файла;
 * @param hPrevInstance - дескриптор предыдущего экземпляра приложения (почти всегда равен 0);
 * @param lpCmdLine - командная строка приложения, исключая имя программы;
 * @param nCmdShow - управляет отображением окна;
 * @return msg.wParam - сообщение о закрытии окна.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

/**
 * Функцию compare мы используем для загрузки индексов отрисовываемых фигур во временный массив индексов единичного куба.
 * @param current - временный вектор;
 * @param back - существует ли соседняя нода в лабиринте сзади;
 * @param right - существует ли соседняя нода в лабиринте справа;
 * @param forw - существует ли соседняя нода в лабиринте спереди;
 * @param left - существует ли соседняя нода в лабиринте слева;
 * @param bot - существует ли соседняя нода в лабиринте снизу;
 * @param top - существует ли соседняя нода в лабиринте сверху.
 */
void compare(std::vector<int> &current, bool &back, bool &right, bool &forw, bool &left, bool &bot, bool &top);

/**
 * Функция texindForm формирует описанный ранее двумерный вектор индексов.
 * @param c - хранит в себе высоту нашего лабиринта;
 * @param v2 - ссылка на сформированный в generation массив индексов.
 * @param baseInd - двумерный вектор, в котором для каждого индекса единичного куба лежит набор индексов отрисовываемых текстур;
 */
void texindForm(int c, std::vector<int> &v2, std::vector<std::vector<int>> &baseInd);

/**
 * Создает текстуру нашего любимого CodeBlocks и записывает его в texture.
 */
void Load_Texture();

/**
 * Функция изменяет настройки проекции в зависимости от области вывода.
 * @param x - длина окна;
 * @param y - ширина окна;
 */
void Win_Resize(int x, int y);

/**
 * Инициализация, запусткаемая до цикла отрисовки, в которой мы создаем текстуры, настраиваем параметры плоскости проекции.
 */
void GameInit();

/**
 * Если окно игры в фокусе пользователя, то включает движение игрока мышью.
 */
void Player_Move();

/**
 * Главная функция игры, каждый тик отрисовывая картинку мира.
 * @param vert - массив вершин каждой ноды;
 * @param ind - массив индексов каждой ноды;
 * @param ppp - координаты вершин последнего квадрата;
 * @param ind_size - длина массива индексов;
 * @param vert_size - длина массива вершин;
 * @param tex_coord - массив текстурных координат единичного куба;
 * @param vertex - массив вершин единичного куба.
 * @param baseInd - двумерный вектор, в котором для каждого индекса единичного куба лежит набор индексов отрисовываемых текстур;
 * @param ind_clear - чистый массив индексов каждой ноды.
 */
void ShowWorld(float *vert, GLuint *ind, float *ppp, int ind_size, int vert_size, float *tex_coord, float *vertex,
               std::vector<std::vector<int>> &baseInd, GLuint *ind_clear);

/**
 * @param coordinatex - размер лабиринта по оси x;
 * @param coordinatey - размер лабиринта по оси y;
 * @param coordinatez - размер лабиринта по оси z;
 * @param x_weight - приоритет создания прохода по оси x;
 * @param y_weight - приоритет создания прохода по оси y;
 * @param z_weight - приоритет создания прохода по оси z;
 */
const int coordinatex = 5;
const int coordinatey = 5;
const int coordinatez = 5;
const float x_weight = 0.3;
const float y_weight = 0.3;
const float z_weight = 0.3;


/**
 * структура Точка(координата x, координата y, координата z)
 * функция cor() выводит координаты точки
 */
struct Point {
    size_t x;
    size_t y;
    size_t z;

    Point(size_t x, size_t y, size_t z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void cor(int k = 1) const {
        if (k == 1)
            std::cout << x << ' ' << y << ' ' << z << ' ';
        else
            std::cout << x << ' ' << y << ' ' << z << '\n';
    }

    bool operator<(const Point &right) const {
        if (x < right.x)
            return true;
        else if (x == right.x) {
            if (y < right.y)
                return true;
            else if (y == right.y) {
                return z < right.z;
            }
        }
        return false;
    }
};

/**
 * m_print() - выводит список смежности лабиринта
 * @param maze список смежности лабиринта
 */
auto m_print(std::map<Point, std::vector<Point>> &maze) -> void;

auto comp(std::pair<char, int> &a, std::pair<char, int> &b) -> bool;

/**
 * gen() - функция генерирующая лабиринт и записывающая его структуру в два вектора
 * @param side_x размер лабиринта по x
 * @param side_y размер лабиринта по y
 * @param side_z размер лабиринта по z
 * @param weightx приоритет создания прохода по x
 * @param weighty приоритет создания прохода по y
 * @param weightz приоритет создания прохода по z
 * @param vertex ссылка на вектор, в котором будут храниться вершины
 * @param index индексы вершин из вектора vertex, которые надо попарно соединить
 */
auto gen(size_t side_x, size_t side_y, size_t side_z, float weightx, float weighty, float weightz,
         std::vector<float> &vertex, std::vector<int> &index) -> Point;

/**
 * функция, расставляющая для каждой вершины кол-во вершин от неё до дерева + 1
 * @param p0 вершина, которую рассматриваем на каждой итерации
 * @param maze словарь вершин, где для каждой значением является вектор точек, с которыми они соединены
 * @param vert_ind словарь, хранящий индексацию вершин и их отдалённость от корня
 */
auto cost(Point p0, std::map<Point, std::vector<Point>> &maze, std::map<Point, std::pair<int, int>> &vert_ind) -> void;

/**
 * принимает вектор и очищает его от пар повторяющихся элементов, порядок элементов в паре не играет роли
 * @param v вектор для очистки
 */
auto cleaning(std::vector<int> &v) -> void;

#endif //FRICK_FUNCTION_H