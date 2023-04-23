#ifndef PROJETOEXEC_MATRIXOPERATIONS_H
#define PROJETOEXEC_MATRIXOPERATIONS_H

#include <vector>

void buildRotMatrix(float *x, float *y, float *z, float *m);
void cross(float *a, float *b, float *res);
void normalize(float *a);
float length(float *v);
void multMatrixVector(float m[4][4], float *v, float *res);
void crossnormalize(float *a, float *b, float *res);
void multiplicaVetorValor(std::vector<float> vetor, float valor, std::vector<float> * res);
void somaVetores(std::vector<float> p1, std::vector<float> p2, std::vector<float> p3, std::vector<float> p4, std::vector<float> * res);
#endif //PROJETOEXEC_MATRIXOPERATIONS_H
