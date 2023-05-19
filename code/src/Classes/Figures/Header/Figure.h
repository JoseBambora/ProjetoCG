#ifndef PROJETOEXEC_FIGURE_H
#define PROJETOEXEC_FIGURE_H

#include <string>
#include <vector>

#include "../../EngineClasses/Header/Node.h"

class Figure : public Node{
public:
    unsigned int *vbos;
    unsigned int verticeCount;
    int texturaID;
    static const int codPlane = 0;
    static const int codBox = 2;
    static const int codCone = 3;
    static const int codSphere = 1;
    static const int codDonut = 4;
    static const int codCylinder = 5;
    static const int codBezierPatch = 6;
    std::vector<float>* ambient,*specular,*diffuse,*emissive;
    std::vector<float> normaisvetor;
    float shininnes;

    static Figure* Build(int argc, char** argv);
    static Figure* ReadFile(const std::string& name, std::vector<float>* diffusecolor, std::vector<float>*ambientcolor, std::vector<float>*specularcolor, std::vector<float>*emissivecolor, float shininessvalue,int texture);
    virtual std::string toString() override = 0;
    virtual ~Figure()=default;
    virtual void drawFigure();
    virtual void loadVBO();
    void load() override;
    void undo() override;
    void apply() override;
    void loadVertices(unsigned int*,int);
};


#endif
