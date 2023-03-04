//
// Created by josebambora on 04-03-2023.
//

#ifndef PROJETOEXEC_CYLINDER_H
#define PROJETOEXEC_CYLINDER_H


#include <string>
#include "Figure.h"

class Cylinder :public Figure{
public:
    float radius = 0;
    float height = 0;
    int slices = 0;
    static Cylinder* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Cylinder* Read_File(std::ifstream file);
    std::string toString() override;
    ~Cylinder() override;
    void drawFigure() override;
};


#endif //PROJETOEXEC_CYLINDER_H
