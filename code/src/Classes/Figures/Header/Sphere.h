#ifndef PROJETOEXEC_SPHERE_H
#define PROJETOEXEC_SPHERE_H

#include <string>
#include "Figure.h"


class Sphere : public Figure{
public:
    float radius = 0;
    int slices = 0;
    int stacks = 0;
    static Sphere* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Sphere* Read_File(std::ifstream);
    std::string toString() override;
    ~Sphere() override;
};

#endif