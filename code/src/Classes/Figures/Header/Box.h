#ifndef PROJETOEXEC_BOX_H
#define PROJETOEXEC_BOX_H
#include "Figure.h"

class Box : public Figure{
public:
    float length = 0;
    float dimension = 0;
    static Box* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Box* Read_File(std::ifstream file);
    std::string toString() override;
    ~Box() override;
    void drawFigure() override;
};

#endif