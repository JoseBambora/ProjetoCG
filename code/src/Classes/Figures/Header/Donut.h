//
// Created by josebambora on 04-03-2023.
//

#ifndef PROJETOEXEC_DONUT_H
#define PROJETOEXEC_DONUT_H

#include "Figure.h"

class Donut : public Figure{
public:
    float radiusin = 0;
    float radiusout = 0;
    int slices = 0;
    int stacks = 0;
    static Donut* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Donut* Read_File(std::ifstream);
    std::string toString() override;
    ~Donut() override;
    void drawFigure() override;
};

#endif //PROJETOEXEC_DONUT_H
