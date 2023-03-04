#include <string>
#include <fstream>
#include "../Header/Box.h"
#include "../Header/Plane.h"

const int Figure::codBox;

Box* Box::Build(int argc, char **argv) {
    Box *b = new Box();
    if(argc == 5)
    {
        b->length = std::stof(argv[2]);
        b->dimension = std::stof(argv[3]);
        std::string name = argv[4];
        b->Write_File(name);
    }
    else
        printf("Invalid arguments for box. Creating a box with default values.\n");
    return b;
}

void Box::Write_File(const std::string& name) {
    std::ofstream myfile;
    myfile.open (name, std::ios::binary | std::fstream::out);
    myfile.write((char *) &Figure::codBox,sizeof(Figure::codBox));
    myfile.write((char *) &length,sizeof(length));
    myfile.write((char *) &dimension,sizeof(dimension));
    myfile.close();
}

Box* Box::Read_File(std::ifstream file) {
    Box *res = new Box();
    float d1, d2;
    file.read((char *) &d1, sizeof(d1));
    file.read((char *) &d2, sizeof(d2));
    res->length = d1;
    res->dimension = d2;
    return res;
}

std::string Box::toString() {
    std::string res = "\tBox:\n";
    res.append("\t\tLength: ");
    res.append(std::to_string(this->length));
    res.append("\n\t\tDimension: ");
    res.append(std::to_string(this->dimension));
    return res;
}

void Box::drawFigure() {
    auto *pb = new Plane();
    pb->length = this->length;
    pb->dimension = this->dimension;
    float lb = this->length/2;
    float ls = (-1) * this->length/2;
    pb->drawFigure(lb,Plane::horizontal, false,Plane::negativo);
    pb->drawFigure(ls,Plane::horizontal, false,Plane::positivo);
    pb->drawFigure(lb,Plane::frontal,false,Plane::positivo);
    pb->drawFigure(ls,Plane::frontal,false,Plane::negativo);
    pb->drawFigure(lb,Plane::perfil,false,Plane::negativo);
    pb->drawFigure(ls,Plane::perfil,false,Plane::positivo);
    delete pb;
}

Box::~Box() = default;
