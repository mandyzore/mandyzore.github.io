#include "Maze_world.h"


camera::camera() {
    this->radius = 100;
    this->eye[0] = this->orignal_eye[0]= 0;
    this->eye[1] = this->orignal_eye[1]= 0;
    this->eye[2] = this->orignal_eye[2]= 0;
    this->center[0] = this->orignal_center[0] =0;
    this->center[1] = this->orignal_center[1] =0;
    this->center[2] = this->orignal_center[2] = radius;
    this->up[0] = this->orignal_up[0] = 0;
    this->up[1] = this->orignal_up[1] = radius;
    this->up[2] = this->orignal_up[2] = 0;
    this->move_speed = 15;
	this->moveCamera(30,0,30);
}


camera::~camera() {

}

void camera::setEye(float ex,float ey,float ez) {
    this->eye[0] = ex;
    this->eye[1] = ey;
    this->eye[2] = ez;
}


void camera::setCenter(float cx,float cy,float cz) {
    this->center[0] = cx;
    this->center[1] = cy;
    this->center[2] = cz;
}

void camera::setUp(float ux,float uy,float uz) {
    this->up[0] = ux;
    this->up[1] = uy;
    this->up[2] = uz;
}

const float * camera::getEye() {
    return this->eye;
}

const float * camera::getCenter() {
    return this->center;
}

const float * camera::getUp() {
    return this->up;
}

/************************************************************************/
/* 旋转照相机，alpha为垂直旋转，theta为水平旋转                         */
/************************************************************************/
void camera::rotateCamera(float alpha,float theta) {
    float sin_alpha = sin(alpha);
    float cos_alpha = cos(alpha);
    float sin_theta = sin(theta);
    float cos_theta = cos(theta);
    float cx = this->orignal_center[0];
    float cy = this->orignal_center[1];
    float cz = this->orignal_center[2];
    float ex = this->orignal_eye[0];
    float ey = this->orignal_eye[1];
    float ez = this->orignal_eye[2];
    float ux = this->orignal_up[0];
    float uy = this->orignal_up[1];
    float uz = this->orignal_up[2];
    this->center[0] = cos_theta * (cx - ex) + sin_theta * sin_alpha * (cy - ey) + sin_theta * cos_alpha * (cz - ez) + ex;
    this->center[1] = cos_alpha * (cy - ey) - sin_alpha * (cz - ez) + ey;
    this->center[2] = -sin_theta * (cx - ex) + cos_theta * sin_alpha * (cy - ey) + cos_theta * cos_alpha * (cz - ez) + ez;
}

/************************************************************************/
/*  旋转照相机，theta为旋转角，x,y,z定义旋转轴                        */
/************************************************************************/
void camera::rotateCamera(float theta,float x, float y, float z) {
    float sin_theta = sin(theta);
    float cos_theta = cos(theta);
    float cx = this->orignal_center[0];
    float cy = this->orignal_center[1];
    float cz = this->orignal_center[2];
    float ex = this->orignal_eye[0];
    float ey = this->orignal_eye[1];
    float ez = this->orignal_eye[2];
    float ux = this->orignal_up[0];
    float uy = this->orignal_up[1];
    float uz = this->orignal_up[2];

}

void camera::moveCamera(float m_x,float m_y,float m_z) {
    this->eye[0]+=m_x;
    this->center[0]+=m_x;
    this->up[0]+=m_x;
    this->eye[1]+=m_y;
    this->center[1]+=m_y;
    this->up[1]+=m_y;
    this->eye[2]+=m_z;
    this->center[2]+=m_z;
    this->up[2]+=m_z;

    this->orignal_eye[0]+=m_x;
    this->orignal_center[0]+=m_x;
    this->orignal_up[0]+=m_x;
    this->orignal_eye[1]+=m_y;
    this->orignal_center[1]+=m_y;
    this->orignal_up[1]+=m_y;
    this->orignal_eye[2]+=m_z;
    this->orignal_center[2]+=m_z;
    this->orignal_up[2]+=m_z;
}

//////////////////////////////////////////////////////////////////////////
//
//dir的值只能为 CAMERA_MOVE_LEFT、CAMERA_MOVE_RIGHT、
//				CAMERA_MOVE_FORWARD、CAMERA_MOVE_BACK
//////////////////////////////////////////////////////////////////////////
void camera::moveCamera(int dir) {
    float c0 = center[0] - eye[0];
    float c3 = center[2] - eye[2];
    float ml = sqrt(c0 * c0 + c3 * c3);
    float mx;
    float mz;
    if (dir == CAMERA_MOVE_FORWARD) {
        mx = c0 / ml * move_speed;
        mz = c3 / ml * move_speed;
    }
    if (dir == CAMERA_MOVE_BACK) {
        mx = - c0 / ml * move_speed;
        mz = - c3 / ml * move_speed;
    }
    if (dir == CAMERA_MOVE_LEFT) {
        mx = c3 / ml * move_speed;
        mz = -c0 / ml * move_speed;
    }
    if (dir == CAMERA_MOVE_RIGHT) {
        mx = - c3 / ml * move_speed;
        mz = c0 / ml * move_speed;
    }
    moveCamera(mx,0,mz);
}