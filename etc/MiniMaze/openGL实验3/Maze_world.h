#ifndef MAZE_WORLD_H
#define MAZE_WORLD_H

#include "Maze_math.h"

#define CAMERA_MOVE_LEFT    0
#define CAMERA_MOVE_RIGHT   1
#define CAMERA_MOVE_FORWARD 2
#define CAMERA_MOVE_BACK    3

class camera
{
public:
	camera();
	~camera();
	void setEye(float ex,float ey,float ez);
	void setCenter(float cx,float cy,float cz);
	void setUp(float ux,float uy,float uz);
	void rotateCamera(float alpha,float theta);
	void rotateCamera(float theta,float x, float y, float z);
    void moveCamera(float m_x,float m_y,float m_z);
	void moveCamera(int dir);
	const float * getEye();
	const float * getCenter();
	const float * getUp();
protected:
private:
	float orignal_eye[3];
	float orignal_center[3];
	float orignal_up[3];
	float eye[3];//观察者视点位置
	float center[3];//观察者观察方向
	float up[3];//观察者向上的方向
	float radius;//观察距离，景深
	float theta;//视线与z轴负方向夹角
	float alpha;//up与y轴夹角
	float move_speed;
};

class lightSource
	{
	public:
	protected:
	private:
		float x;
		float y;
		float z;
	};

#endif