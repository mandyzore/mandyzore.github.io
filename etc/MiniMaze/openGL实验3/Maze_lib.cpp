#include "Maze_lib.h"
#include "Maze_objects.h"

bool run_game = false;
textures texs = {NULL,100,NULL};
textures m_texs = {NULL,100,NULL};
camera * watcher_camera = NULL;
Round * r = NULL;
MD2Model * mmd2 =NULL;
scene_maze * maze = NULL;


void initAll() {
    glClearColor(0.0,0.0,0.0,0.0);
    initTexture();
    initStructs();
    initObjects();



}

inline void initStructs() {

}

void initTexture() {
    initModelTexture();
    initEvnTexture();
}

void initModelTexture() {
    int len = m_texs.n;
    m_texs.texture_name = new GLuint[len];
    m_texs.data = new unsigned char *[len];
    m_texs.info = new BITMAPINFOHEADER*[len];
    for (int i = 0; i<len; i++) {
        m_texs.texture_name[i] = -1;
        m_texs.data[i] = NULL;
    }

    //
    BITMAPINFOHEADER* info_head = new BITMAPINFOHEADER;
    m_texs.data[0] = loadBitmap("\\model\\tris\\blade_black.bmp",*info_head);
    m_texs.info[0] = info_head;
//     BITMAPINFOHEADER* info_head2 = new BITMAPINFOHEADER;
//     m_texs.data[1] = loadBitmap("\\model\\soldier\\AAA.BMP",*info_head2);
//     m_texs.info[1] = info_head2;
    //
    //分配n个名称
    glGenTextures(len,m_texs.texture_name);
    for (int i =0; i<len; i++) {
        if (m_texs.data[i] != NULL) {
            glBindTexture(GL_TEXTURE_2D,m_texs.texture_name[i]);//创建对象
            glTexImage2D(GL_TEXTURE_2D , 0 , 3 , m_texs.info[i]->biWidth ,
                         m_texs.info[i]->biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,m_texs.data[i]);//添加纹理数据
        }
    }
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);// 线形滤波
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);// 线形滤波
    glEnable(GL_TEXTURE_2D);

}

void initEvnTexture() {
    int len = texs.n;
    texs.texture_name = new GLuint[len];
    texs.data = new unsigned char *[len];
    texs.info = new BITMAPINFOHEADER*[len];
    for (int i = 0; i<len; i++) {
        texs.texture_name[i] = -1;
        texs.data[i] = NULL;
    }

    //
    BITMAPINFOHEADER* info_head = new BITMAPINFOHEADER;
    texs.data[0] = loadBitmap("\\texture\\wall_1.bmp",*info_head);
    texs.info[0] = info_head;

    //
    //分配n个名称
    glGenTextures(len,texs.texture_name);
    for (int i =0; i<len; i++) {
        if (texs.data[i] != NULL) {
            glBindTexture(GL_TEXTURE_2D,texs.texture_name[i]);//创建对象
            glTexImage2D(GL_TEXTURE_2D , 0 , 3 , texs.info[i]->biWidth ,
                         texs.info[i]->biHeight,0,GL_RGB,GL_UNSIGNED_BYTE,texs.data[i]);//添加纹理数据
        }
    }
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);// 线形滤波
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);// 线形滤波
    glEnable(GL_TEXTURE_2D);

}

