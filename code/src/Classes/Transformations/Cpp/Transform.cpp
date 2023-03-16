#include "../Header/Transform.h"
#include "../Header/Transformation.h"

Transform::Transform() {
    this->lista = new std::vector<Transformation*>();
}

Transform::~Transform() {
    for(Transformation *t : *this->lista)
    {
        delete t;
    }
    delete this->lista;
}

void Transform::undo() {
    for(Transformation *t : *this->lista)
    {
        t->undo();
    }
}

void Transform::apply() {
    for(Transformation *t : *this->lista)
    {
        t->apply();
    }
}

std::string Transform::toString() {
    std::string res = "[ ";
    for(Transformation *t : *this->lista)
    {
        res += t->toString() + " | ";
    }
    return res + ']';
}

void Transform::addTranformation(Transformation *t) {
    this->lista->push_back(t);
}
