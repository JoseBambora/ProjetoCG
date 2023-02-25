//
// Created by josebambora on 18-02-2023.
//

#include "../Header/Camera.h"
#include "GL/glut.h"

Camera::Camera(float posx,float posy, float posz,
               float lax, float lay,  float laz,
               float upx, float upy,  float upz,
               float fov, float near, float far ) {
    this->posx = posx;
    this->posy = posy;
    this->posz = posz;
    this->lax = lax;
    this->lay = lay;
    this->laz = laz;
    this->upx = upx;
    this->upy = upy;
    this->upz = upz;
    this->profov = fov;
    this->pronear = near;
    this->profar = far;
}

std::string Camera::toString() const {
    std::string res;
    res.append("Position:\n");
    res.append("\tx: ");
    res.append(std::to_string(this->posx));
    res.append("\n\ty: ");
    res.append(std::to_string(this->posy));
    res.append("\n\tz: ");
    res.append(std::to_string(this->posz));
    res.append("\nLook at:\n");
    res.append("\tx: ");
    res.append(std::to_string(this->lax));
    res.append("\n\ty: ");
    res.append(std::to_string(this->lay));
    res.append("\n\tz: ");
    res.append(std::to_string(this->laz));
    res.append("\nUP:\n");
    res.append("\tx: ");
    res.append(std::to_string(this->upx));
    res.append("\n\ty: ");
    res.append(std::to_string(this->upy));
    res.append("\n\tz: ");
    res.append(std::to_string(this->upz));
    res.append("\nProjection:\n");
    res.append("\tfov: ");
    res.append(std::to_string(this->profov));
    res.append("\n\tnear: ");
    res.append(std::to_string(this->pronear));
    res.append("\n\tfar: ");
    res.append(std::to_string(this->profar));
    res.append("\n");
    return res;
}

void Camera::posicionaCamara(int w, int h) const {

    gluLookAt(this->posx, this->posy, this->posz,
              this->lax, this->lay, this->laz,
              this->upx, this->upy, this->upz);
    //gluPerspective(this->profov,(GLfloat)w/(GLfloat)h,this->pronear,this->profar);
}
