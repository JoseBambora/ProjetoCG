
#include <fstream>
#include <vector>
#include "../Header/Donut.h"
#include "../Header/Basics.h"
#include <cmath>
#include "GL/glut.h"

const int Figure::codDonut;

Donut* Donut::Build(int argc, char **argv)
{
    auto *res = new Donut();
    if(argc == 7)
    {
        float rin = std::stof(argv[2]);
        float rout = std::stof(argv[3]);
        int slices = std::stoi(argv[4]);
        int stacks = std::stoi(argv[5]);
        std::string name = argv[6];
        res->calculatePoints(rin,rout,slices,stacks);
        res->Write_File(name);
    }
    else
        printf("Invalid arguments for donut. Creating a donut with default values.\n");
    return res;
}

void Donut::Write_File(const std::string &name) {
    writePoints(this->superficielateral, name, Figure::codDonut);
}

Donut *Donut::Read_File(std::ifstream file) {
    auto *res = new Donut();
    res->superficielateral = readPoints(std::move(file));
    return res;
}

std::string Donut::toString() {
    std::string res = "Donut";
    // res.append("\t\tNúmero circunferências laterais:");
    // res.append(std::to_string(this->superficielateral.size()));
    return res;
}

Donut::~Donut() {

}

void Donut::drawFigure() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    std::vector<float> anteriorint = this->superficielateral[0];
    std::vector<float> anteriorext = this->superficielateral[0];
    for(int i = 1; i < this->superficielateral.size(); i+=2)
    {
        std::vector<float> cint = this->superficielateral[i];
        std::vector<float> cext = this->superficielateral[i+1];
        drawSideDentro(anteriorint,cint,1.0f,1.0f,1.0f);
        drawSideFora(anteriorext,cext,1.0f,1.0f,1.0f);
        anteriorint = cint;
        anteriorext = cext;
    }
}

void Donut::calculatePoints(float radiusin, float radiusout, int slices, int stacks)
{
    float raiointermedio = (radiusout-radiusin)/2;
    std::vector<float> cmdown = getPointsCircumference(0,-raiointermedio,0,raiointermedio+radiusin,slices);
    this->superficielateral = std::vector<std::vector<float>>();
    this->superficielateral.push_back(cmdown);
    float aumento = M_PI/stacks;
    float alfa = -M_PI_2;
    for(int i = 0; i < stacks+1; i++)
    {
        float cosalfa = std::cos(alfa);
        float yc = std::sin(alfa) * raiointermedio;
        float rint = radiusin + (raiointermedio - cosalfa * raiointermedio);
        float rext = radiusin + (raiointermedio + cosalfa * raiointermedio);
        std::vector<float> cint = getPointsCircumference(0,yc,0,rint,slices);
        std::vector<float> cext = getPointsCircumference(0,yc,0,rext,slices);
        this->superficielateral.push_back(cint);
        this->superficielateral.push_back(cext);
        alfa += aumento;
    }
}
