//
// Created by josebambora on 16-03-2023.
//

#ifndef PROJETOEXEC_DEFAULTNODE_H
#define PROJETOEXEC_DEFAULTNODE_H

#include <string>
#include "../../EngineClasses/Header/Node.h"

class DefaultNode : public Node{
public:
    void undo() override;
    void apply() override;
    std::string toString() override;
};


#endif //PROJETOEXEC_DEFAULTNODE_H
