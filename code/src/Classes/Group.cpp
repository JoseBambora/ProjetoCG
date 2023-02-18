//
// Created by josebambora on 18-02-2023.
//

#include "Group.h"

Group::Group() {
    this->models = std::list<std::string>();
}

void Group::insertModel(std::string model) {
    this->models.push_back(model);
}

std::string Group::toString() {
    std::string res;
    res.append("Models:\n");
    for(std::string elem : this->models)
    {
        res.append("\t");
        res.append(elem);
        res.append("\n");
    }
    return res;
}
