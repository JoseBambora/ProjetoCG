//
// Created by josebambora on 18-02-2023.
//

#include "../Header/Camera.h"
#include "../Header/MatrixOperations.h"
#include "GL/glut.h"
#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <iostream>

Camera* Camera::instance;
float Camera::profar;
float Camera::pronear;
float Camera::profov;

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
    profov = fov;
    pronear = near;
    profar = far;
    instance = this;
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


void getVetorDirecaoAndUp(float *d, float *u)
{
    auto *p = new float[3];
    p[0] = Camera::instance->posx;
    p[1] = Camera::instance->posy;
    p[2] = Camera::instance->posz;
    auto *l = new float[3];
    l[0] = Camera::instance->lax;
    l[1] = Camera::instance->lay;
    l[2] = Camera::instance->laz;
    u[0] = Camera::instance->upx;
    u[1] = Camera::instance->upy;
    u[2] = Camera::instance->upz;
    vetorPontos(p,l,d);
    delete []l;
    delete []p;
}

void esquerda(float *u,float *d,float *final)
{
    // multiplicar up com d -> esquerda
    // normalizar
    multVetor(u,d,final);
}

void direita(float *u,float *d,float *final)
{
    // multiplicar d com up -> direita
    // normalizar
    multVetor(d,u,final);
}

void frente(float *d, float *final)
{
    // d
    final[0] = d[0];
    final[1] = d[1];
    final[2] = d[2];
}

void traz(float *d, float *final)
{
    // o simétrico de d
    final[0] = -d[0];
    final[1] = -d[1];
    final[2] = -d[2];
}

void sobe(float *u, float *d, float *final)
{
    auto aux = new float[3];
    // multiplicar up com d -> esquerda
    // normalizar
    // multiplicar d com esquerda -> cima
    // normalizar
    multVetor(u,d,aux);
    multVetor(d,aux,final);
    delete []aux;
}


void baixo(float *u, float *d, float *final)
{
    auto aux = new float[3];
    // multiplicar up com d -> esquerda
    // normalizar
    // multiplicar d com esquerda -> cima
    // normalizar
    multVetor(u,d,aux);
    multVetor(aux,d,final);
    delete []aux;
}

void Camera::processSpecialKeys(int key, int xx, int yy) {
    auto *d = new float[3];
    auto *u = new float[3];
    getVetorDirecaoAndUp(d,u);
    auto *final = new float[3];
    if (key == 114)
    {
        baixo(u,d,final);
        Camera::instance->atualiza(final);
    }
    else
    {
        bool aux = true;
        switch (key)
        {
            case GLUT_KEY_LEFT:
                esquerda(u,d,final);
                break;
            case GLUT_KEY_RIGHT:
                direita(u,d,final);
                break;
            case GLUT_KEY_UP:
                sobe(u,d,final);
                break;
            case GLUT_KEY_DOWN:
                baixo(u,d,final);
                break;
            default:
                aux = false;
                break;
        }
        if(aux)
            Camera::instance->atualizaLA(final);
    }
    delete []final;
    delete []d;
    delete []u;
    glutPostRedisplay();
}


void Camera::processKeys(unsigned char key, int xx, int yy) {
    auto *d = new float[3];
    auto *u = new float[3];
    getVetorDirecaoAndUp(d,u);
    auto *final = new float[3];
    bool aux = true;
    switch (key)
    {
        // sobe
        case ' ':
            sobe(u,d,final);
            break;
        // frente
        case 'w':
            frente(d,final);
            break;
        // esquerda
        case 'a':
            esquerda(u,d,final);
            break;
        // direita
        case 'd':
            direita(u,d,final);
            break;
        // baixo
        case 's':
            traz(d,final);
            break;
        default:
            aux = false;
            break;
    }
    if(aux)
        Camera::instance->atualiza(final);
    delete []final;
    delete []d;
    glutPostRedisplay();
}


void Camera::posicionaCamara(int w, int h) const {
    gluLookAt(this->posx, this->posy, this->posz,
              this->lax, this->lay, this->laz,
              this->upx, this->upy, this->upz);
}

void Camera::changeSize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = w * 1.0f / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(profov, ratio, pronear, profar);
    glMatrixMode(GL_MODELVIEW);
}

void Camera::atualiza(float *movimento) {
    movimento[0] /= 2;
    movimento[1] /= 2;
    movimento[2] /= 2;
    this->posx += movimento[0];
    this->posy += movimento[1];
    this->posz += movimento[2];
    this->lax += movimento[0];
    this->lay += movimento[1];
    this->laz += movimento[2];
}

void Camera::atualizaLA(float *movimento) {
    movimento[0] /= 3;
    movimento[1] /= 3;
    movimento[2] /= 3;
    this->lax += movimento[0];
    this->lay += movimento[1];
    this->laz += movimento[2];
}

