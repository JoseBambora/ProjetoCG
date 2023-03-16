#include "../Header/Scale.h"
#include "GL/glut.h"

std::string Scale::toString() {
    return "Scale "; // + std::to_string(this->x)+','+ std::to_string(this->y)+','+ std::to_string(this->z) +')';

}


void Scale::apply() {
    glPushMatrix();
    glScalef(this->x,this->y,this->z);
}

Scale::~Scale() {

}

Scale::Scale(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
