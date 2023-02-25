#ifndef PROJETOEXEC_CONE_H
#define PROJETOEXEC_CONE_H

#include <string>
#include "Figure.h"


class Cone : public Figure{
public:
    float radius = 0;
    float height = 0;
    int slices = 0;
    int stacks = 0;
    static Cone* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Cone* Read_File(std::ifstream file);
    std::string toString() override;
    ~Cone() override;
    void drawFigure(float,float,float) override;
};

#endif