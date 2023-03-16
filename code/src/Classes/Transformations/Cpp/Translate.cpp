#include "../Header/Translate.h"
#include "GL/glut.h"

std::string Translate::toString() {
    return "Translate";
}

void Translate::apply() {
    glPushMatrix();
    glTranslatef(this->x,this->y,this->z);
}

Translate::~Translate() {

}

Translate::Translate(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
