#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <GL/glew.h>
#include "../Header/Basics.h"
#include "../Header/Bezier.h"
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
/*
 * separar em x y z
 * seila = M * V (4x4 * 4x1 = 4x1)
 * seila2x = px * seila (4x4 * 4x1 = 4x1)
 * seila2y = py * seila (4x4 * 4x1 = 4x1)
 * seila2z = pz * seila (4x4 * 4x1 = 4x1)
 * seila2x = M * seila2x (4x4 * 4x1 = 4x1)
 * seila2y = M * seila2y (4x4 * 4x1 = 4x1)
 * seila2z = M * seila2z (4x4 * 4x1 = 4x1)
 * resx = U * seila2x = (1x4 * 4x1 = 1)
 * resy = U * seila2y = (1x4 * 4x1 = 1)
 * resz = U * seila2z = (1x4 * 4x1 = 1)
 * res = (resx, resy, resz)
 * this->pointsConnections->push_back(res)
 * Pescorrer os pontos e desenhar strips
 * this->pointsConnections = new std::vector<std::vector<float>>();
 */
void Bezier::calculaPoints( std::vector<std::vector<int>> indices, std::vector<std::vector<float>> points) {
    float px[4][4];
    float py[4][4];
    float pz[4][4];
    float m[4][4];
    bezierMatrixM(m);
    for(int i = 0; i < indices.size(); i++)
    {
        std::vector<std::vector<float>> patch;
        std::vector<int> indexline = indices[i];
        std::vector<std::vector<float>> p0;
        std::vector<std::vector<float>> p1;
        std::vector<std::vector<float>> p2;
        std::vector<std::vector<float>> p3;
        for(int j = 0; j < 4; j++)
        {
            p0.push_back(points[indexline[j]]);
            p1.push_back(points[indexline[j+4]]);
            p2.push_back(points[indexline[j+8]]);
            p3.push_back(points[indexline[j+12]]);
        }
        bezierMatrixPoints(p0,p1,p2,p3,px,py,pz);
        float uvalor = 0;
        float u[4];
        int iteracoes = this->lim+1;
        for(int primeiras = 0; primeiras < iteracoes; primeiras++)
        {
            float vvalor = 0;
            float v[4];
            bezierMatrixUV(uvalor,u);
            for(int segundas = 0; segundas < iteracoes; segundas++)
            {
                bezierMatrixUV(vvalor,v);
                float res1[4];
                multMatrixVector(m,v,res1);
                float resx1[4];
                float resy1[4];
                float resz1[4];
                multMatrixVector(px,res1,resx1);
                multMatrixVector(py,res1,resy1);
                multMatrixVector(pz,res1,resz1);
                float resx2[4];
                float resy2[4];
                float resz2[4];
                multMatrixVector(m,resx1,resx2);
                multMatrixVector(m,resy1,resy2);
                multMatrixVector(m,resz1,resz2);
                float resx3 = multiplicaVetores(u,resx2);
                float resy3 = multiplicaVetores(u,resy2);
                float resz3 = multiplicaVetores(u,resz2);
                std::vector<float> point;
                point.push_back(resx3);
                point.push_back(resy3);
                point.push_back(resz3);
                patch.push_back(point);
                vvalor += (float) 1/this->lim;
            }
            uvalor += (float) 1/this->lim;
        }
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
    this->allVertices = new GLuint[numlinhas];
    glGenBuffers(numlinhas, this->allVertices);
    this->sizeVertices = numlinhas;
    int index = 0;
    for(int i = 0; i < allPoints->size(); i++)
    {
        std::vector<std::vector<float>> patch = allPoints->at(i);
        std::vector<float> points;
        for(int j = 0; j < patch.size(); j++)
        {
            std::vector<float>point = patch[j];
            points.push_back(point[0]);
            points.push_back(point[1]);
            points.push_back(point[2]);
            if(j%2 != 0 && j % num == num-1)
            {
                glBindBuffer(GL_ARRAY_BUFFER, this->allVertices[index]);
                glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
                points.clear();
                index++;
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
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glColor3f(1,1,1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    for(int i = 0; i < sizeVertices; i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, allVertices[i]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, verticeCount);
    }
    glPopMatrix();
}
