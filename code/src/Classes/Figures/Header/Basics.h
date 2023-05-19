#ifndef PROJETOEXEC_BASICS_H
#define PROJETOEXEC_BASICS_H
std::vector<float> getPointsCircumference(float x, float y, float z, float radius, int slices);
void drawPyramid(std::vector<float> base, float x, float y, float z, bool direcao, float cred, float cgreen, float cblue);
void drawSideFora(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue);
void drawSideDentro(std::vector<float> cbaixo,std::vector<float> ccima, float cred, float cgreen, float cblue);
std::vector<std::vector<float>> readPoints(std::ifstream file);
void writePoints(std::vector<std::vector<float>> points, const std::string& name, int codigo);
void connectPyramid(std::vector<float> *allPoints,std::vector<float> base, float x, float y, float z, bool direcao, std::vector<float>*normais,bool plana,float cx,float cy,float cz);
void connectSideDentro(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz);
void connectSideFora(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz);
void connectSideForaV2(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz,float cx1,float cy1,float cz1);
unsigned int* saveInfoPlacaGrafica(std::vector<float>* allPoints);
unsigned int* saveInfoPlacaGraficaIluminacao(std::vector<float> *allPoints, std::vector<float> *normais);
unsigned int* saveInfoPlacaGraficaIluminacaoTextura(std::vector<float> *allPoints, std::vector<float> *normais,std::vector<float> *texturas );
void drawVBO(unsigned int vertices, unsigned int verticeCount, float red, float green, float blue);
void drawVBOIluminacao(unsigned int *vbos, unsigned int verticeCount);
void drawVBOIluminacaoTextura(unsigned int *vbos, unsigned int verticeCount);
void materialLighting(std::vector<float> *ambient, std::vector<float> *diffuse, std::vector<float> *specular, std::vector<float> *emission,float shininess);
void calculaNormaisCircunferencia(std::vector<float>* allPoints, float x, float y, float z,std::vector<float>* normais);
int loadTexture(std::string s);
void calculaNormalBases(bool cima, std::vector<float> *res);
#endif
