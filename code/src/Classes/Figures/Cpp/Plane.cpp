#include <fstream>
#include "../Header/Plane.h"

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
    std::string res = "Plane:\n";
    res.append("\tLength: ");
    res.append(std::to_string(this->length));
    res.append("\n\tDimension: ");
    res.append(std::to_string(this->dimension));
    return res;
}

Plane::~Plane() = default;
