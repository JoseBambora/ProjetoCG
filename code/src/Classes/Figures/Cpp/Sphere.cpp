#include <fstream>
#include "../Header/Sphere.h"
#include "GL/glut.h"

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

void Sphere::drawFigure(float x, float y, float z) {
    glutWireSphere(this->radius, this->slices, this->stacks);
}
Sphere::~Sphere() = default;
