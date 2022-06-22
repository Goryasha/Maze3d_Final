//Функции взамодействия программы с камерой.
#include "camera.h"
#include <gl/gl.h>
#include <windows.h>
#include <cmath>

SCam camera ={0,0,1.7,70,-40};

void Camera_Apply(int coordinx,int coordiny,int coordinz){
    glRotatef(-camera.xdeg,1,0,0);
    glRotatef(-camera.zdeg,0,0,1);
    glTranslatef(-camera.x,-camera.y,-camera.z);
    if(camera.x<=-3 || camera.x>=coordinx*5-3 || camera.y<=-3 || camera.y>=coordiny*5-3 || camera.z<=-3 || camera.z>=coordinz*5-3){
        camera.x=0.5;
        camera.y=0.5;
        camera.z=0.5;
    }
}

void Camera_Rotation(float xAngle,float zAngle){
    camera.zdeg+=zAngle;
    if(camera.zdeg<0) camera.zdeg+=360;
    if(camera.zdeg>360) camera.zdeg-=360;
    camera.xdeg+=xAngle;
    if(camera.xdeg<0) camera.xdeg=0;
    if(camera.xdeg>180) camera.xdeg=180;
}
/*
 * Поворачивает камеру на указанные углы по двум плоскостям.
 * xAngle - угол по оси xy;
 * zAngle - угол по оси xz;
 */

void Camera_MoveByMouse(int CenterX, int CenterY){
    float angle = -camera.zdeg / 180 * M_PI ;
    float speed =0;
    float speedz =0;
    /*
     * angle - угол поворота камеры;
     * speed - скорость перемешения камеры в плоскости xy;
     * speedz - скорость перемешения камеры по z;
     */
    if (GetKeyState('W')<0) speed =0.1;
    if (GetKeyState(VK_SPACE)<0) speedz =0.1;
    if (GetKeyState(VK_CONTROL)<0 || GetKeyState(VK_SHIFT)<0) speedz =-0.1;
    if (GetKeyState('S')<0) speed =-0.1;
    if (GetKeyState('A')<0) {speed =0.1;angle -=M_PI*0.5;};
    if (GetKeyState('D')<0) {speed =0.1;angle +=M_PI*0.5;};
    if (speed!=0) {
        camera.x +=sin(angle)*speed;
        camera.y +=cos(angle)*speed;
    }
    if(speedz!=0){
        camera.z+=speedz;
    }

    POINT cur;
    POINT base ={CenterX,CenterY};
    /*
     * cur - содержит новое положение курсора на экране;
     * base - базове положение курсора на экране;
     */
    GetCursorPos(&cur);
    Camera_Rotation((base.y-cur.y)/5.0,(base.x-cur.x)/5.0);
    SetCursorPos(base.x,base.y);
}
/*
 * Функция поворота камеры по повортоу мыши.
 * CenterX - базовое нахождение камеры на экране по x;
 * CenterY - базовое нахождение камеры на экране по y;
 */