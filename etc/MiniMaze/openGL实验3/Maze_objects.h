#ifndef MAZE_OBJECTS_H
#define MAZE_OBJECTS_H

#include "Maze_lib.h"

#define NUMVERTEXNORMALS 162//预处理法向量个数

typedef struct {
    float vector3[6][4];//底面、正面、右面、后面、左面、顶面

} rect;

typedef struct {
    unsigned char v[3]; //压缩的顶点(x,y,z)坐标
    unsigned char lightnormalindex; //法向量的索引，光照绘制时使用
} vertex;

typedef struct texCood_typ {
    short s;
    short t;
} texCood;

typedef float vector3[3];

typedef struct anim_typ {
    int first_frame; //动画的第一帧
    int last_frame; //帧数
    int fps; //每秒的帧数
} anim;

typedef struct animState_typ {
    int startframe; //第一帧
    int endframe; //最后帧
    int fps; //这个动画的每秒帧数。
    float curr_time; //当前时间
    float old_time; //上次时间
    float interpol; //插值的比例
    int type; //动画类型
    int curr_frame; //当前帧
    int next_frame; //下一帧
} animState;

typedef struct {
    float scale[3]; //比例值
    float translate[3]; //位移向量
    char name[16]; //帧名
    vertex alias_vertices[1]; //该帧的第一个顶点
    texCood alias_textures[1];//该帧的第一个顶点对应纹理位置
} frame;

typedef struct {
    short index_xyz[3]; //三角形顶点的索引
    short index_st[3]; //顶点的纹理坐标的索引
} triangle;

class AABB {
public:
    AABB();
    ~AABB();
    bool isCollide(AABB& a);
    const float * getMin();
    const float * getMax();
    void setMin(float * m);
    void setMax(float * m);
protected:
private:
    float min_v[3];
    float max_v[3];
};

class object {
public:
    object();
    ~object();
protected:
    float x;
    float y;
    float z;
    float mat_ambient[4];//材料的环境光反射颜色
    float mat_diffuse[4];//材料的散射光反射颜色
    float mat_specular[4];//材料镜面反射颜色
    float mat_shininess[1];//镜面反射指数
    float mat_emission[4];//材料的发射光颜色
    AABB * bound_rect;
    void setMatAmient(const float * values);
    void setMatDiffuse(const float * values);
    void setMatSpecular(const float * values);
    void setMatShininess(float values);
    void setMatEmission(const float * values);
    void setBoundBox(const float * left_bottom,const float * right_top);//对应左下角和右上角
    const float * getMatAmient();
    const float * getMatDiffuse();
    const float * getMatSpecular();
    float getMatShininess();
    const float * getMatEmission();
    const AABB * getAABB();
private:

};

class Round : object {
public:
    Round(float x,float y,float z,float radius);
    ~Round();
    void drawRound();
    void setLocation(float x,float y,float z);
protected:
private:
    float radius;
};

class MD2Model:object {
public:
    MD2Model();
    ~MD2Model();
    bool load_model(const char * filename);
    bool load_skin(GLuint m_texid);
    void drawModel(float time);
    void drawFrame(int frame);
    void setAnim(int type);
    void setScale(float s);
    // vector3 anorms[NUMVERTEXNORMALS];
    //float anorms_dots[SHADEDOT_QUANT][256];
    anim animlist[21]; //动画列表
protected:
private:
	int skinWidth;
	int skinHeight;
    int num_tris;//模型中的三角形个数
    int num_frames; //帧数
    int num_xyz; //顶点数
    int num_glcmds; //OpenGL 指令数
    int *m_glcmds; //OpenGL 指令数组
    int *m_lightnormals; //法向量索引数组
    GLuint m_texid; //纹理id
    float m_scale; //缩放比例值
    vector3 *m_vertices; //顶点数组
    texCood *m_texCoods;//纹理数组
	triangle * m_triangle;
    triangle ** m_frame;
    animState m_anim; //动画
    void Animate(float time);
    void ProcessLighting(void);
    void Interpolate(vector3 * vertlist);
    void RenderFrame();
};

class hero {
public:
    hero();
    ~hero();
    void setEye(float ex,float ey,float ez);
    void setCenter(float cx,float cy,float cz);
    void setUp(float ux,float uy,float uz);
    const float * getEye();
    const float * getCenter();
    const float * getUp();
protected:
private:
    float eye[3];//观察者视点位置
    float center[3];//观察者观察方向
    float up[3];//观察者向上的方向

};

class scene_map:object {
public:
    scene_map();
    ~scene_map();
    void initMap(float x,float y,float z,int unit_w_num,int unit_h_num,int unit_y_num,float unit_w);
    void drawMap();
    void getXYZ(float * xyz);
    float getWidth();
    float getHeight();
    void setTexture(GLuint name);
    int getTexture();
protected:
private:
    float x;
    float y;
    float z;
    float unit_w;//单元格宽度
    int unit_w_num;//横向单元格个数
    int unit_h_num;//纵向单元格个数
    int unit_y_num;//高度单元格数
    int texture_name;//纹理名称
};

class scene_wall:object {
public:
    scene_wall();
    ~scene_wall();
    void initWall(float x,float y,float z,int left,int right,int bottom,int top,int y_num,float wall_w);
    void drawWall();
    void setTexture(GLuint name);
    GLuint getTexture();
protected:

private:
    float x;
    float y;
    float z;
    float wall_w;//与map中unit_w一样
    int left;
    int right;
    int bottom;
    int top;
    int y_num;

    int texture_name;//纹理名称
};

class scene_maze:object {
public:
    scene_maze(int wall_num);
    ~scene_maze();
    void initMaze(float x,float y,float z,int unit_w_num,int unit_h_num,int unit_y_num,float unit_w);
    void initWall(const int * wall_des_loc);
    void drawMaze();
    void getXYZ(float * xyz);
    float getWidth();
    float getHeight();
    void setTexture(const GLuint * name);
    GLuint getTexture();
protected:
private:
    float x;
    float y;
    float z;
    float unit_w;//单元格宽度
    int unit_w_num;//横向单元格个数
    int unit_h_num;//纵向单元格个数
    int unit_y_num;//高度单元格数
    int wall_num;//墙的个数
    scene_map * map;
    scene_wall ** walls;
    const GLuint * texture_name;//纹理名称
};

#endif