//
// Created by josebambora on 04-03-2023.
//

#include <vector>
#include <fstream>
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

void Cylinder::drawFigure() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    drawPyramid(basecima,centrocima[0],centrocima[1],centrocima[2], true,1.0f,1.0f,1.0f);
    drawPyramid(basebaixo,0,0,0, false,1.0f,1.0f,1.0f);
    drawSideFora(basebaixo,basecima,1.0f,1.0f,1.0f);
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
