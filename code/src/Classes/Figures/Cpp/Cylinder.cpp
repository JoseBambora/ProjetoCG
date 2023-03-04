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
        c->radius = std::stof(argv[2]);
        c->height = std::stof(argv[3]);
        c->slices = std::stoi(argv[4]);
        std::string name = argv[5];
        c->Write_File(name);
    }
    else
        printf("Invalid arguments for cylinder. Creating a cylinder with default values.\n");
    return c;
}

void Cylinder::Write_File(const std::string &name) {
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &Figure::codCylinder,sizeof(Figure::codCylinder));
    myfile.write((char *) &radius,sizeof(radius));
    myfile.write((char *) &height,sizeof(height));
    myfile.write((char *) &slices,sizeof(slices));
    myfile.close();
}

Cylinder *Cylinder::Read_File(std::ifstream file) {
    auto *res = new Cylinder();
    float radius, height;
    int slices;
    file.read((char *) &radius, sizeof(radius));
    file.read((char *) &height, sizeof(height));
    file.read((char *) &slices, sizeof(slices));
    res->radius = radius;
    res->slices = slices;
    res->height = height;
    return res;
}

std::string Cylinder::toString() {
    std::string res = "\tCylinder:\n";
    res.append("\t\tRadius: ");
    res.append(std::to_string(this->radius));
    res.append("\n\t\tHeight: ");
    res.append(std::to_string(this->height));
    res.append("\n\t\tSlices: ");
    res.append(std::to_string(this->slices));
    return res;
}

Cylinder::~Cylinder() {

}

void Cylinder::drawFigure() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    std::vector<float> basecima = getPointsCircumference(0,this->height,0,this->radius,this->slices);
    std::vector<float> basebaixo = getPointsCircumference(0,0,0,this->radius,this->slices);
    drawPyramid(basecima,0,this->height,0, true,1.0f,1.0f,1.0f);
    drawPyramid(basebaixo,0,0,0, false,1.0f,1.0f,1.0f);
    drawSide(basebaixo,basecima,1.0f,1.0f,1.0f);
}
