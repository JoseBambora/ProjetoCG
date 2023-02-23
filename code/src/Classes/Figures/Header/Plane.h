#ifndef PROJETOEXEC_PLANE_H
#define PROJETOEXEC_PLANE_H
#include <string>
#include "Figure.h"

class Plane : public Figure{
public:
    float length = 0;
    float dimension = 0;
    static Plane* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Plane* Read_File(std::ifstream file);
    std::string toString() override;
    ~Plane() override;
};

#endif