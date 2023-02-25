#include <fstream>
#include "../Header/Plane.h"
#include "GL/glut.h"

const int Figure::codPlane;

Plane* Plane::Build(int argc, char **argv) {
    auto *p = new Plane();
    if(argc == 5)
    {
        p->length = std::stof(argv[2]);
        p->dimension = std::stof(argv[3]);
        std::string name = argv[4];
        p->Write_File(name);
    }
    else
        printf("Invalid arguments for plane. Creating a plane with default values.\n");
    return p;
}

void Plane::Write_File(const std::string& name) {
    std::ofstream myfile;
    myfile.open (name, std::ios::binary | std::fstream::out);
    myfile.write((char *) &Figure::codPlane,sizeof(Figure::codPlane));
    myfile.write((char *) &length,sizeof(length));
    myfile.write((char *) &dimension,sizeof(dimension));
    myfile.close();
}

Plane* Plane::Read_File(std::ifstream file) {
    auto *res = new Plane();
    float d1, d2;
    file.read((char *) &d1, sizeof(d1));
    file.read((char *) &d2, sizeof(d2));
    res->length = d1;
    res->dimension = d2;
    return res;
}

std::string Plane::toString() {
    std::string res = "\tPlane:\n";
    res.append("\t\tLength: ");
    res.append(std::to_string(this->length));
    res.append("\n\t\tDimension: ");
    res.append(std::to_string(this->dimension));
    return res;
}

void Plane::drawFigure(float ori, int orientation) {
    float d = this->dimension;
    float l = this->length;
    float nq = d * d;
    float cxi = (-1) * l/2;
    float cyi = l/2;
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    for(int i = 0; i < nq; i++)
    {
        float n1 = cxi+l/d;
        float n2 = cyi-l/d;
        switch(orientation)
        {
            case horizontal:
                glVertex3f(cxi,ori,cyi);
                glVertex3f(n1,ori,cyi);
                glVertex3f(n1,ori,cyi);
                glVertex3f(n1,ori,n2);
                glVertex3f(n1,ori,n2);
                glVertex3f(cxi,ori,cyi);
                glVertex3f(cxi,ori,cyi);
                glVertex3f(cxi,ori,n2);
                glVertex3f(cxi,ori,n2);
                glVertex3f(n1,ori,n2);
                glVertex3f(n1,ori,n2);
                glVertex3f(cxi,ori,cyi);
                break;
            case frontal:
                glVertex3f(cxi,cyi,ori);
                glVertex3f(n1,cyi,ori);
                glVertex3f(n1,cyi,ori);
                glVertex3f(n1,n2,ori);
                glVertex3f(n1,n2,ori);
                glVertex3f(cxi,cyi,ori);
                glVertex3f(cxi,cyi,ori);
                glVertex3f(cxi,n2,ori);
                glVertex3f(cxi,n2,ori);
                glVertex3f(n1,n2,ori);
                glVertex3f(n1,n2,ori);
                glVertex3f(cxi,cyi,ori);
                break;
            case perfil:
                glVertex3f(ori,cxi,cyi);
                glVertex3f(ori,n1,cyi);
                glVertex3f(ori,n1,cyi);
                glVertex3f(ori,n1,n2);
                glVertex3f(ori,n1,n2);
                glVertex3f(ori,cxi,cyi);
                glVertex3f(ori,cxi,cyi);
                glVertex3f(ori,cxi,n2);
                glVertex3f(ori,cxi,n2);
                glVertex3f(ori,n1,n2);
                glVertex3f(ori,n1,n2);
                glVertex3f(ori,cxi,cyi);
                break;
        }
        cyi = n2;
        if(cyi <= (-1) * l/2)
        {
            cxi += l/d;
            cyi = l/2;
        }
    }
    glEnd();
}

void Plane::drawFigure(float, float, float) {
    drawFigure(0,horizontal);
}

Plane::~Plane() = default;
