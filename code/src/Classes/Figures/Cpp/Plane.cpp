#include <fstream>
#include "../Header/Plane.h"
#include "GL/glut.h"
#include "../Header/Basics.h"

const int Figure::codPlane;

Plane* Plane::Build(int argc, char **argv) {
    auto *p = new Plane();
    if(argc == 5)
    {
        float length = std::stof(argv[2]);
        int dimension = std::stoi(argv[3]);
        p->calculatePoints(length,dimension,Plane::horizontal,Plane::negativo,0);
        std::string name = argv[4];
        p->Write_File(name);
    }
    else
        printf("Invalid arguments for plane. Creating a plane with default values.\n");
    return p;
}

void Plane::Write_File(const std::string& name) const {
    std::vector<std::vector<float>> write = std::vector<std::vector<float>>();
    write.push_back(this->points);
    writePoints(write, name, Figure::codPlane);
}

Plane* Plane::Read_File(std::ifstream file) {
    auto *res = new Plane();
    std::vector<std::vector<float>> read = readPoints(std::move(file));
    res->points = read[0];
    return res;
}

std::string Plane::toString() {
    std::string res = "Plane:";
    // res.append("\t\tNúmero de pontos totais:");
    // res.append(std::to_string(this->points.size()));
    return res;
}

std::vector<float> Plane::getPointsHorizontal(int d, float l, int direcao, int nq, float cxi, float czi, float ori) {
    std::vector<float> res = std::vector<float>();
    float fixo = 0.005f * d;
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
        if(czi - fixo <= (-1) * (l/2))
        {
            cxi += l/d;
            czi = l/2;
        }
    }
    return res;
}

std::vector<float> Plane::getPointsFrontal(int d, float l, int direcao, int nq, float cxi, float cyi, float ori) {
    std::vector<float> res = std::vector<float>();
    float fixo = 0.005f * d;
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
        if(cyi - fixo < (-1) * l/2)
        {
            cxi += l/d;
            cyi = l/2;
        }
    }
    return res;
}

std::vector<float> Plane::getPointsPerfil(int d, float l, int direcao, int nq, float czi, float cyi, float ori) {
    std::vector<float> res = std::vector<float>();
    float fixo = 0.005f * d;
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
        if(cyi - fixo < (-1) * l/2)
        {
            czi += l/d;
            cyi = l/2;
        }
    }
    return res;
}

void Plane::calculatePoints(float length, int dimension, int orientation, int direcao, float origin) {
    int nq = dimension * dimension;
    float cxi = (-1) * length/2;
    float cyi = length/2;
    switch(orientation)
    {
        case horizontal:
            points = this->getPointsHorizontal(dimension,length, direcao,nq,cxi,cyi,origin);
            break;
        case frontal:
            points = this->getPointsFrontal(dimension,length,direcao,nq,cxi,cyi,origin);
            break;
        case perfil:
            points = this->getPointsPerfil(dimension,length,direcao,nq,cxi,cyi,origin);
            break;
    }
}

std::vector<float> Plane::calculatePointsStatic(float length, int dimension,int orientation, int referencial, float origin) {
    auto *p = new Plane();
    p->calculatePoints(length,dimension,orientation,referencial,origin);
    std::vector<float> res = std::move(p->points);
    delete p;
    return res;
}

void Plane::loadVBO() {

    auto * allPoints = new std::vector<float>();
    float aux,aux2;
    int quadrado = 1;
    for (int i = 0; i < points.size(); i+=3)
    {
        switch(quadrado){
            case 1:
                aux = 0;
                aux2= 1;
                break;
            case 2:
                aux = 0;
                aux2= 0;
                break;
            case 3:
                aux = 1;
                aux2= 0;
                break;
            case 4:
                aux = 1;
                aux2 = 1;
                break;
            case 5:
                aux = 0;
                aux2= 1;
                break;
            case 6:
                aux = 1;
                aux2 = 0;
                break;
            default:
                break;
        }
        allPoints->push_back(points[i]);
        allPoints->push_back(points[i+1]);
        allPoints->push_back(points[i+2]);
        normaisvetor.push_back(0);
        normaisvetor.push_back(1);
        normaisvetor.push_back(0);
        texturasCoords.push_back(aux);
        texturasCoords.push_back(aux2);

        if(quadrado == 6){
            quadrado = 0;
        }
        quadrado+=1;
        //printf("%d",quadrado);
    }
    this->loadVertices(saveInfoPlacaGraficaIluminacaoTextura(allPoints,&normaisvetor,&texturasCoords),allPoints->size()/3);
    delete allPoints;
}

Plane::~Plane() = default;
