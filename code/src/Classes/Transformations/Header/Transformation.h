#ifndef PROJETOEXEC_TRANSFORMATION_H
#define PROJETOEXEC_TRANSFORMATION_H

#include "../../EngineClasses/Header/Node.h"

class Transformation {
public:
    virtual std::string toString() = 0;
    void undo();
    virtual ~Transformation()=default;
    virtual void apply()  = 0;
};


#endif
