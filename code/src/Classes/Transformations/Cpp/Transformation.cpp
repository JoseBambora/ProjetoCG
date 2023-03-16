#include "../Header/Transformation.h"
#include "GL/glut.h"

void Transformation::undo() {
    glPopMatrix();
}
