#ifndef PROJETOEXEC_BASICS_H
#define PROJETOEXEC_BASICS_H
std::vector<float> getPointsCircumference(float x, float y, float z, float radius, int slices);
void drawPyramid(std::vector<float> base, float x, float y, float z, bool direcao, float cred, float cgreen, float cblue);
void drawSide(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue);
#endif
