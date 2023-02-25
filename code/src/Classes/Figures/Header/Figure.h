#ifndef PROJETOEXEC_FIGURE_H
#define PROJETOEXEC_FIGURE_H

#include <string>

class Figure {
public:
    static const int codPlane = 0;
    static const int codBox = 2;
    static const int codCone = 3;
    static const int codSphere = 1;
    static Figure* Build(int argc, char** argv);
    static Figure* ReadFile(const std::string& name);
    virtual std::string toString() = 0;
    virtual ~Figure()=default;
    virtual void drawFigure(float,float,float);
};


#endif
