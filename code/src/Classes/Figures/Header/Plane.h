#ifndef PROJETOEXEC_PLANE_H
#define PROJETOEXEC_PLANE_H
#include <string>
#include <vector>
#include "Figure.h"

class Plane : public Figure{
private:
    std::vector<float> getPointsHorizontal(int d, float l, int direcao, int nq, float cxi, float cyi, float ori);
    std::vector<float> getPointsFrontal(int d, float l, int direcao, int nq, float cxi, float cyi, float ori);
    std::vector<float> getPointsPerfil(int d, float l, int direcao, int nq, float cxi, float cyi, float ori);
    void calculatePoints(float length, int dimension, int orientation, int referencial, float origin);
public:
    static const int frontal = 1;
    static const int horizontal = 2;
    static const int perfil = 3;
    static const int positivo = 0;
    static const int negativo = 1;
    std::vector<float> points;
    static Plane* Build(int argc, char** argv);
    void Write_File(const std::string& name) const;
    static Plane* Read_File(std::ifstream file);
    std::string toString() override;
    ~Plane() override;
    void drawFigure() override;
    static std::vector<float> calculatePointsStatic(float length, int dimension, int orientation, int referencial, float origin);
};

#endif