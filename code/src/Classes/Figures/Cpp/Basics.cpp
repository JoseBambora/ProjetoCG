#include <vector>
#include <cmath>
#include "../Header/Basics.h"
#include "GL/glut.h"

// Get Points from one circunference
// X Y Z -> coordinates of the center point
// The circunference will be around the Y axis
std::vector<float> getPointsCircumference(float x, float y, float z, float radius, int slices) {
    std::vector<float> res = std::vector<float>();
    double angle = 0;
    double rotation = (2 * M_PI) / (float) slices;
    for (int i = 0; i <= slices; i++) {
        auto px = (float) (radius * sin(angle)) + x;
        auto py = y;
        auto pz = (float) (radius * cos(angle)) + z;
        res.push_back(px);
        res.push_back(py);
        res.push_back(pz);
        angle += rotation;
    }
    return res;
}

// Draws a pyramid, independently of the format of its base
// x y and z are the coordinates of the top of the pyramid.
void drawPyramid(std::vector<float> base, float x, float y, float z, bool direcao,  float cred, float cgreen, float cblue)
{
    glBegin(GL_TRIANGLES);
    glColor3f(cred, cgreen, cblue);
    for(int i = 0; i < base.size()-3; i++)
    {
        float px1 = base.at(i);
        float py1 = base.at(i + 1);
        float pz1 = base.at(i + 2);
        float px2 = base.at(i + 3);
        float py2 = base.at(i + 4);
        float pz2 = base.at(i + 5);
        if(direcao)
        {
            glVertex3f(x,y,z);
            glVertex3f(px1,py1,pz1);
            glVertex3f(px2,py2,pz2);
        }
        else
        {
            glVertex3f(x,y,z);
            glVertex3f(px2,py2,pz2);
            glVertex3f(px1,py1,pz1);
        }
        i+=2;
    }
    glEnd();
}

// Draw the connection between 2 circunference (basically 2 triangles).
// s1 and s2 have the coordinates of the points of both circunference.
void drawSide(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue)
{
    glBegin(GL_TRIANGLES);
    glColor3f(cred, cgreen, cblue);
    for(int i = 0; i < cbaixo.size(); i++)
    {
        float px1 = cbaixo.at(i);
        float py1 = cbaixo.at(i+1);
        float pz1 = cbaixo.at(i+2);

        float px2 = ccima.at(i);
        float py2 = ccima.at(i+1);
        float pz2 = ccima.at(i+2);
        float px3 = px2;
        float py3 = py2;
        float pz3 = pz2;

        float px4 = px3;
        float py4 = py3;
        float pz4 = pz3;
        if(i+3 < cbaixo.size()){
            px3 = cbaixo.at(i+3);
            py3 = cbaixo.at(i+4);
            pz3 = cbaixo.at(i+5);
            px4 = ccima.at(i+3);
            py4 = ccima.at(i+4);
            pz4 = ccima.at(i+5);
        }
        glVertex3f(px1,py1,pz1);
        glVertex3f(px3,py3,pz3);
        glVertex3f(px2,py2,pz2);

        glVertex3f(px4,py4,pz4);
        glVertex3f(px2,py2,pz2);
        glVertex3f(px3,py3,pz3);
        i += 2;
    }
    glEnd();
}