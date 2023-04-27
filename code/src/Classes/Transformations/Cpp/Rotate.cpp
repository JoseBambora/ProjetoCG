#include "../Header/Rotate.h"
#include "GL/glut.h"

std::string Rotate::toString() {
    return "Rotate"; // + std::to_string(this->angle) + ',' + std::to_string(this->x)+','+ std::to_string(this->y)+','+ std::to_string(this->z) +')';

}

void Rotate::apply() {
    glPushMatrix();
    if(this->angle)
        glRotatef(this->numero,this->x,this->y,this->z);
    else
    {
        int current_time = glutGet(GLUT_ELAPSED_TIME);
        this->occor+= ((float) current_time-last_time)/1000;
        this->last_time = current_time;
        float var = (360 / this->numero) * this->occor;
        glRotatef(var,this->x,this->y,this->z);
    }
}

Rotate::~Rotate() {

}

Rotate::Rotate(float numero, float x, float y, float z, bool angle) {
    this->numero = numero;
    this->occor = 0;
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
    this->last_time = 0;
}
