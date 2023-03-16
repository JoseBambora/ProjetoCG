#ifndef PROJETOEXEC_ROTATE_H
#define PROJETOEXEC_ROTATE_H

#include "Transformation.h"

class Rotate : public Transformation {
private:
    float angle,x,y,z;
public:
    Rotate(float,float,float,float);
    std::string toString() override;
    void apply() override;
    ~Rotate() override;
};

#endif

