#ifndef PROJETOEXEC_SPHERE_H
#define PROJETOEXEC_SPHERE_H

#include <string>

class Sphere {
public:
    const int sphereCod = 1;
    float radius = 0;
    int slices = 0;
    int stacks = 0;
    static Sphere* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    void Read_File(std::ifstream);
    std::string toString() const;
};

#endif