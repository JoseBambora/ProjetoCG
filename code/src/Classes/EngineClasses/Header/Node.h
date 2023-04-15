#ifndef PROJETOEXEC_NODE_H
#define PROJETOEXEC_NODE_H


#include <string>

class Node {
public:
    virtual void undo() = 0;
    virtual void apply() = 0;
    virtual void load() = 0;
    virtual std::string toString() = 0;
};


#endif //PROJETOEXEC_NODE_H
