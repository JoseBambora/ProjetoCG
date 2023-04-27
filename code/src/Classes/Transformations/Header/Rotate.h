#ifndef PROJETOEXEC_ROTATE_H
#define PROJETOEXEC_ROTATE_H

#include "Transformation.h"

class Rotate : public Transformation {
private:
    float numero,x,y,z;
    bool angle;
    float occor;
    int last_time;
public:
    Rotate(float,float,float,float,bool);
    std::string toString() override;
    void apply() override;
    ~Rotate() override;
};

#endif

