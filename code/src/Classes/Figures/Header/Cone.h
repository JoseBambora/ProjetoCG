#ifndef PROJETOEXEC_CONE_H
#define PROJETOEXEC_CONE_H

#include <string>
#include <vector>
#include "Figure.h"


class Cone : public Figure{
private:
    void calculatePoints(float radius, float height, int slices, int stacks);
public:
    std::vector<float> base;
    std::vector<std::vector<float>> superficielateral;
    std::vector<float> coordsTopo;
    static Cone* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Cone* Read_File(std::ifstream file);
    std::string toString() override;
    ~Cone() override;
    void drawFigure() override;
};

#endif