
#ifndef PROJETOEXEC_BEZIER_H
#define PROJETOEXEC_BEZIER_H


#include <vector>
#include "Figure.h"

class Bezier : public Figure {
private:
    int lim = 10;
    int curvasreais;
    void aplicaFormula(std::vector<float>p1,std::vector<float>p2,std::vector<float>p3,std::vector<float>p4,float t,std::vector<float> *res);
    void calculaPoints(std::vector<std::vector<int>>,std::vector<std::vector<float>>);
    //void calculaCurva(std::vector<float>,std::vector<float>,std::vector<float>,std::vector<float>);
    std::vector<std::vector<float>>* pointsCurve;
    std::vector<std::vector<float>>* pointsConnections;
    void connectPoints(std::vector<std::vector<float>>,std::vector<std::vector<float>>,bool);
    void reorganizaPontos();
    void calculapuv(float *u, float *v,std::vector<std::vector<float>>);
public:
    Bezier(const char *filename);
    static Bezier* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Bezier* Read_File(std::ifstream file);
    std::string toString() override;
    void loadVBO() override;
};


#endif
