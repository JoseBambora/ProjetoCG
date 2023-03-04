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
    // Pensar em triangulas na circunferência (ver foto), sin e cos trabalham em radianos
    float aumento = M_PI/this->stacks;
    float alfa = -M_PI_2;
    std::vector<float> anterior;
    std::vector<float> primeira;
    for(int i = 0; i < this->stacks;i++)
    {
        float yc = std::sin(alfa) * this->radius;
        float r = std::cos(alfa) * this->radius;
        std::vector<float> c = getPointsCircumference(0,yc,0,r,this->slices);
        if(i > 0)
            drawSide(anterior,c,1.0f,1.0f,1.0f);
        else
            primeira = c;
        alfa += aumento;
        anterior = c;
    }
    drawPyramid(anterior,0,this->radius,0, true,1.0f,1.0f,1.0f);
    drawPyramid(primeira,0,-this->radius,0, false,1.0f,1.0f,1.0f);
}

Sphere::~Sphere() = default;
