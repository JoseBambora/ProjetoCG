#ifndef PROJETOEXEC_TRANSFORM_H
#define PROJETOEXEC_TRANSFORM_H
#include "../../EngineClasses/Header/Node.h"
#include <vector>
class Transformation;
class Transform :public Node{
private:
    std::vector<Transformation*> *lista;
public:
    Transform();
    std::string toString() override;
    void undo() override;
    void apply() override;
    void load() override;
    void addTranformation(Transformation* t);
    ~Transform();

};


#endif //PROJETOEXEC_TRANSFORM_H
