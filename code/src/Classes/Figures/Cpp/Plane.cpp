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

void Plane::drawFigure(float referencial, int orientation, bool isPlane, int direcao) {
    float d = this->dimension;
    float l = this->length;
    int nq = (int) (d * d);
    float cxi = (-1) * l/2;
    float cyi = l/2;
    std::vector<float> points;
    switch(orientation)
    {
        case horizontal:
            points = this->getPointsHorizontal(direcao,nq,cxi,cyi,referencial);
            break;
        case frontal:
            points = this->getPointsFrontal(direcao,nq,cxi,cyi,referencial);
            break;
        case perfil:
            points = this->getPointsPerfil(direcao,nq,cxi,cyi,referencial);
            break;
    }
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    if(isPlane)
        glDisable(GL_CULL_FACE);
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < points.size(); i+=3)
        glVertex3f(points[i],points[i+1],points[i+2]);
    glEnd();
}

void Plane::drawFigure() {
    drawFigure(0,horizontal, true, positivo);
}

std::vector<float> Plane::getPointsHorizontal(int direcao, int nq, float cxi, float czi, float ori) {
    float d = this->dimension;
    float l = this->length;
    std::vector<float> res = std::vector<float>();
    for(int i = 0; i < nq; i++)
    {
        // Vertices de baixo x (ver desenho)
        float n1 = cxi + l / d;
        // Vertices de baixo z (ver desenho)
        float n2 = czi - l / d;
        switch (direcao)
        {
            case positivo:
                // Triangulo de baixo

                res.push_back(cxi);
                res.push_back(ori);
                res.push_back(czi);

                res.push_back(cxi);
                res.push_back(ori);
                res.push_back(n2);

                res.push_back(n1);
                res.push_back(ori);
                res.push_back(n2);

                // Triangulo de cima

                res.push_back(cxi);
                res.push_back(ori);
                res.push_back(czi);

                res.push_back(n1);
                res.push_back(ori);
                res.push_back(n2);

                res.push_back(n1);
                res.push_back(ori);
                res.push_back(czi);

                break;
            case negativo:
                // Triangulo de baixo

                res.push_back(cxi);
                res.push_back(ori);
                res.push_back(czi);

                res.push_back(n1);
                res.push_back(ori);
                res.push_back(n2);

                res.push_back(cxi);
                res.push_back(ori);
                res.push_back(n2);

                // Triangulo de cima

                res.push_back(cxi);
                res.push_back(ori);
                res.push_back(czi);

                res.push_back(n1);
                res.push_back(ori);
                res.push_back(czi);

                res.push_back(n1);
                res.push_back(ori);
                res.push_back(n2);


                break;
        }
        czi = n2;
        if(czi <= (-1) * l/2)
        {
            cxi += l/d;
            czi = l/2;
        }
    }
    return res;
}

std::vector<float> Plane::getPointsFrontal(int direcao, int nq, float cxi, float cyi, float ori) {
    float d = this->dimension;
    float l = this->length;
    std::vector<float> res = std::vector<float>();
    for(int i = 0; i < nq; i++)
    {
        // Vertices de baixo x (ver desenho)
        float n1 = cxi + l / d;
        // Vertices de baixo y (ver desenho)
        float n2 = cyi - l / d;
        switch (direcao)
        {
            case positivo:
                // Triangulo de baixo

                res.push_back(cxi);
                res.push_back(cyi);
                res.push_back(ori);

                res.push_back(cxi);
                res.push_back(n2);
                res.push_back(ori);

                res.push_back(n1);
                res.push_back(n2);
                res.push_back(ori);

                // Triangulo de cima

                res.push_back(cxi);
                res.push_back(cyi);
                res.push_back(ori);

                res.push_back(n1);
                res.push_back(n2);
                res.push_back(ori);

                res.push_back(n1);
                res.push_back(cyi);
                res.push_back(ori);

                break;
            case negativo:
                // Triangulo de baixo

                res.push_back(cxi);
                res.push_back(cyi);
                res.push_back(ori);

                res.push_back(n1);
                res.push_back(n2);
                res.push_back(ori);

                res.push_back(cxi);
                res.push_back(n2);
                res.push_back(ori);

                // Triangulo de cima

                res.push_back(cxi);
                res.push_back(cyi);
                res.push_back(ori);

                res.push_back(n1);
                res.push_back(cyi);
                res.push_back(ori);

                res.push_back(n1);
                res.push_back(n2);
                res.push_back(ori);
                break;
        }
        cyi = n2;
        if(cyi <= (-1) * l/2)
        {
            cxi += l/d;
            cyi = l/2;
        }
    }
    return res;
}

std::vector<float> Plane::getPointsPerfil(int direcao, int nq, float czi, float cyi, float ori) {
    float d = this->dimension;
    float l = this->length;
    std::vector<float> res = std::vector<float>();
    for(int i = 0; i < nq; i++)
    {
        // Vertices de baixo z (ver desenho)
        float n1 = czi + l / d;
        // Vertices de baixo y (ver desenho)
        float n2 = cyi - l / d;
        switch (direcao)
        {
            case positivo:
                // Triangulo de baixo

                res.push_back(ori);
                res.push_back(cyi);
                res.push_back(czi);

                res.push_back(ori);
                res.push_back(n2);
                res.push_back(czi);

                res.push_back(ori);
                res.push_back(n2);
                res.push_back(n1);

                // Triangulo de cima

                res.push_back(ori);
                res.push_back(cyi);
                res.push_back(czi);

                res.push_back(ori);
                res.push_back(n2);
                res.push_back(n1);

                res.push_back(ori);
                res.push_back(cyi);
                res.push_back(n1);

                break;
            case negativo:
                // Triangulo de baixo

                res.push_back(ori);
                res.push_back(cyi);
                res.push_back(czi);

                res.push_back(ori);
                res.push_back(n2);
                res.push_back(n1);

                res.push_back(ori);
                res.push_back(n2);
                res.push_back(czi);

                // Triangulo de cima

                res.push_back(ori);
                res.push_back(cyi);
                res.push_back(czi);

                res.push_back(ori);
                res.push_back(cyi);
                res.push_back(n1);

                res.push_back(ori);
                res.push_back(n2);
                res.push_back(n1);
                break;
        }
        cyi = n2;
        if(cyi <= (-1) * l/2)
        {
            czi += l/d;
            cyi = l/2;
        }
    }
    return res;
}

Plane::~Plane() = default;
