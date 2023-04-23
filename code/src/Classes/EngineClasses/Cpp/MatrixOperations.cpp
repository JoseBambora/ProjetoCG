//
// Created by josebambora on 22-04-2023.
//

#include "../Header/MatrixOperations.h"
#include <cmath>
#include <vector>


void buildRotMatrix(float *x, float *y, float *z, float *m) {
    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float *a, float *b, float *res) {
    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}


void normalize(float *a) {

    float l = std::sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}


float length(float *v) {

    float res = std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    return res;

}

void multMatrixVector(float m[4][4], float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }
}

void multMatrix(float m[4][4][3], float m2[4][4], float *res) {
    for (int j = 0; j < 4; ++j)
    {
        for (int k = 0; k < 4; ++k)
        {
            float *vetor = m[j][k];
            float res[4];
            multMatrixVector(m2,vetor,res);
        }
    }
}

void crossnormalize(float *a, float *b, float *res)
{
    cross(a,b,res);
    normalize(res);
}

void multiplicaVetorValor(std::vector<float> vetor, float valor, std::vector<float> * res)
{
    res->push_back(valor * vetor.at(0));
    res->push_back(valor * vetor.at(1));
    res->push_back(valor * vetor.at(2));
}

void somaVetores(std::vector<float> p1, std::vector<float> p2, std::vector<float> p3, std::vector<float> p4, std::vector<float> * res)
{
    for(int i = 0; i < 3; i++)
    {
        res->push_back(p1[i] + p2[i] + p3[i] + p4[i]);
    }
}
