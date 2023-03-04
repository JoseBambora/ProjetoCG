#ifndef PROJETOEXEC_CAMERA_H
#define PROJETOEXEC_CAMERA_H

#include <string>

class Camera{
public:
    static void processSpecialKeys(int key, int xx, int yy) ;
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
    static double beta;
    static double alfa;
    std::string toString() const;
    void posicionaCamara(int w, int h) const;
};

#endif