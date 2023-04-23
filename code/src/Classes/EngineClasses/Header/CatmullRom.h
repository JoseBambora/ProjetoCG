#ifndef PROJETOEXEC_CATMULLROM_H
#define PROJETOEXEC_CATMULLROM_H

#include <vector>
#include "../../Transformations/Header/Transformation.h"

class CatmullRom : public Transformation{
private:
    float aux;
    int POINT_COUNT;
    // float p[POINT_COUNT][3] = {{-1,-1,0},{-1,1,0},{1,1,0},{0,0,0},{1,-1,0}};
    float **p;
    float time;
    bool align;
    float Y[3] = {0,-1,0};
    void renderCatmullRomCurve();
    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
    void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);
    void applyTransformations();
public:
    explicit CatmullRom(std::vector<float>*,float,bool);
    void apply() override;
    std::string toString() override;
    ~CatmullRom();
};
#endif
