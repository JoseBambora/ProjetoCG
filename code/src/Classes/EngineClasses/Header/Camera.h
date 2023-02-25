#ifndef PROJETOEXEC_CAMERA_H
#define PROJETOEXEC_CAMERA_H

#include <string>

class Camera{
public:
    Camera(float ,float,float,float,float,float,float,float,float,float,float,float);
    float posx;
    float posy;
    float posz;
    float lax;
    float lay;
    float laz;
    float upx;
    float upy;
    float upz;
    float profov;
    float pronear;
    float profar;
    std::string toString() const;
    void posicionaCamara(int w, int h) const;
};

#endif