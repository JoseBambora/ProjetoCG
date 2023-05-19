#include "../Header/Group.h"
#include "../../Figures/Header/Figure.h"
#include "../../Transformations/Header/Transform.h"
#include "../Header/ListTree.h"
#include <GL/glew.h>

Group::Group(ListTree * tree) {
    this->tree = tree;
}

std::string Group::toString() {
    return this->tree->toString();
}

Group::~Group(){
    delete this->tree;
}

void Group::load()
{
    this->tree->loadInfo();
}

void Group::execute() {
    this->tree->execute();
}