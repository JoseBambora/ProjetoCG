#ifndef PROJETOEXEC_BASICS_H
#define PROJETOEXEC_BASICS_H
std::vector<float> getPointsCircumference(float x, float y, float z, float radius, int slices);
void drawPyramid(std::vector<float> base, float x, float y, float z, bool direcao, float cred, float cgreen, float cblue);
void drawSideFora(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue);
void drawSideDentro(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue);
std::vector<std::vector<float>> readPoints(std::ifstream file);
void writePoints(std::vector<std::vector<float>> points, const std::string& name, int codigo);
#endif
