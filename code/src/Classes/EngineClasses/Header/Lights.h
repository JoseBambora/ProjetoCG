#ifndef PROJETOEXEC_LIGHTS_H
#define PROJETOEXEC_LIGHTS_H


#include <vector>
#include <GL/glut.h>

class Lights {
private:
    int type;
    GLenum luz;
    std::vector<float> *values;
public:
    static const int point = 0;
    static const int directional = 1;
    static const int spotlight = 2;
    Lights(int type, GLenum luz, std::vector<float> *values);
    void renderLight();
    void initLight();
    ~Lights();
};


#endif
