#include "Maze_objects.h"

vector3 anorms[NUMVERTEXNORMALS] = {
#include "anorms.h"
};

//第一帧，最后～帧，fps
anim animlist[ 21 ] = {
    { 0, 39, 9 }, // STAND
    {40, 45, 10 }, // RUN
    { 46, 53, 10 }, // ATTACK
    { 54, 57, 7 }, // PAIN_A
    { 58, 61, 7 }, // PAIN_B
    { 62, 65, 7 }, // PAIN_C
    { 66, 71, 7 }, // JUMP
    { 72, 83, 7 }, // FLIP
    { 84, 94, 7 }, // SALUTE
    { 95, 111, 10 }, // FALLBACK
    { 112, 122, 7 }, // WAVE
    { 123, 134, 6 }, // POINT
    { 135, 153, 10 }, // CROUCH_STAND
    { 154, 159, 7 }, // CROUCH_WALK
    { 160, 168, 10 }, // CROUCH_ATTACK
    { 196, 172, 7 }, // CROUCH_PAIN
    { 173, 177, 5 }, // CROUCH_DEATH
    { 178, 183, 7 }, // DEATH_FALLBACK
    { 184, 189, 7 }, // DEATH_FALLFORWARD
    { 190, 197, 7 }, // DEATH_FALLBACKSLOW
    { 198, 198, 5 }, // BOOM
};

typedef enum {
    STAND,
    RUN,
    ATTACK,
    PAIN_A,
    PAIN_B,
    PAIN_C,
    JUMP,
    FLIP,
    SALUTE,
    FALLBACK,
    WAVE,
    POINTAT,
    CROUCH_STAND,
    CROUCH_WALK,
    CROUCH_ATTACK,
    CROUCH_PAIN,
    CROUCH_DEATH,
    DEATH_FALLBACK,
    DEATH_FALLFORWARD,
    DEATH_FALLBACKSLOW,
    BOOM,
    MAX_ANIMATIONS
} animType;

AABB::AABB() {

}

AABB::~AABB() {}

void AABB::setMax(float * m) {
    max_v[0] = m[0];
    max_v[1] = m[1];
    max_v[2] = m[2];
}

void AABB::setMin(float * m) {
    min_v[0] = m[0];
    min_v[1] = m[1];
    min_v[2] = m[2];
}

const float * AABB::getMax() {
    return this->max_v;
}

const float * AABB::getMin() {
    return this->min_v;
}

bool AABB::isCollide(AABB& a) {
    const float * a_min = a.getMin();
    const float * a_max = a.getMax();
    if (min_v[0] > a_max[0]) return false;
    if (max_v[0] < a_min[0]) return false;
    if (min_v[1] > a_max[1]) return false;
    if (max_v[1] < a_min[1]) return false;
    if (min_v[2] > a_max[2]) return false;
    if (max_v[2] < a_min[2]) return false;

    return true;
}

object::object() {

}

object::~object() {

}

void object::setMatAmient(const float * values) {
    for (int i=0; i<4; i++) {
        this->mat_ambient[i] = values[i];
    }
}

void object::setMatDiffuse(const float * values) {
    for (int i=0; i<4; i++) {
        this->mat_diffuse[i] = values[i];
    }
}

void object::setMatSpecular(const float * values) {
    for (int i=0; i<4; i++) {
        this->mat_specular[i] = values[i];
    }
}

void object::setMatShininess(float values) {
    this->mat_shininess[0] = values;
}

void object::setMatEmission(const float * values) {
    for (int i=0; i<4; i++) {
        this->mat_emission[i] = values[i];
    }
}

void object::setBoundBox(const float * left_bottom,const float * right_top) {



}

