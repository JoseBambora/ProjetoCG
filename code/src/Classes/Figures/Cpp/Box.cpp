#include <string>
#include <fstream>
#include "../Header/Box.h"
#include "../Header/Plane.h"
#include "../Header/Basics.h"

const int Figure::codBox;

Box* Box::Build(int argc, char **argv) {
    Box *b = new Box();
    if(argc == 5)
    {
        float length = std::stof(argv[2]);
        float dimension = std::stof(argv[3]);
        std::string name = argv[4];
        b->calculatePoints(length,dimension);
        b->Write_File(name);
    }
    else
        printf("Invalid arguments for box. Creating a box with default values.\n");
    return b;
}

void Box::Write_File(const std::string& name) {
    writePoints(this->points, name, Figure::codBox);
}

Box* Box::Read_File(std::ifstream file) {
    Box *res = new Box();
    res->points = readPoints(std::move(file));
    return res;
}

std::string Box::toString() {
    std::string res = "Box";
    return res;
}

void Box::calculatePoints(float length, int dimension) {
    auto *pb = new Plane();
    float lb = length/2;
    float ls = (-1) * length/2;
    this->points = std::vector<std::vector<float>>();
    std::vector<std::vector<float>> aux;
    points.push_back(Plane::calculatePointsStatic(length,dimension,Plane::horizontal,Plane::negativo,lb));
    points.push_back(Plane::calculatePointsStatic(length,dimension,Plane::horizontal,Plane::positivo,ls));
    points.push_back(Plane::calculatePointsStatic(length,dimension,Plane::frontal,Plane::positivo,lb));
    points.push_back(Plane::calculatePointsStatic(length,dimension,Plane::frontal,Plane::negativo,ls));
    points.push_back(Plane::calculatePointsStatic(length,dimension,Plane::perfil,Plane::negativo,lb));
    points.push_back(Plane::calculatePointsStatic(length,dimension,Plane::perfil,Plane::positivo,ls));
    delete pb;
}

void Box::loadVBO() {
    auto * allPoints = new std::vector<float>();
    float nx = 0, ny = 1,nz = 0;
    for(int j = 0; j < points.size(); j++)
    {
        std::vector<float> drawPoints = this->points[j];
        for (int i = 0; i < drawPoints.size(); i+=3)
        {
            allPoints->push_back(drawPoints[i]);
            allPoints->push_back(drawPoints[i+1]);
            allPoints->push_back(drawPoints[i+2]);

            normaisvetor.push_back(nx);
            normaisvetor.push_back(ny);
            normaisvetor.push_back(nz);
        }
        // Horizontal
        if (nx == 0 && ny == 1 && nz == 0)
            ny = -1;
        else if (nx == 0 && ny == -1 && nz == 0)
        {
            ny = 0;
            nz = 1;
        }
        // Frontal
        else if (nx == 0 && ny == 0 && nz == 1)
            nz = -1;
        else if (nx == 0 && ny == 0 && nz == -1)
        {
            nx = 1;
            nz = 0;
        }
        // Perfil
        else if (nx == 1 && ny == 0 && nz == 0)
            nx = -1;
    }
    this->loadVertices(saveInfoPlacaGraficaIluminacao(allPoints,&normaisvetor),allPoints->size()/3);
    delete allPoints;

}

Box::~Box() = default;
