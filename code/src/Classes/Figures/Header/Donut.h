//
// Created by josebambora on 04-03-2023.
//

#ifndef PROJETOEXEC_DONUT_H
#define PROJETOEXEC_DONUT_H

#include "Figure.h"

class Donut : public Figure{
private:
    void calculatePoints(float radiusin,float radiusout, int slices, int stacks);
public:
    std::vector<std::vector<float>> superficielateral;
    static Donut* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Donut* Read_File(std::ifstream);
    std::string toString() override;
    ~Donut() override;
    void loadVBO() override;
};

#endif //PROJETOEXEC_DONUT_H
