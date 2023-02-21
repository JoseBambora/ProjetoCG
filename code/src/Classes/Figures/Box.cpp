#include <string>
#include <fstream>
#include "Box.h"

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
        printf("Invalid arguments for box\n");
    return b;
}

void Box::Write_File(const std::string& name) {
    std::ofstream myfile;
    myfile.open (name, std::ios::binary | std::fstream::out);
    myfile.write((char *) &this->boxCod,sizeof(this->boxCod));
    myfile.write((char *) &length,sizeof(length));
    myfile.write((char *) &dimension,sizeof(dimension));
    myfile.close();
}

void Box::Read_File(std::ifstream file) {
    float d1, d2;
    file.read((char *) &d1, sizeof(d1));
    file.read((char *) &d2, sizeof(d2));
    this->length = d1;
    this->dimension = d2;
}

std::string Box::toString() const {
    std::string res = "Box:\n";
    res.append("\tLength:");
    res.append(std::to_string(this->length));
    res.append("\n\tDimension:");
    res.append(std::to_string(this->dimension));
    return res;
}
