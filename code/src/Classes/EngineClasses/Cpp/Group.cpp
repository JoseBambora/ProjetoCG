//
// Created by josebambora on 18-02-2023.
//

#include "../Header/Group.h"

Group::Group() {
    this->models = new std::list<std::string>();
}

void Group::insertModel(const std::string& model) {
    this->models->push_back(model);
}

std::string Group::toString() {
    std::string res;
    res.append("Models:\n");
    for(const std::string& elem : *this->models)
    {
        res.append("\t");
        res.append(elem);
        res.append("\n");
    }
    return res;
}

Group::~Group(){
    delete this->models;
}
