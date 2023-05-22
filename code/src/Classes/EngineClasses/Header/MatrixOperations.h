#ifndef PROJETOEXEC_MATRIXOPERATIONS_H
#define PROJETOEXEC_MATRIXOPERATIONS_H

#include <vector>

void buildRotMatrix(const float *x, const float *y, const float *z, float *m);
void cross(const float *a, const float *b, float *res);
void normalize(float *a);
void multMatrixVector(float m[4][4], const float *v, float *res);
void crossnormalize(float *a, float *b, float *res);
void normalizecrossnormalize(float *a, float *b, float *res);
void vetorPontos (float *p1, float *p2, float *res);
void multVetor (float *v1, float *v2, float *res);

void bezierMatrixPoints(const std::vector<std::vector<float>>& p0, const std::vector<std::vector<float>>& p1,const std::vector<std::vector<float>>& p2,const std::vector<std::vector<float>>& p3,float resx[4][4], float resy[4][4], float resz[4][4]);
void bezierMatrixM(float res[4][4]);
void bezierCalculate(float u[4],float v[4],float px[4][4],float py[4][4],float pz[4][4],float m[4][4],std::vector<float>* point);
void bezierGeraPatch(std::vector<std::vector<float>> *patch,float px[4][4],float py[4][4],float pz[4][4],float m[4][4],int lim);
#endif //PROJETOEXEC_MATRIXOPERATIONS_H
