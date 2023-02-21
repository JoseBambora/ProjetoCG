#ifndef PROJETOEXEC_CONE_H
#define PROJETOEXEC_CONE_H

#include <string>

class Cone {
public:
    const int coneCod = 3;
    float radius = 0;
    float height = 0;
    int slices = 0;
    int stacks = 0;
    static Cone* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    void Read_File(std::ifstream file);
    std::string toString() const;
};

#endif