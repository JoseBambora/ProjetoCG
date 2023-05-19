#include <sstream>
#include <vector>
#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include "../Header/Bezier.h"
#include "../Header/Basics.h"
#include "../../EngineClasses/Header/MatrixOperations.h"

const int Figure::codBezierPatch;

template<typename T>
void getNumbers(std::istringstream iss, std::vector<T>* points)
{
    T number;
    while(iss >> number)
    {
        points->push_back(number);
        if (iss.peek() == ',' || iss.peek() == ' ')
            iss.ignore();
    }
}

void readInfoPatch(int *numpatchs, int *controlpoints,std::vector<std::vector<int>>* indices,std::vector<std::vector<float>>* points, const std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    int np;
    int cp;
    for (int i = 0; std::getline(infile, line); i++)
    {
        std::istringstream iss(line);
        if(i == 0)
            iss >> np;
        else if (i <= np)
        {
            std::vector<int> indexadd;
            getNumbers(std::move(iss),&indexadd);
            indices->push_back(indexadd);
        }
        else if (i == np + 1)
            iss >> cp;
        else
        {
            std::vector<float> pointAdd;
            getNumbers(std::move(iss),&pointAdd);
            points->push_back(pointAdd);
        }
    }
    *numpatchs = np;
    *controlpoints = cp;
}

Bezier::Bezier(const char *filename, int dim) {
    this->lim = dim;
    this->pointsCurve = new std::vector<std::vector<std::vector<float>>>();
    std::string file = filename;
    int numpatchs;
    int controlpoints;
    std::vector<std::vector<int>> indices;
    std::vector<std::vector<float>> points;
    readInfoPatch(&numpatchs,&controlpoints,&indices,&points,file);
    this->calculaPoints(indices,points);
}

void Bezier:: desenhaPatch(std::vector<std::vector<float>> patch)
{
    int num = this->lim + 1;
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glBegin(GL_TRIANGLE_STRIP);
    std::vector<std::vector<float>> repeat(patch.begin() + num, patch.end());
    for(int j = 0; j < repeat.size();j++)
    {
        std::vector<float> point = patch[j];
        std::vector<float> point2 = repeat[j];
        glVertex3f(point2[0],point2[1],point2[2]);
        glVertex3f(point[0],point[1],point[2]);
        if(j % num == num-1)
        {
            glEnd();
            glBegin(GL_TRIANGLE_STRIP);
        }
    }
    glEnd();
    glPopMatrix();
}

void Bezier::calculaPoints( std::vector<std::vector<int>> indices, std::vector<std::vector<float>> points) {

    float px[4][4];
    float py[4][4];
    float pz[4][4];
    float m[4][4];
    bezierMatrixM(m);
    for(int i = 0; i < indices.size(); i++)
    {
        std::vector<int> indexline = indices[i];
        std::vector<std::vector<float>> p0, p1,p2,p3;
        for(int j = 0; j < 4; j++)
        {
            p0.push_back(points[indexline[j]]);
            p1.push_back(points[indexline[j+4]]);
            p2.push_back(points[indexline[j+8]]);
            p3.push_back(points[indexline[j+12]]);
        }
        bezierMatrixPoints(p0,p1,p2,p3,px,py,pz);
        std::vector<std::vector<float>> patch;
        bezierGeraPatch(&patch,px,py,pz,m,this->lim);
        this->pointsCurve->push_back(patch);
    }
}
Bezier *Bezier::Build(int argc, char **argv) {
    Bezier *b;
    if(argc == 5)
    {
        char *filename = argv[2];
        int dim = std::stoi(argv[3]);
        char *filewrite = argv[4];
        b = new Bezier(filename,dim);
        b->Write_File(filewrite);
    }
    else
    {
        b = new Bezier();
        printf("Invalid arguments for bezier patch. Creating a empty patch with default values.\n");
    }
    return b;
}

void Bezier::Write_File(const std::string &name) {
    int codigo = Figure::codBezierPatch;
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &codigo,sizeof(codigo));
    myfile.write((char *) &this->lim,sizeof(this->lim));
    size_t ss = this->pointsCurve->size();
    myfile.write((char *) &ss,sizeof(ss));
    for(int i = 0; i < ss; i++)
    {
        size_t ss_ = this->pointsCurve->at(i).size();
        myfile.write((char *) &ss_,sizeof(ss_));
        for(int j = 0; j < ss_; j++)
        {
            size_t _ss_ = this->pointsCurve->at(i)[j].size();
            myfile.write((char *) &_ss_,sizeof(_ss_));
            for(int k = 0; k < _ss_; k++)
            {
                myfile.write((char *) &(this->pointsCurve->at(i)[j][k]),sizeof(this->pointsCurve->at(i)[j][k]));
            }
        }
    }
    myfile.close();

}

