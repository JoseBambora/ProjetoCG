#include "../Header/World.h"
#include "../Header/Camera.h"
#include "../Header/Group.h"
#include "GL/glut.h"

World* World::instance;

World::World(float width, float height,
             float posx, float posy, float posz,
             float lax, float lay,float laz,
             float upx, float upy,float upz,
             float fov, float near,float far,
             ListTree * tree) {
    this->camera = new Camera(posx,posy,posz,lax,lay,laz,upx,upy,upz,fov,near,far);
    this->width = width;
    this->height = height;
    this->group = new Group(tree);
    instance = this;
}

std::string World::toString()
{
    std::string res;
    res.append("Width: ");
    res.append(std::to_string(this->width));
    res.append("\nHeigth: ");
    res.append(std::to_string(this->height));
    res.append("\n");
    res.append(this->camera->toString());
    res.append(this->group->toString());
    return res;
}

World::~World() {
    delete this->group;
    delete this->camera;
}

static void renderAllScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float w = World::instance->width;
    float h = World::instance->height;
    World::instance->camera->posicionaCamara(w,h);
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnd();
    World::instance->group->execute();
    glutSwapBuffers();
}


void World::drawWorld() {
    char** argv = new char*();
    int argc = 0;
    glutInit(&argc, argv);
    delete argv;
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(this->width, this->height);
    glutCreateWindow("Projeto CG - Grupo 20");
    glutSpecialFunc(Camera::processSpecialKeys);
    glutReshapeFunc(Camera::changeSize);
    glutIdleFunc(renderAllScene);
    glutDisplayFunc(renderAllScene);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    this->group->load();
    glutMainLoop();
}
