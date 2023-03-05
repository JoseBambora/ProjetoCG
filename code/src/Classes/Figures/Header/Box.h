#ifndef PROJETOEXEC_BOX_H
#define PROJETOEXEC_BOX_H

#include <vector>
#include "Figure.h"

class Box : public Figure{
private:
    void calculatePoints(float length, int dimension);
public:
    std::vector<std::vector<float>> points;
    static Box* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Box* Read_File(std::ifstream file);
    std::string toString() override;
    ~Box() override;
    void drawFigure() override;
};

#endif