Round::Round(float x,float y,float z,float radius) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    float ambient[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float diffuse[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float specular[4] = {1.0 , 1.0 , 1.0 , 1.0};
    this->setMatAmient(ambient);
    this->setMatDiffuse(diffuse);
    this->setMatSpecular(specular);
    this->setMatShininess(50.0);
}

Round::~Round() {

}

void Round::drawRound() {
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    glTranslatef(x,y,z);
    glutSolidSphere(radius,20,16);
    glPopMatrix();
}

void Round::setLocation(float x,float y,float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

hero::hero() {

}

hero::~hero() {

}

void hero::setEye(float ex,float ey,float ez) {
    this->eye[0] = ex;
    this->eye[1] = ey;
    this->eye[2] = ez;
}

void hero::setCenter(float cx,float cy,float cz) {
    this->center[0] = cx;
    this->center[1] = cy;
    this->center[2] = cz;
}

void hero::setUp(float ux,float uy,float uz) {
    this->up[0] = ux;
    this->up[1] = uy;
    this->up[2] = uz;
}

const float * hero::getEye() {
    return this->eye;
}

const float * hero::getCenter() {
    return this->center;
}

const float * hero::getUp() {
    return this->up;
}

MD2Model::MD2Model() {
    m_vertices =0;
    m_glcmds =0;
    m_lightnormals =0;
    num_frames =0;
    num_xyz =0;
    num_glcmds =0;
    m_texid =0;
    m_scale =1.0;
    setAnim(0);
    float ambient[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float diffuse[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float specular[4] = {1.0 , 1.0 , 1.0 , 1.0};
    this->setMatAmient(ambient);
    this->setMatDiffuse(diffuse);
    this->setMatSpecular(specular);
    this->setMatShininess(50.0);
}

MD2Model::~MD2Model() {
    delete [] m_vertices;
    delete [] m_glcmds;
    delete [] m_lightnormals;
}

void MD2Model::setScale(float s) {
    m_scale = s;
}

void MD2Model::setAnim(int type) {
    if( (type < 0) || (type > MAX_ANIMATIONS) )
        type = 0;
    m_anim.startframe = animlist[ type ].first_frame;
    m_anim.endframe = animlist[ type ].last_frame;
    m_anim.next_frame = animlist[ type ].first_frame + 1;
    m_anim.fps = animlist[ type ].fps;
    m_anim.type = type;
}

void MD2Model::Animate( float time ) {
    m_anim.curr_time = time;
    // 计算当前帧和下一帧
    if( m_anim.curr_time - m_anim.old_time > (1.0 / m_anim.fps) ) {
        m_anim.curr_frame = m_anim.next_frame;
        m_anim.next_frame++;
        if( m_anim.next_frame > m_anim.endframe )
            m_anim.next_frame = m_anim.startframe;
        m_anim.old_time = m_anim.curr_time;
    }
    // 防止当前帧或下一帧超出了总帧数…
    if( m_anim.curr_frame > (num_frames - 1) )
        m_anim.curr_frame = 0;
    if( m_anim.next_frame > (num_frames - 1) )
        m_anim.next_frame = 0;
    m_anim.interpol = m_anim.fps * (m_anim.curr_time - m_anim.old_time);
}

bool MD2Model::load_model(const char * filename) {
    FILE * file = NULL;
    MD2HEADINFO_ptr md2_head = new MD2HEADINFO;
    char * buffer;
    frame *f; //临时变量
    vector3 *verts_ptr; //指向m_vertices 的指针
    int *normals_ptr; //指向m lightnormals 的指针
    triangle *triangles;
    char current_dir[512];
    GetCurrentDirectory(512,current_dir);
    strcat(current_dir,filename);
    file = fopen(current_dir,"rb");
    if (file == NULL) {
        return false;
    }
    fread(md2_head,sizeof(MD2HEADINFO),1,file);
    if( (md2_head->magic != MD2_MAGIC_NUM) && (md2_head->version != MD2_VERSION) ) {
        //这不是一个MD2 文件
        fclose(file);
        return false;
    }
    //初始化成员变量
    skinWidth = md2_head->skinWidth;
    skinHeight = md2_head->skinHeight;
    num_frames = md2_head->num_frames;
    num_xyz = md2_head->num_xyz;
    num_glcmds = md2_head->num_glcmds;
    num_tris = md2_head->num_tris;
    //申请内存
    m_texCoods = new texCood[md2_head->num_st];
    m_vertices = new vector3[ num_xyz * num_frames ];
    m_glcmds = new int[ num_glcmds ];
    m_lightnormals = new int[ num_xyz * num_frames ];
    m_triangle = new triangle[md2_head->num_tris];

    buffer = new char[ num_frames * md2_head->frameSize ];
    //读入文件数据
    //读入帧数据
    fseek(file,md2_head->ofs_frames,SEEK_SET);
    fread(buffer,num_frames * md2_head->frameSize,1,file);
    for (int i=0; i< num_frames; i++) {
        f = (frame *)&buffer[ md2_head->frameSize * i ];
        verts_ptr = &m_vertices[ num_xyz * i ];
        normals_ptr = &m_lightnormals[ num_xyz * i ];
        for( int j = 0; j < num_xyz; j++ ) {
            verts_ptr[j][0] = (f->alias_vertices[j].v[0] * f->scale[0]) + f->translate[0];
            verts_ptr[j][1] = (f->alias_vertices[j].v[1] * f->scale[1]) + f->translate[1];
            verts_ptr[j][2] = (f->alias_vertices[j].v[2] * f->scale[2]) + f->translate[2];
            normals_ptr[j] = f->alias_vertices[j].lightnormalindex;
        }
    }

    //导入三角形
    fseek(file,md2_head->ofs_tris,SEEK_SET);
    fread(m_triangle, sizeof(triangle), num_tris ,file);

    //导入纹理坐标
    fseek(file,md2_head->ofs_st,SEEK_SET);
    fread(m_texCoods,sizeof(texCood),md2_head->num_st,file);

    delete [] buffer;
    fclose(file);
    return true;
}

bool MD2Model::load_skin(GLuint m_texid) {
    this->m_texid = m_texid;
    return true;
}

void MD2Model::Interpolate(vector3 * vertlist) {
    m_anim.curr_frame = 1;
    for( int i = 0; i < num_xyz ; i++ ) {
        vertlist[i][0] = m_vertices[ i + (num_xyz * m_anim.curr_frame) ][0] * m_scale;
        vertlist[i][1] = m_vertices[ i + (num_xyz * m_anim.curr_frame) ][1] * m_scale;
        vertlist[i][2] = m_vertices[ i + (num_xyz * m_anim.curr_frame) ][2] * m_scale;
    }
}

void MD2Model::RenderFrame() {
    vector3 *v = new vector3[num_xyz];
    Interpolate(v);
    glBindTexture(GL_TEXTURE_2D,m_texid);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < num_tris; i++) {
        for (int j = 0; j < 3; j++) {
            glTexCoord2f((float)m_texCoods[m_triangle[i].index_st[j]].s / skinWidth , (float)m_texCoods[m_triangle[i].index_st[j]].t / skinHeight);
            glNormal3fv(anorms[m_lightnormals[m_triangle[i].index_xyz[j]]]);
            glVertex3f(v[m_triangle[i].index_xyz[j]][0] , v[m_triangle[i].index_xyz[j]][1] , v[m_triangle[i].index_xyz[j]][2]);
        }
    }
    glEnd();
    delete [] v;
}

void MD2Model::drawFrame(int frame) {
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    glTranslatef(100,-70,140);
    glRotatef(-90,1.0,0.0,0.0);
    RenderFrame();
    glPopMatrix();
}

scene_map::scene_map() {
    this->x = -150;
    this->y = -50;
    this->z = -150;
    this->unit_w = 60;
    this->unit_w_num = 400;
    this->unit_h_num = 400;
    float ambient[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float diffuse[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float specular[4] = {1.0 , 1.0 , 1.0 , 1.0};
    this->setMatAmient(ambient);
    this->setMatDiffuse(diffuse);
    this->setMatSpecular(specular);
    this->setMatShininess(50.0);
}

scene_map::~scene_map() {


}

void scene_map::initMap(float x,float y,float z,int unit_w_num,int unit_h_num,int unit_y_num,float unit_w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->unit_w_num = unit_w_num;
    this->unit_h_num = unit_h_num;
    this->unit_y_num = unit_y_num;
    this->unit_w = unit_w;
}

void scene_map::drawMap() {
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    glTranslatef(x,y,z);
    glBindTexture(GL_TEXTURE_2D,texture_name);
    glBegin(GL_QUADS);
    for (int i = 0 ; i < unit_w_num ; i++) {
        for(int j = 0 ; j < unit_h_num ; j++) {
            glTexCoord2f(0,0);
            glVertex3f(i * unit_w, 0 ,j * unit_w);
            glTexCoord2f(1,0);
            glVertex3f(i * unit_w, 0 ,(j + 1) * unit_w);
            glTexCoord2f(1,1);
            glVertex3f((i + 1) * unit_w, 0 ,(j + 1) * unit_w);
            glTexCoord2f(0,1);
            glVertex3f((i + 1) * unit_w, 0 ,j * unit_w);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int i = 0 ; i < unit_h_num ; i++) {
        for(int j = 0 ; j < unit_y_num ; j++) {
            glTexCoord2f(0,0);
            glVertex3f(0, j * unit_w , (i + 1) * unit_w);
            glTexCoord2f(1,0);
            glVertex3f(0, j * unit_w ,i * unit_w);
            glTexCoord2f(1,1);
            glVertex3f(0, (j + 1) * unit_w ,i * unit_w);
            glTexCoord2f(0,1);
            glVertex3f(0, (j + 1) * unit_w ,(i + 1) * unit_w);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    float z = unit_h_num * unit_w;
    for (int i = 0 ; i < unit_w_num ; i++) {
        for(int j = 0 ; j < unit_y_num ; j++) {
            glTexCoord2f(0,0);
            glVertex3f((unit_w_num - i) * unit_w, j * unit_w , z);
            glTexCoord2f(1,0);
            glVertex3f((unit_w_num - 1 - i) * unit_w, j * unit_w ,z);
            glTexCoord2f(1,1);
            glVertex3f((unit_w_num - 1 - i) * unit_w, (j + 1) * unit_w ,z);
            glTexCoord2f(0,1);
            glVertex3f((unit_w_num - i) * unit_w, (j + 1) * unit_w ,z);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    float x = unit_w_num * unit_w;
    for (int i = 0 ; i < unit_h_num ; i++) {
        for(int j = 0 ; j < unit_y_num ; j++) {
            glTexCoord2f(0,0);
            glVertex3f(x, j * unit_w , i * unit_w);
            glTexCoord2f(1,0);
            glVertex3f(x, j * unit_w ,(i + 1) * unit_w);
            glTexCoord2f(1,1);
            glVertex3f(x, (j + 1) * unit_w ,(i + 1) * unit_w);
            glTexCoord2f(0,1);
            glVertex3f(x, (j + 1) * unit_w ,i * unit_w);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int i = 0 ; i < unit_w_num ; i++) {
        for(int j = 0 ; j < unit_y_num ; j++) {
            glTexCoord2f(0,0);
            glVertex3f(i * unit_w, j * unit_w , 0);
            glTexCoord2f(1,0);
            glVertex3f((i + 1) * unit_w, j * unit_w ,0);
            glTexCoord2f(1,1);
            glVertex3f((i + 1) * unit_w, (j + 1) * unit_w ,0);
            glTexCoord2f(0,1);
            glVertex3f(i * unit_w, (j + 1) * unit_w ,0);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    for (int i = 0 ; i < unit_w_num ; i++) {
        for(int j = 0 ; j < unit_h_num ; j++) {
            glTexCoord2f(0,0);
            glVertex3f(i * unit_w, unit_w * unit_y_num ,j * unit_w);
            glTexCoord2f(1,0);
            glVertex3f((i + 1) * unit_w, unit_w * unit_y_num ,j * unit_w);
            glTexCoord2f(1,1);
            glVertex3f((i + 1) * unit_w, unit_w * unit_y_num ,(j + 1) * unit_w);
            glTexCoord2f(0,1);
            glVertex3f(i * unit_w, unit_w * unit_y_num ,(j + 1) * unit_w);
        }
    }
    glEnd();
    glPopMatrix();

}

void scene_map::setTexture(GLuint name) {
    this->texture_name = name;
}

//////////////////////////////////////////////////////////////////////////
//
//left为墙体在地图中所在方格的左上角位置，right为右下角位置,以方格为单位
//y_num为垂直方向方格数
//////////////////////////////////////////////////////////////////////////
scene_wall::scene_wall() {
    float ambient[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float diffuse[4] = {1.0 , 1.0 , 1.0 , 1.0};
    float specular[4] = {1.0 , 1.0 , 1.0 , 1.0};
    this->setMatAmient(ambient);
    this->setMatDiffuse(diffuse);
    this->setMatSpecular(specular);
    this->setMatShininess(50.0);
}

scene_wall::~scene_wall() {

}

void scene_wall::initWall(float x,float y,float z,int left,int right,int bottom,int top,int y_num,float wall_w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
    this->y_num = y_num;
    this->wall_w = wall_w;
}

void scene_wall::drawWall() {
    glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    glTranslatef(x,y,z);
    glBindTexture(GL_TEXTURE_2D,texture_name);
    for (int i = 0; i < y_num; i++) {
        glBegin(GL_QUADS);
        for (int j = bottom; j < top; j++) {
            glTexCoord2f(0,0);
            glVertex3f(left * wall_w,i * wall_w ,j * wall_w);
            glTexCoord2f(1,0);
            glVertex3f(left * wall_w,i * wall_w ,(j+1) * wall_w);
            glTexCoord2f(1,1);
            glVertex3f(left * wall_w,(i+1) * wall_w ,(j+1) * wall_w);
            glTexCoord2f(0,1);
            glVertex3f(left * wall_w,(i+1) * wall_w ,j * wall_w);
        }
        glEnd();
        glBegin(GL_QUADS);
        for (int j = left; j < right; j++) {
            glTexCoord2f(0,0);
            glVertex3f(j * wall_w,i * wall_w ,top * wall_w);
            glTexCoord2f(1,0);
            glVertex3f((j+1) * wall_w,i * wall_w ,top * wall_w);
            glTexCoord2f(1,1);
            glVertex3f((j+1) * wall_w,(i+1) * wall_w ,top * wall_w);
            glTexCoord2f(0,1);
            glVertex3f(j * wall_w,(i+1) * wall_w ,top * wall_w);
        }
        glEnd();
        glBegin(GL_QUADS);
        for (int j = top; j > bottom; j--) {
            glTexCoord2f(0,0);
            glVertex3f(right * wall_w,i * wall_w ,j * wall_w);
            glTexCoord2f(1,0);
            glVertex3f(right * wall_w,i * wall_w ,(j-1) * wall_w);
            glTexCoord2f(1,1);
            glVertex3f(right * wall_w,(i+1) * wall_w ,(j-1) * wall_w);
            glTexCoord2f(0,1);
            glVertex3f(right * wall_w,(i+1) * wall_w ,j * wall_w);
        }
        glEnd();
        glBegin(GL_QUADS);
        for (int j = right; j > left; j--) {
            glTexCoord2f(0,0);
            glVertex3f(j * wall_w,i * wall_w ,bottom * wall_w);
            glTexCoord2f(1,0);
            glVertex3f((j-1) * wall_w,i * wall_w ,bottom * wall_w);
            glTexCoord2f(1,1);
            glVertex3f((j-1) * wall_w,(i+1) * wall_w ,bottom * wall_w);
            glTexCoord2f(0,1);
            glVertex3f(j * wall_w,(i+1) * wall_w ,bottom * wall_w);
        }
        glEnd();
    }
    glPopMatrix();
}

void scene_wall::setTexture(GLuint name) {
    this->texture_name = name;
}

scene_maze::scene_maze(int wall_num) {
    map = new scene_map();
    this->wall_num = wall_num;
    walls = new scene_wall * [wall_num];
    for (int i=0; i< wall_num; i++) {
        walls[i] = new scene_wall();
    }
}

scene_maze::~scene_maze() {
    if (map != NULL) {
        delete map;
        map = NULL;
    }
    if (walls!=NULL) {
        for (int i=0; i< wall_num; i++) {
            if (walls[i]!=NULL) {
                delete [] walls[i];
            }
        }
        delete [] walls;
        walls =NULL;
    }
}

void scene_maze::initMaze(float x,float y,float z,int unit_w_num,int unit_h_num,int unit_y_num,float unit_w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->unit_w_num = unit_w_num;
    this->unit_h_num = unit_h_num;
    this->unit_y_num = unit_y_num;
    this->unit_w = unit_w;
    map->initMap(x,y,z,unit_w_num,unit_h_num,unit_y_num,unit_w);
}

//////////////////////////////////////////////////////////////////////////
//
//wall_des_loc是对场景中墙体的位置描述，wall_des_loc的长度一定为4 * wall_num
//每四个相邻元素分别表示left，right，bottom，top
//
//////////////////////////////////////////////////////////////////////////
void scene_maze::initWall(const int * wall_des_loc) {
    int j = 0;
    for (int i = 0; i<wall_num; i++) {
        j+=4;
        walls[i]->initWall(x,y,z,wall_des_loc[j-4],wall_des_loc[j-3],wall_des_loc[j-2],wall_des_loc[j-1],unit_y_num,unit_w);
    }
}

void scene_maze::setTexture(const GLuint * name) {
    this->texture_name = name;
    map->setTexture(name[0]);
    for (int i = 0; i<wall_num; i++) {
        walls[i]->setTexture(name[0]);
    }
}

void scene_maze::drawMaze() {
    map->drawMap();
    for (int i=0; i<wall_num; i++) {
        walls[i]->drawWall();
    }
}