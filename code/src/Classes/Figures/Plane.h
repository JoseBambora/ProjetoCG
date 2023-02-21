#ifndef PROJETOEXEC_PLANE_H
#define PROJETOEXEC_PLANE_H

#include <string>

class Plane {
public:
    const int planeCod = 0;
    float length = 0;
    float dimension = 0;
    static Plane* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    void Read_File(std::ifstream file);
    std::string toString() const;
};

#endif