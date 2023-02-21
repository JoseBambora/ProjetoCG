#include <fstream>
#include "Cone.h"

Cone* Cone::Build(int argc, char **argv) {
    Cone *c = new Cone();
    if(argc == 7)
    {
        c->radius = std::stof(argv[2]);
        c->height = std::stof(argv[3]);
        c->slices = std::stoi(argv[4]);
        c->stacks = std::stoi(argv[5]);
        std::string name = argv[6];
        c->Write_File(name);
    }
    else
        printf("Invalid arguments for cone\n");
    return c;
}

void Cone::Write_File(const std::string &name) {
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &coneCod,sizeof(coneCod));
    myfile.write((char *) &radius,sizeof(radius));
    myfile.write((char *) &height,sizeof(height));
    myfile.write((char *) &slices,sizeof(slices));
    myfile.write((char *) &stacks,sizeof(stacks));
    myfile.close();
}

void Cone::Read_File(std::ifstream file) {
    float d3,d4;
    int d5,d6;
    file.read((char *) &d3, sizeof(d3));
    file.read((char *) &d4, sizeof(d4));
    file.read((char *) &d5, sizeof(d5));
    file.read((char *) &d6, sizeof(d6));
    this->radius = d3;
    this->height = d4;
    this->slices = d5;
    this->stacks = d6;
}

std::string Cone::toString() const {
    std::string res = "Cone:\n";
    res.append("\tRadius:");
    res.append(std::to_string(this->radius));
    res.append("\n\tHeight:");
    res.append(std::to_string(this->height));
    res.append("\n\tSlices:");
    res.append(std::to_string(this->slices));
    res.append("\n\tStacks:");
    res.append(std::to_string(this->stacks));
    return res;
}
