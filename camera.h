//// Заголовочный файл с функциями для управления камерой

#ifndef FRICK_CAMERA_H
#define FRICK_CAMERA_H

/**
 * Структура содержащая основные паратетры камеры.
 * @param x - координата камеры по оси x;
 * @param y - координата камеры по оси y;
 * @param z - координата камеры по оси z;
 * @param xdeg - угол поворота камеры на плоскости xy;
 * @param zdeg - угол поворота камеры на плоскости xz.
 */
struct SCam{
    float x,y,z;
    float xdeg,zdeg;
};

/**
 * Прменяет параметры камеры на каждом тике отрисовки + плюс проверяет на выход из лабиринта.
 * @param coordinx - размер лабиринта по оси x;
 * @param coordiny - размер лабиринта по оси y;
 * @param coordinz - размер лабиринта по оси z.
 */
void Camera_Apply(int coordinx,int coordiny,int coordinz);

/**
 * Поворачивает камеру на указанные углы по двум плоскостям.
 * @param xAngle - угол по оси xy;
 * @param zAngle - угол по оси xz.
 */
void Camera_Rotation(float xAngle,float zAngle);

/**
 * Функция поворота камеры по повортоу мыши.
 * @param CenterX - базовое нахождение камеры на экране по x;
 * @param CenterY - базовое нахождение камеры на экране по y.
 */
void Camera_MoveByMouse(int CenterX, int CenterY);

#endif //FRICK_CAMERA_H
