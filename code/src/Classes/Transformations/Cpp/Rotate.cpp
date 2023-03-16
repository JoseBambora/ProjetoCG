#include "../Header/Rotate.h"
#include "GL/glut.h"

std::string Rotate::toString() {
    return "Rotate"; // + std::to_string(this->angle) + ',' + std::to_string(this->x)+','+ std::to_string(this->y)+','+ std::to_string(this->z) +')';

}

void Rotate::apply() {
    glPushMatrix();
    glRotatef(this->angle,this->x,this->y,this->z);
}

Rotate::~Rotate() {

}

Rotate::Rotate(float angle, float x, float y, float z) {
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
}
