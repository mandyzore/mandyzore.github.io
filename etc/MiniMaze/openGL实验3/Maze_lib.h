#ifndef MAZE_LIB_H
#define MAZE_LIB_H

#include <Windows.h>
#include <WindowsX.h>
#include <mmsystem.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <gl/GLUT.H>
#include <gl/GLAUX.H>
#include <gl/GLU.h>
#include <gl/GL.h>


#include "Maze_math.h"
#include "Maze_world.h"

using namespace std;


#define BITMAP_TYPE   0x4D42//位图类型，用于判断某一文件是否为位图
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

#define PI        ((float)3.141592653589)
#define PI_DEV_2  ((float)1.5707963267945)
#define PI_MUL_2  ((float)6.283185307178)


typedef struct passive_motion_type {
    int lx;
    int ly;
    int nx;
    int ny;
    int first;
} pMotion,* pMotionPtr;
//纹理集
typedef struct textures_typ {
    unsigned char * * data;
    int n;
    GLuint * texture_name;
    BITMAPINFOHEADER ** info;
} textures,* textures_ptr;

#define MD2_MAGIC_NUM (('I')+('P'<<8)+('D'<<16)+('2'<<24))
#define MD2_VERSION   8

typedef struct MD2HEADINFO_typ {
    int magic; //魔术数，一定为“IPD2”
    int version; //md2 版本号，一定等于8
    int skinWidth; //纹理的宽度
    int skinHeight; //纹理的高度
    int frameSize; //一帧数据的尺寸（字节）
    int num_skins; //纹理的数目
    int num_xyz; //顶点的数目
    int num_st; //纹理坐标的数目
    int num_tris; //三角形的数目
    int num_glcmds; //OpenGL 指令的数目
    int num_frames; //总帧数
    int ofs_skins; //到纹理名字的偏移量（每个64 字节）
    int ofs_st; //到ｓ－ｔ纹理坐标的偏移量
    int ofs_tris; //到三角形的偏移量
    int ofs_frames; //到帧数据的偏移量
    int ofs_glcmds; //到OpenGL 指令的偏移量
    int ofs_end; //到文件尾的偏移量
} MD2HEADINFO, * MD2HEADINFO_ptr;

void initAll();

void initTexture();

void initEvnTexture();

void initModelTexture();

inline void initStructs();

void initObjects();

void display();

void changSize(int width,int height);

void keyPress(unsigned char key,int width,int height);

void activeMotion(int x,int y);

void passiveMotion(int x,int y);

void TimerProc();

void timerFunc(int id);

void updateGame();

unsigned char * loadBitmap(const char * filename,BITMAPINFOHEADER & info_head);

extern bool run_game;



#endif