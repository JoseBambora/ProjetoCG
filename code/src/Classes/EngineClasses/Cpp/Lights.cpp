
#include <iostream>
#include "../Header/Lights.h"
#include "../Header/MatrixOperations.h"
#include "GL/glut.h"

Lights::Lights(int type, GLenum luz, std::vector<float> *values) {
    this->type = type;
    this->luz = luz;
    this->values = values;
}

Lights::~Lights() {
    delete this->values;
}

void Lights::renderLight() {
    float pos1[4] = {this->values->at(0),this->values->at(1),this->values->at(2),1.0f};
    float pos2[4] = {this->values->at(0),this->values->at(1),this->values->at(2),0.0f};
    switch (this->type)
    {
        case point:
            glLightfv(luz,GL_POSITION, pos1);
            break;
        case directional:
            glLightfv(luz,GL_POSITION, pos2);
            break;
        case spotlight:
            float dir[3] = {this->values->at(3),this->values->at(4),this->values->at(5)};
            normalize(dir);
            float angle = this->values->at(6);
            glLightfv(luz,GL_POSITION, pos1);
            glLightfv(luz,GL_SPOT_DIRECTION, dir);
            glLightf(luz,GL_SPOT_CUTOFF, angle);
            break;
    }
}

void Lights::initLight() {
    glEnable(this->luz);
    float dark[4] = {0.2, 0.2, 0.2, 1.0};
    float white[4] = {1.0, 1.0, 1.0, 1.0};
    float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    glLightfv(this->luz, GL_AMBIENT, dark);
    glLightfv(this->luz, GL_DIFFUSE, white);
    glLightfv(this->luz, GL_SPECULAR, white);

}
