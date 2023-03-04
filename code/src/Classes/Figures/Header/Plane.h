#ifndef PROJETOEXEC_PLANE_H
#define PROJETOEXEC_PLANE_H
#include <string>
#include <vector>
#include "Figure.h"

class Plane : public Figure{
private:
    std::vector<float> getPointsHorizontal(int direcao, int nq, float cxi, float cyi, float ori);
    std::vector<float> getPointsFrontal(int direcao, int nq, float cxi, float cyi, float ori);
    std::vector<float> getPointsPerfil(int direcao, int nq, float cxi, float cyi, float ori);
public:
    static const int frontal = 1;
    static const int horizontal = 2;
    static const int perfil = 3;
    static const int positivo = 0;
    static const int negativo = 1;
    float length = 0;
    float dimension = 0;
    static Plane* Build(int argc, char** argv);
    void Write_File(const std::string& name);
    static Plane* Read_File(std::ifstream file);
    std::string toString() override;
    ~Plane() override;
    void drawFigure() override;
    void drawFigure(float ori, int orientation, bool isPlane, int direcao);
};

#endif