//
// Created by josebambora on 22-04-2023.
//

#include "../Header/MatrixOperations.h"
#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <vector>
#include <iostream>


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

void normalizecrossnormalize(float *a, float *b, float *res)
{
    normalize(a);
    normalize(b);
    crossnormalize(a,b,res);
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

void bezierMatrixUVDerivada(float value,float res[4])
{
    res[0] = 3 * powf(value,2);
    res[1] = 2 * value;
    res[2] = 1;
    res[3] = 0;
}

void bezierMatrixUVAll(float value,float valor[4], float derivada[4])
{
    bezierMatrixUV(value,valor);
    bezierMatrixUVDerivada(value,derivada);
}



void bezierCalculate(float u[4],float v[4],float px[4][4],float py[4][4],float pz[4][4],float m[4][4],std::vector<float>* point) {
    float res1[4];
    float resx1[4], resy1[4], resz1[4];
    float resx2[4], resy2[4], resz2[4];

    multMatrixVector(m,v,res1);

    multMatrixVector(px,res1,resx1);
    multMatrixVector(py,res1,resy1);
    multMatrixVector(pz,res1,resz1);

    multMatrixVector(m,resx1,resx2);
    multMatrixVector(m,resy1,resy2);
    multMatrixVector(m,resz1,resz2);

    float resx3 = multiplicaVetores(u,resx2);
    float resy3 = multiplicaVetores(u,resy2);
    float resz3 = multiplicaVetores(u,resz2);

    point->push_back(resx3);
    point->push_back(resy3);
    point->push_back(resz3);
}

/*
 * separar em x y z
 * seila = M * V (4x4 * 4x1 = 4x1)
 * seila2x = px * seila (4x4 * 4x1 = 4x1)
 * seila2y = py * seila (4x4 * 4x1 = 4x1)
 * seila2z = pz * seila (4x4 * 4x1 = 4x1)
 * seila2x = M * seila2x (4x4 * 4x1 = 4x1)
 * seila2y = M * seila2y (4x4 * 4x1 = 4x1)
 * seila2z = M * seila2z (4x4 * 4x1 = 4x1)
 * resx = U * seila2x = (1x4 * 4x1 = 1)
 * resy = U * seila2y = (1x4 * 4x1 = 1)
 * resz = U * seila2z = (1x4 * 4x1 = 1)
 * res = (resx, resy, resz)
 * this->pointsConnections->push_back(res)
 * Pescorrer os pontos e desenhar strips
 * this->pointsConnections = new std::vector<std::vector<float>>();
 */
void bezierGeraPatch(std::vector<std::vector<float>> *patch,float px[4][4],float py[4][4],float pz[4][4],float m[4][4],int lim)
{
    int iteracoes = lim+1;
    float uvalor = 0;
    float u[4], uDerivada[4];
    auto *normal = new float[3];
    float aumento = (float) 1 / lim;
    for(int primeiras = 0; primeiras < iteracoes; primeiras++)
    {
        float vvalor = 0;
        float v[4], vDerivada[4];
        bezierMatrixUV(uvalor,u);
        bezierMatrixUVDerivada(uvalor,uDerivada);
        for(int segundas = 0; segundas < iteracoes; segundas++)
        {
            std::vector<float> point,derivu,derivv;
            bezierMatrixUV(vvalor,v);
            bezierMatrixUVDerivada(vvalor,vDerivada);

            bezierCalculate(u,v,px,py,pz,m,&point);
            bezierCalculate(uDerivada,v,px,py,pz,m,&derivu);
            bezierCalculate(u,vDerivada,px,py,pz,m,&derivv);

            normalizecrossnormalize(derivv.data(),derivu.data(),normal);

            // to do : guardar aqui em point os valores da normal.
            // Depois no render ir buscar as componentes [4] [5] e [6]
            // x y z, nx, ny, nz
            point.push_back(normal[0]);
            point.push_back(normal[1]);
            point.push_back(normal[2]);

            patch->push_back(point);
            vvalor += aumento;
        }
        uvalor += aumento;
    }
    delete []normal;
}