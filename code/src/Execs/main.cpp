#include "../Classes/Figures/Header/Bezier.h"
#include <GL/glut.h>
Bezier b = Bezier("../teapot.patch",10);
#include <cmath>
float alfa;
float beta;

void processSpecialKeys(int key, int xx, int yy) {
    double c = M_PI / 18;
    switch (key) {
        case GLUT_KEY_LEFT:
            alfa -= c;
            break;
        case GLUT_KEY_RIGHT:
            alfa += c;
            break;
        case GLUT_KEY_UP:
            beta += c;
            if (beta > M_PI / 2) beta = M_PI_2;
            break;
        case GLUT_KEY_DOWN:
            beta -= c;
            if (beta < (-1) * M_PI / 2) beta = (-1) * M_PI_2;
            break;
    }
    glutPostRedisplay();
}

void changeSize(int w, int h)
{
    // prevent a divide by zero, when window is too short
    // (you can not make a window with zero width).
    if (h == 0)
        h = 1;
    // compute window's aspect ratio
    float ratio = w * 1.0f / h;

    // set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load the identity matrix
    glLoadIdentity();
    // set the perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);

    // et the viewport to be the entire window
    glViewport(0, 0, w, h);
}


void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int  k = 10;
    // set camera
    glLoadIdentity();
    gluLookAt(k*cos(beta)*sin(alfa), k*sin(beta), k*cos(beta)*cos(alfa),
              0,0,0,
    0,1,0);
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f( 100.0f, 1.0f, 1.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 100.0f, 1.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 100.0f);
    glEnd();

    glColor3f(1,1,1);

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    b.drawFigure();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI");
    // put callback registry here
    glutReshapeFunc(changeSize);
    // glutIdleFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);
    glutDisplayFunc(renderScene);
    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // enter GLUTs main cycle
    glutMainLoop();
}
