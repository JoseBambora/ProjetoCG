#ifndef PROJETOEXEC_CAMERA_H
#define PROJETOEXEC_CAMERA_H

#include <string>

class Camera{
public:
    static void processSpecialKeys(int key, int xx, int yy) ;
    static void processKeys(unsigned char key,int xx, int yy);
    Camera(float ,float,float,float,float,float,float,float,float,float,float,float);
    void atualiza(float *movimento);
    void atualizaLA(float *movimento);
    float posx;
    float posy;
    float posz;
    float lax;
    float lay;
    float laz;
    float upx;
    float upy;
    float upz;
    static float profov;
    static float pronear;
    static float profar;
    static double beta;
    static double alfa;
    static Camera *instance;
    std::string toString() const;
    void posicionaCamara(int w, int h) const;
    static void changeSize(int w, int h);
};

#endif