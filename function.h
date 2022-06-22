// Список всех используемых функций для генерации и отрисовки лабиринта.
#include "gL/gl.h"
#include <map>
#include <vector>
#include <iostream>
#ifndef FRICK_FUNCTION_H
#define FRICK_FUNCTION_H


LRESULT CALLBACK WindowProc(HWND HWND, UINT UNIT, WPARAM WPARAM, LPARAM LPARAM);
/*
 * Функция для обраотки вззаимодействия с окном в том числе нахождения курсора.
 * UNIT - это код сообщения;
 * WPARAM - флаг, указывающий, было ли окно свернуто, развернуто или изменено;
 * LPARAM - содержит новую ширину и высоту окна при взаимодействии с ним.
 */
void EnableOpenGL(HWND hwnd, HDC* HDC, HGLRC* HGLRC);
void DisableOpenGL(HWND HWND, HDC HDC, HGLRC HGLRC);
 /*
 * EnableOpenGL и DisableOpenGL - открытие и закрытие отрисовки GL
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
/*
 * Замена main для работы с любыми GUI приложениями, используется для явного обращения к Windows и получения данных.
 * hInstance - значением аргумента является базовый адрес образа памяти исполняемого файла;
 * hPrevInstance - дескриптор предыдущего экземпляра приложения (почти всегда равен 0);
 * lpCmdLine - командная строка приложения, исключая имя программы;
 * nCmdShow - управляет отображением окна.
 */


void compare(std::vector<int> &current,bool &back,bool &right,bool &forw,bool &left,bool &bot,bool &top);
/*
 * Функцию compare мы используем для загрузки индексов отрисовываемых фигур во временный массив индексов единичного куба.
 * current - временный вектор;
 * back - существует ли соседняя нода в лабиринте сзади;
 * right - существует ли соседняя нода в лабиринте справа;
 * forw - существует ли соседняя нода в лабиринте спереди;
 * left - существует ли соседняя нода в лабиринте слева;
 * bot- существует ли соседняя нода в лабиринте снизу;
 * top - существует ли соседняя нода в лабиринте сверху.
 */
void texindForm(int c,std::vector<int> &v2,std::vector <std::vector <int>> &baseInd);
/*
 * Функция texindForm формирует описанный ранее двумерный вектор индексов.
 * baseInd - двумерный вектор, в котором для каждого индекса единичного куба лежит набор индексов отрисовываемых текстур;
 * c - хранит в себе высоту нашего лабиринта;
 * v2 - ссылка на сформированный в generation массив индексов.
 */
void Load_Texture();
/*
 * Создает текстуру нашего любимого CodeBlocks и записывает его в texture.
 */
void Win_Resize(int x, int y);
/*
 * Функция изменяет настройки проекции в зависимости от области вывода.
 * x - длина окна;
 * y - ширина окна;
 */
void GameInit();
/*
 * Инициализация, запусткаемая до цикла отрисовки, в которой мы
 */
void Player_Move();
/*
 * Если окно игры в фокусе пользователя, то включает движение игрока мышью.
 */
void ShowWorld(float *vert,GLuint *ind, float *ppp, int ind_size, int vert_size,float *tex_coord,float *vertex,std::vector <std::vector <int>> &baseInd);
/*
 * Главная функция игры, каждый тик отрисовывая картинку мира.
 * vert - массив вершин каждой ноды;
 * ind - массив индексов каждой ноды;
 * ppp - координаты вершин последнего квадрата;
 * ind_size - длина массива индексов;
 * vert_size - длина массива вершин;
 * tex_coord - массив текстурных координат единичного куба;
 * vertex - массив вершин единичного куба.
 * baseInd - двумерный вектор, в котором для каждого индекса единичного куба лежит набор индексов отрисовываемых текстур;
 */

const int coordinatex=2;
const int coordinatey =2;
const int coordinatez =2;
const float x_weight = 0.3;
const float y_weight = 0.3;
const float z_weight = 0.3;
/*
 * coordinatex - размер лабиринта по оси x;
 * coordinatey - размер лабиринта по оси y;
 * coordinatez - размер лабиринта по оси z;
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


template<typename my_type>
auto m_print(std::vector<std::vector<std::vector<my_type>>> &maze) -> void;

struct Point;

auto comp(std::pair<char, int> &a, std::pair<char, int> &b) -> bool;

auto gen(size_t side_x, size_t side_y, size_t side_z, float weightx, float weighty, float weightz,
         std::vector<float> &vertex, std::vector<int> &index) -> Point;

auto cost(Point p0, std::map<Point, std::vector<Point>> &maze, std::map<Point, std::pair<int, int>> &vert_ind) -> void;

auto cleaning(std::vector<int>& v) -> void;

#endif //FRICK_FUNCTION_H