Bezier *Bezier::Read_File(std::ifstream file) {
    Bezier* res = new Bezier();
    res->pointsCurve = new std::vector<std::vector<std::vector<float>>>;
    file.read((char *) &res->lim, sizeof(res->lim));
    size_t ss;
    file.read((char *) &ss,sizeof(ss));
    for(int i = 0; i < ss; i++)
    {
        size_t ss_;
        file.read((char *) &ss_,sizeof(ss));
        std::vector<std::vector<float>> patch;
        for(int j = 0; j < ss_; j++)
        {
            std::vector<float> point;
            size_t _ss_;
            file.read((char *) &_ss_,sizeof(_ss_));
            for(int k = 0; k < _ss_; k++)
            {
                float num;
                file.read((char *) &num, sizeof(num));
                point.push_back(num);
            }
            patch.push_back(point);
        }
        res->pointsCurve->push_back(patch);
    }
    return res;
}

std::string Bezier::toString() {
    return "Curva Bezier";
}

void Bezier::getAllPoints(std::vector<std::vector<std::vector<float>>>* allPoints)
{
    for(std::vector<std::vector<float>> patch : *this->pointsCurve)
    {
        std::vector<std::vector<float>> points;
        int num = this->lim + 1;
        std::vector<std::vector<float>> repeat(patch.begin() + num, patch.end());
        for(int j = 0; j < repeat.size();j++)
        {
            std::vector<float> point = patch[j];
            std::vector<float> point2 = repeat[j];
            points.push_back(point2);
            points.push_back(point);
        }
        allPoints->push_back(points);
    }
}

void Bezier::loadAllPoints(std::vector<std::vector<std::vector<float>>>* allPoints)
{
    int num = this->lim + 1;
    int numlinhas = this->lim * allPoints->size();
    this->verticeCount = (this->lim+1)*2;
    this->allVertices = new GLuint[numlinhas*3];
    glGenBuffers(numlinhas*3, this->allVertices);
    this->sizeVertices = numlinhas*3;
    int index = 0;
    for(auto patch : *allPoints)
    {
        std::vector<float> points, normais, texturas;
        for(int j = 0; j < patch.size(); j++)
        {
            std::vector<float>point = patch[j];
            points.push_back(point[0]);
            points.push_back(point[1]);
            points.push_back(point[2]);
            // to do: point irá conter a normal também, acumular no vetor normais
            normais.push_back(point[3]);
            normais.push_back(point[4]);
            normais.push_back(point[5]);

            texturas.push_back(point[6]);
            texturas.push_back(point[7]);
            if(j%2 != 0 && j % num == num-1)
            {
                glBindBuffer(GL_ARRAY_BUFFER, this->allVertices[index]);
                glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, this->allVertices[index+1]);
                glBufferData(GL_ARRAY_BUFFER, normais.size() * sizeof(float) , normais.data(),GL_STATIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, this->allVertices[index+2]);
                glBufferData(GL_ARRAY_BUFFER, texturas.size() * sizeof(float), texturas.data(), GL_STATIC_DRAW);

                points.clear();
                normais.clear();
                texturas.clear();

                index+=3;
            }
        }
    }
}

void Bezier::loadVBO() {
    std::vector<std::vector<std::vector<float>>> allPoints;
    getAllPoints(&allPoints);
    loadAllPoints(&allPoints);
}

Bezier::Bezier() {
    this->lim = 0;
    this->pointsCurve = nullptr;
}

void Bezier::drawFigure() {
    if (this->texturaID == 0)
        materialLighting(ambient,diffuse,specular,emissive,shininnes);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, this->texturaID);
    for(int i = 0; i < sizeVertices; i+=3)
    {
        glBindBuffer(GL_ARRAY_BUFFER, allVertices[i]);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER,allVertices[i+1]);
        glNormalPointer(GL_FLOAT,0,0);

        glBindBuffer(GL_ARRAY_BUFFER,allVertices[i+2]);
        glTexCoordPointer(2,GL_FLOAT,0,0);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, verticeCount);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}