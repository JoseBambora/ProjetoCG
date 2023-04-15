#ifndef PROJETOEXEC_FIGURE_H
#define PROJETOEXEC_FIGURE_H

#include <string>

#include "../../EngineClasses/Header/Node.h"

class Figure : public Node{
public:
    unsigned int vertices;
    unsigned int verticeCount;
    static const int codPlane = 0;
    static const int codBox = 2;
    static const int codCone = 3;
    static const int codSphere = 1;
    static const int codDonut = 4;
    static const int codCylinder = 5;
    static Figure* Build(int argc, char** argv);
    static Figure* ReadFile(const std::string& name);
    virtual std::string toString() override = 0;
    virtual ~Figure()=default;
    void drawFigure();
    virtual void loadVBO();
    void load() override;
    void undo() override;
    void apply() override;
    void loadVertices(unsigned int*);
};


#endif
