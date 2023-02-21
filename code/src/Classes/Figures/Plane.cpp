#include <fstream>
#include "Plane.h"

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
        printf("Invalid arguments for plane\n");
    return p;
}

void Plane::Write_File(const std::string& name) {
    std::ofstream myfile;
    myfile.open (name, std::ios::binary | std::fstream::out);
    myfile.write((char *) &this->planeCod,sizeof(this->planeCod));
    myfile.write((char *) &length,sizeof(length));
    myfile.write((char *) &dimension,sizeof(dimension));
    myfile.close();
}

void Plane::Read_File(std::ifstream file) {
    float d1, d2;
    file.read((char *) &d1, sizeof(d1));
    file.read((char *) &d2, sizeof(d2));
    this->length = d1;
    this->dimension = d2;
}

std::string Plane::toString() const {
    std::string res = "Plane:\n";
    res.append("\tLength:");
    res.append(std::to_string(this->length));
    res.append("\n\tDimension:");
    res.append(std::to_string(this->dimension));
    return res;
}
