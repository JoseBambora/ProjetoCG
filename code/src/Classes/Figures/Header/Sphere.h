#ifndef PROJETOEXEC_SPHERE_H
#define PROJETOEXEC_SPHERE_H

#include <string>
#include "Figure.h"


class Sphere : public Figure{
private:
    void calculatePoints(float radius, int slices, int stacks);
public:
    std::vector<std::vector<float>> superficielateral;
    std::vector<float> verticesuperior;
    std::vector<float> verticeinferior;
    static Sphere* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Sphere* Read_File(std::ifstream);
    std::string toString() override;
    ~Sphere() override;
    void drawFigure() override;
};

#endif