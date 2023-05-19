#include <vector>
#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <fstream>
#include "../Header/Basics.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <IL/il.h>
#include "../../EngineClasses/Header/MatrixOperations.h"


void calculaNormaisCircunferenciaV2(float x1, float y1, float z1, float x, float y, float z,std::vector<float>* normais)
{
    float normal[3] = {x1 - x,y1 - y,z1 - z};
    normalize(normal);
    normais->push_back(normal[0]);
    normais->push_back(normal[1]);
    normais->push_back(normal[2]);
}

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


void addPointsAndNormais(std::vector<float> *allPoints,std::vector<float> *normais,float x, float y, float z, float cx, float cy, float cz)
{
    allPoints->push_back(x);
    allPoints->push_back(y);
    allPoints->push_back(z);
    calculaNormaisCircunferenciaV2(x,y,z,cx,cy,cz,normais);
}

void addPointsAndNormaisV2(std::vector<float> *allPoints,std::vector<float> *normais,float x, float y, float z,bool booleano)
{
    allPoints->push_back(x);
    allPoints->push_back(y);
    allPoints->push_back(z);
    calculaNormalBases(booleano,normais);
}


void connectPyramid(std::vector<float> *allPoints,std::vector<float> base, float x, float y, float z, bool direcao, std::vector<float>*normais,bool plana,float cx,float cy,float cz)
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
            // baixo
            calculaNormalBases(false,normais);
            if(plana)
            {
                addPointsAndNormaisV2(allPoints,normais,px2,py2,pz2,false);
                addPointsAndNormaisV2(allPoints,normais,px1,py1,pz1,false);
            }
            else
            {
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px1,py1,pz1,cx,cy,cz);
            }
        }
        else
        {
            calculaNormalBases(false,normais);
            if(plana)
            {
                addPointsAndNormaisV2(allPoints,normais,px1,py1,pz1,true);
                addPointsAndNormaisV2(allPoints,normais,px2,py2,pz2,true);
            }
            else
            {
                addPointsAndNormais(allPoints,normais,px1,py1,pz1,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
            }
        }
    }
}

void connectSide(std::vector<float> *allPoints,std::vector<float> b1,std::vector<float> b2, bool dentro, float cx, float cy, float cz, std::vector<float>*normais)
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
                addPointsAndNormais(allPoints,normais,px1,py1,pz1,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);

                addPointsAndNormais(allPoints,normais,px4,py4,pz4,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);
            }
            else
            {

                addPointsAndNormais(allPoints,normais,px1,py1,pz1,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);

                addPointsAndNormais(allPoints,normais,px4,py4,pz4,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
            }
        }
    }
}


void connectSideV2(std::vector<float> *allPoints,std::vector<float> b1,std::vector<float> b2, bool dentro, float cx, float cy, float cz,float cx1,float cy1,float cz1, std::vector<float>*normais)
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
                addPointsAndNormais(allPoints,normais,px1,py1,pz1,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);

                addPointsAndNormais(allPoints,normais,px4,py4,pz4,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);
            }
            else
            {

                addPointsAndNormais(allPoints,normais,px1,py1,pz1,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);

                addPointsAndNormais(allPoints,normais,px4,py4,pz4,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px3,py3,pz3,cx,cy,cz);
                addPointsAndNormais(allPoints,normais,px2,py2,pz2,cx,cy,cz);
            }
        }
    }
}


void connectSideFora(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz)
{
    connectSide(allPoints,cbaixo,ccima,false,cx,cy,cz,normais);
}


void connectSideForaV2(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz,float cx1,float cy1,float cz1)
{
    connectSideV2(allPoints,cbaixo,ccima,false,cx,cy,cz,cx1,cy1,cz1,normais);
}


void connectSideDentro(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz)
{
    connectSide(allPoints,cbaixo,ccima,true,cx,cy,cz,normais);
}

void calculaNormaisCircunferencia(std::vector<float>* allPoints, float x, float y, float z,std::vector<float>* normais)
{
    for(int i = 0; i < allPoints->size(); i+=3)
    {
        float x1 = allPoints->at(i);
        float y1 = allPoints->at(i+1);
        float z1 = allPoints->at(i+2);
        calculaNormaisCircunferenciaV2(x1,y1,z1,x,y,z,normais);
    }
}


void add3Floats(std::vector<float> *res,float x,float y,float z)
{
    res->push_back(x);
    res->push_back(y);
    res->push_back(z);
}

void calculaNormalBases(bool cima, std::vector<float> *res)
{
    if(cima)
        add3Floats(res,0,1,0);
    else
        add3Floats(res,0,-1,0);
}

void calculaNormalSideYAngle(float delta,float deltay,std::vector<float> *res)
{
    add3Floats(res,sinf(delta),sinf(deltay),cosf(delta));
}

void calculaNormalSideY0(float delta,std::vector<float> *res)
{
    calculaNormalSideYAngle(delta,0,res);
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

GLuint* saveInfoPlacaGraficaIluminacao(std::vector<float> *allPoints, std::vector<float> *normais)
{
    auto * res = new GLuint[2];
    glGenBuffers(2, res);
    glBindBuffer(GL_ARRAY_BUFFER, res[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(float) * allPoints->size(), allPoints->data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, res[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normais->size(), normais->data(),GL_STATIC_DRAW);
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


void drawVBOIluminacao(GLuint *vbos, GLuint verticeCount)
{
    glBindBuffer(GL_ARRAY_BUFFER,vbos[0]);
    glVertexPointer(3,GL_FLOAT,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,vbos[1]);
    glNormalPointer(GL_FLOAT,0,0);

    glDrawArrays(GL_TRIANGLES, 0, verticeCount);
}

void materialLighting(std::vector<float> *ambient, std::vector<float> *diffuse, std::vector<float> *specular, std::vector<float> *emission,float shininess)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient->data());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse->data());
    glMaterialfv(GL_FRONT, GL_EMISSION, emission->data());
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular->data());
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


int loadTexture(std::string s) {
    unsigned int t, tw, th;
    unsigned char* texData;
    unsigned int texID;
    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texID;
}
