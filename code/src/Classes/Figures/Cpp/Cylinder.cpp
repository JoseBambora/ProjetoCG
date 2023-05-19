//
// Created by josebambora on 04-03-2023.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "../Header/Cylinder.h"
#include "../Header/Basics.h"
#include "GL/glut.h"

const int Figure::codCylinder;
Cylinder *Cylinder::Build(int argc, char **argv) {
    auto *c = new Cylinder();
    if(argc == 6)
    {
        float radius = std::stof(argv[2]);
        float height = std::stof(argv[3]);
        int slices = std::stoi(argv[4]);
        std::string name = argv[5];
        c->calculatePoints(radius,height,slices);
        c->Write_File(name);
    }
    else
        printf("Invalid arguments for cylinder. Creating a cylinder with default values.\n");
    return c;
}

/**
 * 1ª linha base de baixo
 * 2ª linha base de cima
 * 3ª linha coordenadas do centro da base de cima
 */

void Cylinder::Write_File(const std::string &name) {
    std::vector<std::vector<float>> c = std::vector<std::vector<float>>();
    c.push_back(this->basebaixo);
    c.push_back(this->basecima);
    c.push_back(this->centrocima);
    writePoints(c, name, Figure::codCylinder);
}

Cylinder *Cylinder::Read_File(std::ifstream file) {
    auto *res = new Cylinder();
    std::vector<std::vector<float>> bases = readPoints(std::move(file));
    res->basebaixo = bases[0];
    res->basecima = bases[1];
    res->centrocima = bases[2];
    return res;
}

std::string Cylinder::toString() {
    std::string res = "Cylinder";
    // res.append("\t\tCentro Superior:");
    // res.append("(");
    // res.append(std::to_string(this->centrocima[0]));
    // res.append(",");
    // res.append(std::to_string(this->centrocima[1]));
    // res.append(",");
    // res.append(std::to_string(this->centrocima[2]));
    // res.append(")\n");
    return res;
}

Cylinder::~Cylinder() {

}

void Cylinder::calculatePoints(float radius, float height, int slices)
{
    this->basecima = getPointsCircumference(0,height,0,radius,slices);
    this->basebaixo = getPointsCircumference(0,0,0,radius,slices);
    this->centrocima = std::vector<float>();
    centrocima.push_back(0);
    centrocima.push_back(height);
    centrocima.push_back(0);
}

void Cylinder::loadVBO() {
    auto * allPoints = new std::vector<float>();
    connectPyramid(allPoints,basecima,centrocima[0],centrocima[1],centrocima[2], false,&normaisvetor, true,0,0,0);
    connectPyramid(allPoints,basebaixo,0,0,0, true,&normaisvetor,true,0,0,0);
    connectSideForaV2(allPoints,basebaixo,basecima,&normaisvetor,0,0,0,centrocima[0],centrocima[1],centrocima[2]);
    this->loadVertices(saveInfoPlacaGraficaIluminacao(allPoints,&normaisvetor),allPoints->size()/3);
    delete allPoints;
}
