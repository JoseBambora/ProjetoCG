#ifndef PROJETOEXEC_TRANSLATE_H
#define PROJETOEXEC_TRANSLATE_H

#include "Transformation.h"

class Translate :public Transformation{
private:
    float x,y,z;
public:
    Translate(float,float,float);
    std::string toString() override ;
    void apply() override;
    ~Translate() override;
};


#endif
