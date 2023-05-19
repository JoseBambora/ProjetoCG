#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include "../Header/Sphere.h"
#include "../Header/Basics.h"
#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include "GL/glut.h"

const int Figure::codSphere;

Sphere* Sphere::Build(int argc, char **argv) {
    auto *s = new Sphere();
    if(argc == 6)
    {
        float radius = std::stof(argv[2]);
        int slices = std::stoi(argv[3]);
        int stacks = std::stoi(argv[4]);
        s->calculatePoints(radius,slices,stacks);
        std::string name = argv[5];
        s->Write_File(name);
    }
    else
        printf("Invalid arguments for sphere. Creating a sphere with default values.\n");
    return s;
}

/**
 * n linhas circunferências laterais
 * últimas 2 linhas:
 *  - verticesuperior
 *  - verticeinferior
 */

void Sphere::Write_File(const std::string &name) {
    std::vector<std::vector<float>> write = this->superficielateral;
    write.push_back(this->verticesuperior);
    write.push_back(this->verticeinferior);
    writePoints(write,name,Figure::codSphere);
}

Sphere* Sphere::Read_File(std::ifstream file) {
    auto *res = new Sphere();
    std::vector<std::vector<float>> read = readPoints(std::move(file));
    res->superficielateral = std::vector<std::vector<float>>(read.begin(),read.end()-2);
    res->verticesuperior = read[read.size()-2];
    res->verticeinferior = read[read.size()-1];
    return res;
}

std::string Sphere::toString()  {
    std::string res = "Sphere:";
    // res.append("\t\tVertice Superior:");
    // res.append("(");
    // res.append(std::to_string(this->verticesuperior[0]));
    // res.append(",");
    // res.append(std::to_string(this->verticesuperior[1]));
    // res.append(",");
    // res.append(std::to_string(this->verticesuperior[2]));
    // res.append(")\n");
    // res.append("\t\tVertice Inferior:");
    // res.append("(");
    // res.append(std::to_string(this->verticeinferior[0]));
    // res.append(",");
    // res.append(std::to_string(this->verticeinferior[1]));
    // res.append(",");
    // res.append(std::to_string(this->verticeinferior[2]));
    // res.append(")\n");
    // res.append("\t\tNúmero circunferências laterais:");
    // res.append(std::to_string(this->superficielateral.size()));
    return res;
}

void Sphere::calculatePoints(float radius, int slices, int stacks)
{
    this->superficielateral = std::vector<std::vector<float>>();
    float aumento = M_PI/stacks;
    float alfa = -M_PI_2;
    for(int i = 0; i < stacks;i++)
    {
        float yc = std::sin(alfa) * radius;
        float r = std::cos(alfa) * radius;
        std::vector<float> c = getPointsCircumference(0,yc,0,r,slices);
        this->superficielateral.push_back(c);
        alfa += aumento;
    }
    verticesuperior = std::vector<float>();
    verticesuperior.push_back(0);
    verticesuperior.push_back(radius);
    verticesuperior.push_back(0);
    verticeinferior = std::vector<float>();
    verticeinferior.push_back(0);
    verticeinferior.push_back(-radius);
    verticeinferior.push_back(0);
}

void Sphere::loadVBO() {
    auto * allPoints = new std::vector<float>();
    std::vector<float> anterior;
    std::vector<float> primeira;
    for(int i = 0; i < this->superficielateral.size();i++)
    {
        std::vector<float> c = this->superficielateral[i];
        if(i > 0)
            connectSideFora(allPoints,anterior,c,&normaisvetor,0,0,0);
        else
            primeira = c;
        anterior = c;
    }
    connectPyramid(allPoints,anterior,this->verticesuperior[0],this->verticesuperior[1],this->verticesuperior[2], false,&normaisvetor,
                   false,0,0,0);
    connectPyramid(allPoints,primeira,this->verticeinferior[0],this->verticeinferior[1],this->verticeinferior[2], true,&normaisvetor,
                   false,0,0,0);
    this->loadVertices(saveInfoPlacaGraficaIluminacao(allPoints,&normaisvetor),allPoints->size()/3);
    //this->loadVertices(saveInfoPlacaGrafica(allPoints));
    delete allPoints;
}

void Sphere::loadNormais() {
    for(int i = 0; i < this->superficielateral.size();i++)
    {
        std::vector<float>  circ = this->superficielateral.at(i);
        calculaNormaisCircunferencia(&circ,0,0,0,&this->normaisvetor);
    }
    calculaNormalBases(true,&this->normaisvetor);
    calculaNormalBases(false,&this->normaisvetor);
}

Sphere::~Sphere() = default;
