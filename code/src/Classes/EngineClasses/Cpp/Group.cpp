//
// Created by josebambora on 18-02-2023.
//

#include "../Header/Group.h"
#include "../../Figures/Header/Figure.h"

Group::Group() {
    this->models = new std::list<Figure*>();
}

void Group::insertModel(const std::string& model) {
    this->models->push_back(Figure::ReadFile(model));
}

std::string Group::toString() {
    std::string res;
    res.append("Models:\n");
    for(Figure* elem : *this->models)
    {
        res.append(elem->toString());
        res.append("\n");
    }
    return res;
}

Group::~Group(){
    for (Figure* elem : *this->models)
        delete elem;
    delete this->models;
}

void Group::drawModels() {
    for (Figure* elem : *this->models)
        elem->drawFigure();
}
