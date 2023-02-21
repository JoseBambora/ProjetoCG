//
// Created by josebambora on 18-02-2023.
//

#include "Camera.h"

Camera::Camera(int posx, int posy, int posz,
               int lax, int lay, int laz,
               int upx, int upy, int upz,
               int fov, int near, int far ) {
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
