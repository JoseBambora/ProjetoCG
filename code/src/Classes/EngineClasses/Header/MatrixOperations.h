#ifndef PROJETOEXEC_MATRIXOPERATIONS_H
#define PROJETOEXEC_MATRIXOPERATIONS_H

#include <vector>

void buildRotMatrix(const float *x, const float *y, const float *z, float *m);
void cross(const float *a, const float *b, float *res);
void normalize(float *a);
float length(const float *v);
void multMatrixVector(float m[4][4], const float *v, float *res);
void crossnormalize(float *a, float *b, float *res);
void multiplicaVetorValor(std::vector<float> vetor, float valor, std::vector<float> * res);
void somaVetores(std::vector<float> p1, std::vector<float> p2, std::vector<float> p3, std::vector<float> p4, std::vector<float> * res);

void bezierMatrixUV(float value,float res[4]);
void bezierMatrixPoints(const std::vector<std::vector<float>>& p0, const std::vector<std::vector<float>>& p1,const std::vector<std::vector<float>>& p2,const std::vector<std::vector<float>>& p3,float resx[4][4], float resy[4][4], float resz[4][4]);
void bezierMatrixM(float res[4][4]);
float multiplicaVetores(float v1[4], float v2[4]);
#endif //PROJETOEXEC_MATRIXOPERATIONS_H
