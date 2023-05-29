#ifndef PROJETOEXEC_BASICS_H
#define PROJETOEXEC_BASICS_H
std::vector<float> getPointsCircumference(float x, float y, float z, float radius, int slices);

std::vector<std::vector<float>> readPoints(std::ifstream file);
void writePoints(std::vector<std::vector<float>> points, const std::string& name, int codigo);

void connectPyramidTexturasCirculo(std::vector<float> *allPoints,std::vector<float>*normais,std::vector<float>*texturas,std::vector<float> base, float x, float y, float z, bool direcao, bool plana,float cx,float cy,float cz,float txcentro, float tycentro, float traio);
void connectPyramidTexturasLinhas(std::vector<float> *allPoints,std::vector<float>*normais,std::vector<float>*texturas,std::vector<float> base, float x, float y, float z, bool direcao, bool plana,float cx,float cy,float cz,float tybase, float tycentro);

void connectSideForaTexturas(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz, std::vector<float> *texturas,float tybaixo, float tycima);
void connectSideForaV2Texturas(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz,float cx1,float cy1,float cz1,std::vector<float> *texturas,float tybaixo, float tycima);
void connectSideForaInversoTexturas(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz, std::vector<float> *texturas,float tybaixo, float tycima);
void connectSideDentroTexturas(std::vector<float>* allPoints,std::vector<float> cbaixo,std::vector<float> ccima,std::vector<float>*normais,float cx, float cy,float cz, std::vector<float> *texturas,float tybaixo, float tycima);

unsigned int* saveInfoPlacaGraficaIluminacaoTextura(std::vector<float> *allPoints, std::vector<float> *normais,std::vector<float> *texturas );

void drawVBOIluminacaoTextura(unsigned int *vbos, unsigned int verticeCount);

void calculaNormalBases(bool cima, std::vector<float> *res);

void materialLighting(std::vector<float> *ambient, std::vector<float> *diffuse, std::vector<float> *specular, std::vector<float> *emission,float shininess);
int loadTexture(std::string s);
#endif
