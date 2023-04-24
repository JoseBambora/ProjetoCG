//
// Created by josebambora on 22-04-2023.
//

#include "../Header/MatrixOperations.h"
#include <cmath>
#include <vector>


void buildRotMatrix(const float *x, const float *y, const float *z, float *m) {
    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(const float *a, const float *b, float *res) {
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


float length(const float *v) {

    float res = std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    return res;

}

void multMatrixVector(float m[4][4], const float *v, float *res) {
    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
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

void bezierMatrixUV(float value,float res[4])
{
    res[0] = powf(value,3);
    res[1] = powf(value,2);
    res[2] = value;
    res[3] = 1;
}

void bezierMatrixPointsAux(std::vector<std::vector<float>> p0, std::vector<std::vector<float>> p1,std::vector<std::vector<float>> p2,std::vector<std::vector<float>> p3,float res[4][4],int index)
{
    res[0][0] = p0[0][index];
    res[0][1] = p0[1][index];
    res[0][2] = p0[2][index];
    res[0][3] = p0[3][index];

    res[1][0] = p1[0][index];
    res[1][1] = p1[1][index];
    res[1][2] = p1[2][index];
    res[1][3] = p1[3][index];

    res[2][0] = p2[0][index];
    res[2][1] = p2[1][index];
    res[2][2] = p2[2][index];
    res[2][3] = p2[3][index];

    res[3][0] = p3[0][index];
    res[3][1] = p3[1][index];
    res[3][2] = p3[2][index];
    res[3][3] = p3[3][index];
}

void bezierMatrixPoints(const std::vector<std::vector<float>>& p0, const std::vector<std::vector<float>>& p1,const std::vector<std::vector<float>>& p2,const std::vector<std::vector<float>>& p3,float resx[4][4], float resy[4][4], float resz[4][4])
{
    bezierMatrixPointsAux(p0,p1,p2,p3,resx,0);
    bezierMatrixPointsAux(p0,p1,p2,p3,resy,1);
    bezierMatrixPointsAux(p0,p1,p2,p3,resz,2);
}

void bezierMatrixM(float res[4][4])
{
    res[0][0] = -1;
    res[0][1] = 3;
    res[0][2] = -3;
    res[0][3] = 1;

    res[1][0] = 3;
    res[1][1] = -6;
    res[1][2] = 3;
    res[1][3] = 0;

    res[2][0] = -3;
    res[2][1] = 3;
    res[2][2] = 0;
    res[2][3] = 0;

    res[3][0] = 1;
    res[3][1] = 0;
    res[3][2] = 0;
    res[3][3] = 0;
}

float multiplicaVetores(float v1[4], float v2[4])
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2] + v1[3] * v2[3];
}