void initObjects() {
    r = new Round(0,0,-80,10);
    maze = new scene_maze(18);
    float maze_xyz[] = {0,-100,0};
    int maze_w_num = 25;
    int maze_h_num = 25;
    int maze_y_num = 5;
    float maze_unit = 60;
    maze->initMaze(maze_xyz[0],maze_xyz[1],maze_xyz[2],maze_w_num,maze_h_num,maze_y_num,maze_unit);
    int  wall_des[72] = {7,8,2,7,
                         0,7,6,7,
                         12,19,2,3,
                         15,21,5,6,
                         12,18,7,8,
                         3,11,10,11,
                         11,12,2,19,
                         0,6,13,14,
                         6,7,13,17,
                         15,16,10,19,
                         19,20,12,16,
                         21,22,5,11,
                         20,25,12,13,
                         0,8,19,20,
                         8,9,19,23,
                         9,19,22,23,
                         19,20,21,23,
                         16,25,18,19
                        };
    maze->initWall(wall_des);
    maze->setTexture(texs.texture_name);

    mmd2 = new MD2Model();
    mmd2->load_model("\\model\\tris\\tris.md2");
    mmd2->load_skin(m_texs.texture_name[0]);
	mmd2->setScale(2);

    glEnable(GL_DEPTH_TEST);

    watcher_camera = new camera();
    float light_position_0[3] = {maze_xyz[0] + maze_w_num * maze_unit /2 , maze_xyz[1] + maze_y_num * maze_unit , maze_xyz[2] + maze_h_num * maze_unit /2};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light_position_1[3] = {0,0,0};
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
}

void changSize(int width,int height) {
    if (height == 0) {
        height =1;
    }

    GLfloat w = (GLfloat)width;
    GLfloat h = (GLfloat)height;
    GLfloat w_h_scale;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    w_h_scale = w / h;
    gluPerspective(50,w_h_scale,20,3000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const float * e = watcher_camera->getEye();
    const float * c = watcher_camera->getCenter();
    const float * u = watcher_camera->getUp();
    gluLookAt(e[0],e[1],e[2],c[0],c[1],c[2],u[0]-e[0],u[1]-e[1],u[2]-e[2]);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    mmd2->drawFrame(1);
    maze->drawMaze();
    glDisable(GL_CULL_FACE);
    glFlush();
    glutSwapBuffers();

}

void keyPress(unsigned char key,int width,int height) {
    switch(key) {
    case 'w': {
        watcher_camera->moveCamera(CAMERA_MOVE_FORWARD);
    }
    break;
    case 'a': {
        watcher_camera->moveCamera(CAMERA_MOVE_LEFT);
    }
    break;
    case 's': {
        watcher_camera->moveCamera(CAMERA_MOVE_BACK);
    }
    break;
    case 'd': {
        watcher_camera->moveCamera(CAMERA_MOVE_RIGHT);
    }
    break;
    case 27:
        exit(0);
        break;
    }
}

void activeMotion(int x,int y) {

}

void passiveMotion(int x,int y) {
    float t;
    float a;
    t = (x /(float)SCREEN_WIDTH - 0.5) * PI_MUL_2;
    a = (y /(float)SCREEN_HEIGHT - 0.5) * PI_DEV_2;
    watcher_camera->rotateCamera(a,-t);

}

void TimerProc() {
    glutTimerFunc(16,&timerFunc,1);
}

void timerFunc(int id) {
    glutPostRedisplay();
    glutTimerFunc(10,&timerFunc,1);
}

unsigned char * loadBitmap(const char * filename,BITMAPINFOHEADER & info_head) {
    BITMAPFILEHEADER file_head;
    FILE * file = NULL;
    unsigned char * data = NULL;
    char current_dir[512];
    GetCurrentDirectory(512,current_dir);
    strcat(current_dir,filename);
    file = fopen(current_dir,"rb");
    if (file == NULL) {
        return NULL;
    }
    fread(&file_head,sizeof(BITMAPFILEHEADER),1,file);
    if (file_head.bfType != BITMAP_TYPE) {
        return NULL;
    } else {
        fread(&info_head,sizeof(BITMAPINFOHEADER),1,file);
        fseek(file,file_head.bfOffBits,SEEK_SET);
        data = new unsigned char[info_head.biSizeImage];
        if (data) {
            fread(data,info_head.biSizeImage,1,file);
            for(int imageIdx=0; imageIdx < info_head.biSizeImage; imageIdx += 3) {
                unsigned char tempRGB = data[imageIdx];
                data[imageIdx]=data[imageIdx+2];
                data[imageIdx+2]=tempRGB;
            }
            return data;
        } else {
            return NULL;
        }
    }
}



