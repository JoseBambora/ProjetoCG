#include <fstream>
#include "Sphere.h"

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
        printf("Invalid arguments for sphere\n");
    return s;
}

void Sphere::Write_File(const std::string &name) {
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &sphereCod,sizeof(sphereCod));
    myfile.write((char *) &radius,sizeof(radius));
    myfile.write((char *) &slices,sizeof(slices));
    myfile.write((char *) &stacks,sizeof(stacks));
    myfile.close();
}

void Sphere::Read_File(std::ifstream file) {
    float d9;
    int d10,d11;
    file.read((char *) &d9, sizeof(d9));
    file.read((char *) &d10, sizeof(d10));
    file.read((char *) &d11, sizeof(d11));
    this->radius = d9;
    this->slices = d10;
    this->stacks = d11;
}

std::string Sphere::toString() const {
    std::string res = "Sphere:\n";
    res.append("\tRadius:");
    res.append(std::to_string(this->radius));
    res.append("\n\tSlices:");
    res.append(std::to_string(this->slices));
    res.append("\n\tStacks:");
    res.append(std::to_string(this->stacks));
    return res;
}
