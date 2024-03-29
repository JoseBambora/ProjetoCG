//
// Created by josebambora on 04-03-2023.
//

#ifndef PROJETOEXEC_CYLINDER_H
#define PROJETOEXEC_CYLINDER_H


#include <string>
#include "Figure.h"

class Cylinder :public Figure{
private:
    void calculatePoints(float radius,float height, int slices);
public:
    std::vector<float> basecima;
    std::vector<float> basebaixo;
    std::vector<float> centrocima;
    static Cylinder* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Cylinder* Read_File(std::ifstream file);
    std::string toString() override;
    ~Cylinder() override;
    void loadVBO() override;
};


#endif //PROJETOEXEC_CYLINDER_H
