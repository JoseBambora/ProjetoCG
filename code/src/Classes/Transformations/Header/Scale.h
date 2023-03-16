#ifndef PROJETOEXEC_SCALE_H
#define PROJETOEXEC_SCALE_H

#include "Transformation.h"
class Scale :public Transformation{
private:
    float x,y,z;
public:
    Scale(float,float,float);
    std::string toString() override ;
    void apply() override;
    ~Scale() override;

};


#endif
