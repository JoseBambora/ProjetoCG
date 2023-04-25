#include <vector>
#include <cmath>
#include <fstream>
#include "../Header/Basics.h"
#include <GL/glew.h>
#include <GL/glut.h>

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


void drawSide(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue, bool dentro)
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
        if(!dentro)
        {
            glVertex3f(px1,py1,pz1);
            glVertex3f(px3,py3,pz3);
            glVertex3f(px2,py2,pz2);

            glVertex3f(px4,py4,pz4);
            glVertex3f(px2,py2,pz2);
            glVertex3f(px3,py3,pz3);
        }
        else
        {
            glVertex3f(px1,py1,pz1);
            glVertex3f(px2,py2,pz2);
            glVertex3f(px3,py3,pz3);

            glVertex3f(px4,py4,pz4);
            glVertex3f(px3,py3,pz3);
            glVertex3f(px2,py2,pz2);
        }
        i += 2;
    }
    glEnd();
}


// Draw the connection between 2 circunference (basically 2 triangles).
// s1 and s2 have the coordinates of the points of both circunference.
void drawSideFora(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue)
{
    drawSide(cbaixo,ccima,cred,cgreen,cblue, false);
}

void drawSideDentro(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue)
{
    drawSide(cbaixo,ccima,cred,cgreen,cblue, true);
}

std::vector<std::vector<float>> readPoints(std::ifstream file)
{
    std::vector<std::vector<float>> res =std::vector<std::vector<float>>();
    size_t ss;
    file.read((char *) &ss,sizeof(ss));
    for(int i = 0; i < ss; i++)
    {
        size_t ss_;
        file.read((char *) &ss_,sizeof(ss));
        res.emplace_back();
        for(int j = 0; j < ss_; j++)
        {
            float num;
            file.read((char *) &num, sizeof(num));
            res[i].push_back(num);
        }
    }
    return res;
}

void writePoints(std::vector<std::vector<float>> circunferences, const std::string& name, int codigo)
{
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &codigo,sizeof(codigo));
    size_t ss = circunferences.size();
    myfile.write((char *) &ss,sizeof(ss));
    for(int i = 0; i < ss; i++)
    {
        size_t ss_ = circunferences[i].size();
        myfile.write((char *) &ss_,sizeof(ss_));
        for(int j = 0; j < ss_; j++)
            myfile.write((char *) &(circunferences[i][j]),sizeof(circunferences[i][j]));
    }
    myfile.close();
}


void connectPyramid(std::vector<float> *allPoints,std::vector<float> base, float x, float y, float z, bool direcao)
{
    for (int i = 0; i < base.size() - 3; i+=3) {
        float px1 = base.at(i);
        float py1 = base.at(i + 1);
        float pz1 = base.at(i + 2);
        float px2 = base.at(i + 3);
        float py2 = base.at(i + 4);
        float pz2 = base.at(i + 5);
        allPoints->push_back(x);
        allPoints->push_back(y);
        allPoints->push_back(z);
        if (direcao)
        {
            allPoints->push_back(px2);
            allPoints->push_back(py2);
            allPoints->push_back(pz2);
            allPoints->push_back(px1);
            allPoints->push_back(py1);
            allPoints->push_back(pz1);
        }
        else
        {
            allPoints->push_back(px1);
            allPoints->push_back(py1);
            allPoints->push_back(pz1);
            allPoints->push_back(px2);
            allPoints->push_back(py2);
            allPoints->push_back(pz2);
        }
    }
}

void connectSide(std::vector<float> *allPoints,std::vector<float> b1,std::vector<float> b2, bool dentro)
{
    for(int i = 0; i < b1.size(); i+=3)
    {
        if(i+3 < b1.size())
        {
            float px1 = b1.at(i);
            float py1 = b1.at(i+1);
            float pz1 = b1.at(i+2);

            float px2 = b2.at(i);
            float py2 = b2.at(i+1);
            float pz2 = b2.at(i+2);

            float px3 = b1.at(i+3);
            float py3 = b1.at(i+4);
            float pz3 = b1.at(i+5);

            float px4 = b2.at(i+3);
            float py4 = b2.at(i+4);
            float pz4 = b2.at(i+5);


            if(!dentro)
            {


                allPoints->push_back(px1);
                allPoints->push_back(py1);
                allPoints->push_back(pz1);
                allPoints->push_back(px3);
                allPoints->push_back(py3);
                allPoints->push_back(pz3);
                allPoints->push_back(px2);
                allPoints->push_back(py2);
                allPoints->push_back(pz2);

                allPoints->push_back(px4);
                allPoints->push_back(py4);
                allPoints->push_back(pz4);
                allPoints->push_back(px2);
                allPoints->push_back(py2);
                allPoints->push_back(pz2);
                allPoints->push_back(px3);
                allPoints->push_back(py3);
                allPoints->push_back(pz3);
            }
            else
            {


                allPoints->push_back(px1);
                allPoints->push_back(py1);
                allPoints->push_back(pz1);
                allPoints->push_back(px2);
                allPoints->push_back(py2);
                allPoints->push_back(pz2);
                allPoints->push_back(px3);
                allPoints->push_back(py3);
                allPoints->push_back(pz3);

                allPoints->push_back(px4);
                allPoints->push_back(py4);
                allPoints->push_back(pz4);
                allPoints->push_back(px3);
                allPoints->push_back(py3);
                allPoints->push_back(pz3);
                allPoints->push_back(px2);
                allPoints->push_back(py2);
                allPoints->push_back(pz2);
            }
        }
    }
}

void connectSideFora(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima)
{
    connectSide(allPoints,cbaixo,ccima,false);
}

void connectSideDentro(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima)
{
    connectSide(allPoints,cbaixo,ccima,true);
}

GLuint* saveInfoPlacaGrafica(std::vector<float> *allPoints)
{
    GLuint verticeCount = allPoints->size() / 3;
    GLuint vertices;
    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * allPoints->size(), allPoints->data(), GL_STATIC_DRAW);
    auto * res = new GLuint[2];
    res[0] = verticeCount;
    res[1] = vertices;
    return res;
}


void drawVBO(GLuint vertices, GLuint verticeCount, float red, float green, float blue)
{
    glColor3f(red,green,blue);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, verticeCount);
}

