//

#ifndef FRICK_CAMERA_H
#define FRICK_CAMERA_H

struct SCam{
    float x,y,z;
    float xdeg,zdeg;
};

void Camera_Apply();
void Camera_Rotation(float xAngle,float zAngle);
void Camera_MoveByMouse(int CenterX, int CenterY);

#endif //FRICK_CAMERA_H
