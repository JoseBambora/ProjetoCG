
#ifndef PROJETOEXEC_BEZIER_H
#define PROJETOEXEC_BEZIER_H


#include <vector>
#include "Figure.h"
#include <GL/glew.h>

class Bezier : public Figure {
private:
    GLuint *allVertices;
    int sizeVertices;
    int lim;
    void getAllPoints(std::vector<std::vector<std::vector<float>>>* allPoints);
    void loadAllPoints(std::vector<std::vector<std::vector<float>>>* allPoints);
    void calculaPoints(std::vector<std::vector<int>>,std::vector<std::vector<float>>);
    void desenhaPatch(std::vector<std::vector<float>> patch);
    std::vector<std::vector<std::vector<float>>>* pointsCurve;
public:
    Bezier(const char *filename,int);
    Bezier();
    static Bezier* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Bezier* Read_File(std::ifstream file);
    std::string toString() override;
    void loadVBO() override;
    void drawFigure() override;
};


#endif
