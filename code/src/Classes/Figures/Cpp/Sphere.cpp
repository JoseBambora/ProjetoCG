#include <cmath>
#include <fstream>
#include <vector>
#include "../Header/Sphere.h"
#include "../Header/Basics.h"
#include "GL/glut.h"
#include <cmath>

const int Figure::codSphere;

Sphere* Sphere::Build(int argc, char **argv) {
    auto *s = new Sphere();
    if(argc == 6)
    {
        s->radius = std::stof(argv[2]);
        s->slices = std::stoi(argv[3]);
        s->stacks = std::stoi(argv[4]);
        std::string name = argv[5];
        s->Write_File(name);
    }
    else
        printf("Invalid arguments for sphere. Creating a sphere with default values.\n");
    return s;
}

void Sphere::Write_File(const std::string &name) {
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &Figure::codSphere,sizeof(Figure::codSphere));
    myfile.write((char *) &radius,sizeof(radius));
    myfile.write((char *) &slices,sizeof(slices));
    myfile.write((char *) &stacks,sizeof(stacks));
    myfile.close();
}

Sphere* Sphere::Read_File(std::ifstream file) {
    auto *res = new Sphere();
    float d9;
    int d10,d11;
    file.read((char *) &d9, sizeof(d9));
    file.read((char *) &d10, sizeof(d10));
    file.read((char *) &d11, sizeof(d11));
    res->radius = d9;
    res->slices = d10;
    res->stacks = d11;
    return res;
}

std::string Sphere::toString()  {
    std::string res = "\tSphere:\n";
    res.append("\t\tRadius: ");
    res.append(std::to_string(this->radius));
    res.append("\n\t\tSlices: ");
    res.append(std::to_string(this->slices));
    res.append("\n\t\tStacks: ");
    res.append(std::to_string(this->stacks));
    return res;
}

void Sphere::drawFigure() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    // Circunferência do meio
    std::vector<float> base = getPointsCircumference(0,0,0,this->radius,this->slices);
    // Pensar em triangulas na circunferência (ver foto), sin e cos trabalham em radianos
    float aumento = M_PI_2/this->stacks;
    float alfa = aumento;
    std::vector<float> anteriorcima = base;
    std::vector<float> anteriorbaixo = base;
    for(int i = 0; i < this->stacks;i++)
    {
        float yc = std::sin(alfa) * this->radius;
        float r = std::cos(alfa) * this->radius;
        std::vector<float> ccima = getPointsCircumference(0,yc,0,r,this->slices);
        std::vector<float> cbaixo = getPointsCircumference(0,-yc,0,r,this->slices);
        drawSide(anteriorcima,ccima,1.0f,1.0f,1.0f);
        drawSide(cbaixo,anteriorbaixo,1.0f,1.0f,1.0f);
        alfa += aumento;
        anteriorbaixo = cbaixo;
        anteriorcima = ccima;
    }
    drawPyramid(anteriorcima,0,this->radius,0, true,1.0f,1.0f,1.0f);
    drawPyramid(anteriorbaixo,0,this->radius,0, false,1.0f,1.0f,1.0f);
}

Sphere::~Sphere() = default;
