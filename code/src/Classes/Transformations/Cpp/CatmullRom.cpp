#include "../Header/CatmullRom.h"
#include <GL/glut.h>
#include "../../EngineClasses/Header/MatrixOperations.h"
#include <cmath>

CatmullRom::CatmullRom(std::vector<float> *points,float time, bool align)
{
    this->last_time = 0;
    this->aux = 0;
    this->time = time;
    this->align = align;
    this->POINT_COUNT = points->size()/3;
    this->p = new float *[this->POINT_COUNT];
    int j = 0;
    for(int i = 0; i < points->size(); i+=3)
    {
        this->p[j] = new float[3];
        this->p[j][0] = points->at(i);
        this->p[j][1] = points->at(i+1);
        this->p[j][2] = points->at(i+2);
        j++;
    }
}

void CatmullRom::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv)
{
    float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
                     { 1.0f, -2.5f,  2.0f, -0.5f},
                     {-0.5f,  0.0f,  0.5f,  0.0f},
                     { 0.0f,  1.0f,  0.0f,  0.0f}};

    for(int i = 0; i < 3; i++)
    {
        float points[4] = {p0[i],p1[i],p2[i],p3[i]};
        auto * res = new float[4];
        multMatrixVector(m,points,res);
        pos[i] = powf(t,3) * res[0] + powf(t,2) * res[1] + t * res[2] + res[3];
        deriv[i] = powf(t,2) * res[0] + t * res[1] + res[2];
        delete []res;
    }
}

void CatmullRom::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv)
{
    float t = gt * POINT_COUNT; // this is the real global t
    int index = floor(t);    // which segment
    t = t - index;              // where within  the segment
    // indices store the points
    int indices[4];
    indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;
    indices[1] = (indices[0]+1)%POINT_COUNT;
    indices[2] = (indices[1]+1)%POINT_COUNT;
    indices[3] = (indices[2]+1)%POINT_COUNT;

    getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}


void CatmullRom::renderCatmullRomCurve()
{
    auto *pos = new float[3];
    auto *deriv = new float[3];
    glBegin(GL_LINE_LOOP);
    //glColor3f(0,0,0);
    float gt = 0;
    while (gt < 1)
    {
        getGlobalCatmullRomPoint(gt, pos, deriv);
        glVertex3f(pos[0],pos[1],pos[2]);
        gt += 1.0/100.0;
    }
    glEnd();
    delete []pos;
    delete []deriv;
}

CatmullRom::~CatmullRom() {
    for(int i = 0; i < this->POINT_COUNT; i+=3)
    {
        delete[] p[i];
    }
    delete[] p;
}

void CatmullRom::applyTransformations() {
    glPushMatrix();
    auto *pos = new float[3];
    auto *deriv = new float[3];
    getGlobalCatmullRomPoint(this->aux, pos, deriv);
    glTranslatef(pos[0], pos[1], pos[2]);
    if(this->align)
    {
        float X[3] = {deriv[0], deriv[1], deriv[2]};
        float m[16];
        normalize(X);
        float Z[3];
        crossnormalize(X, Y, Z);
        crossnormalize(Z, X, Y);
        buildRotMatrix(X, Y, Z, m);
        glMultMatrixf(m);
    }
    delete[] pos;
    delete[] deriv;
    int current_time = glutGet(GLUT_ELAPSED_TIME);
    float occor = ((float) current_time-last_time)/1000;
    this->last_time = current_time;
    this->aux += occor / this->time;
}

void CatmullRom::apply() {
    this->renderCatmullRomCurve();
    this->applyTransformations();
}

std::string CatmullRom::toString() {
    return "CatmullRom curva";
}