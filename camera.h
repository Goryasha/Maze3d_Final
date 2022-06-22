// Заголовочный файл с функциями для управления камерой

#ifndef FRICK_CAMERA_H
#define FRICK_CAMERA_H

struct SCam{
    float x,y,z;
    float xdeg,zdeg;
};
/*
 * Структура содержащая основные паратетры камеры.
 * x - координата камеры по оси x;
 * y - координата камеры по оси y;
 * z - координата камеры по оси z;
 * xdeg - угол поворота камеры на плоскости xy;
 * zdeg - угол поворота камеры на плоскости xz.
 */

void Camera_Apply(int coordinx,int coordiny,int coordinz);
/*
 * Прменяет параметры камеры на каждом тике отрисовки + плюс проверяет на выход из лабиринта.
 * coordinx - размер лабиринта по оси x;
 * coordiny - размер лабиринта по оси y;
 * coordinz - размер лабиринта по оси z;
 */
void Camera_Rotation(float xAngle,float zAngle);
/*
 *
 */
void Camera_MoveByMouse(int CenterX, int CenterY);

#endif //FRICK_CAMERA_H
