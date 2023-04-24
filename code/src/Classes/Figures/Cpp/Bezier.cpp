#include <sstream>
#include <vector>
#include <fstream>
#include <cmath>
#include <GL/glut.h>
#include "../Header/Bezier.h"
#include "../../EngineClasses/Header/MatrixOperations.h"

template<typename T>
void getNumbers(std::istringstream iss, std::vector<T>* points)
{
    T number;
    while(iss >> number)
    {
        points->push_back(number);
        if (iss.peek() == ',' || iss.peek() == ' ')
            iss.ignore();
    }
}

void readInfoPatch(int *numpatchs, int *controlpoints,std::vector<std::vector<int>>* indices,std::vector<std::vector<float>>* points, const std::string& filename)
{
    std::ifstream infile(filename);
    std::string line;
    int np;
    int cp;
    for (int i = 0; std::getline(infile, line); i++)
    {
        std::istringstream iss(line);
        if(i == 0)
            iss >> np;
        else if (i <= np)
        {
            std::vector<int> indexadd;
            getNumbers(std::move(iss),&indexadd);
            indices->push_back(indexadd);
        }
        else if (i == np + 1)
            iss >> cp;
        else
        {
            std::vector<float> pointAdd;
            getNumbers(std::move(iss),&pointAdd);
            points->push_back(pointAdd);
        }
    }
    *numpatchs = np;
    *controlpoints = cp;
}

Bezier::Bezier(const char *filename) {
    std::string file = filename;
    int numpatchs;
    int controlpoints;
    std::vector<std::vector<int>> indices;
    std::vector<std::vector<float>> points;
    readInfoPatch(&numpatchs,&controlpoints,&indices,&points,file);
    this->calculaPoints(indices,points);
}


void Bezier::calculaPoints( std::vector<std::vector<int>> indices, std::vector<std::vector<float>> points) {
    // separar em x y z
    // seila = M * V (4x4 * 4x1 = 4x1)
    // seila2x = px * seila (4x4 * 4x1 = 4x1)
    // seila2y = py * seila (4x4 * 4x1 = 4x1)
    // seila2z = pz * seila (4x4 * 4x1 = 4x1)
    // seila2x = M * seila2x (4x4 * 4x1 = 4x1)
    // seila2y = M * seila2y (4x4 * 4x1 = 4x1)
    // seila2z = M * seila2z (4x4 * 4x1 = 4x1)
    // resx = U * seila2x = (1x4 * 4x1 = 1)
    // resy = U * seila2y = (1x4 * 4x1 = 1)
    // resz = U * seila2z = (1x4 * 4x1 = 1)
    // res = (resx, resy, resz)
    // this->pointsConnections->push_back(res)
    // Pescorrer os pontos e desenhar strips
    this->pointsConnections = new std::vector<std::vector<float>>();
    float px[4][4];
    float py[4][4];
    float pz[4][4];
    float m[4][4];
    bezierMatrixM(m);
    printf("Calculou M corretamente\n");
    // for(int k = 0; k < 4; k++)
    //     printf("%.2f %.2f %.2f %.2f\n",m[k][0],m[k][1],m[k][2],m[k][3]);
    for(int i = 0; i < indices.size(); i++)
    {
        std::vector<int> indexline = indices[i];
        std::vector<std::vector<float>> p0;
        std::vector<std::vector<float>> p1;
        std::vector<std::vector<float>> p2;
        std::vector<std::vector<float>> p3;
        for(int j = 0; j < 4; j++)
        {
            // printf("p0: %.2f %.2f %.2f\n", points[indexline[j]][0],points[indexline[j]][1],points[indexline[j]][2]);
            // printf("p1: %.2f %.2f %.2f\n", points[indexline[j+4]][0],points[indexline[j+4]][1],points[indexline[j+4]][2]);
            // printf("p2: %.2f %.2f %.2f\n", points[indexline[j+8]][0],points[indexline[j+8]][1],points[indexline[j+8]][2]);
            // printf("p3: %.2f %.2f %.2f\n", points[indexline[j+12]][0],points[indexline[j+12]][1],points[indexline[j+12]][2]);
            p0.push_back(points[indexline[j]]);
            p1.push_back(points[indexline[j+4]]);
            p2.push_back(points[indexline[j+8]]);
            p3.push_back(points[indexline[j+12]]);
        }
        bezierMatrixPoints(p0,p1,p2,p3,px,py,pz);
        printf("Calculou pontos p0 p1 p2 p3 corretamente\n");
        float uvalor = 0;
        float u[4];
        for(int primeiras = 0; primeiras < lim; primeiras++)
        {
            float vvalor = 0;
            float v[4];
            bezierMatrixUV(uvalor,u);
            for(int segundas = 0; segundas < lim; segundas++)
            {
                bezierMatrixUV(vvalor,v);
                vvalor += (float) 1/lim;
                float res1[4];
                multMatrixVector(m,v,res1);
                float resx1[4];
                float resy1[4];
                float resz1[4];
                multMatrixVector(px,res1,resx1);
                multMatrixVector(py,res1,resy1);
                multMatrixVector(pz,res1,resz1);
                float resx2[4];
                float resy2[4];
                float resz2[4];
                multMatrixVector(m,resx1,resx2);
                multMatrixVector(m,resy1,resy2);
                multMatrixVector(m,resz1,resz2);
                float resx3 = multiplicaVetores(u,resx2);
                float resy3 = multiplicaVetores(u,resy2);
                float resz3 = multiplicaVetores(u,resz2);
                std::vector<float> point;
                point.push_back(resx3);
                point.push_back(resy3);
                point.push_back(resz3);
                this->pointsConnections->push_back(point);
            }
            uvalor += (float) 1/lim;
        }
    }
    //this->reorganizaPontos();
}
Bezier *Bezier::Build(int argc, char **argv) {
    printf("Função Build a fazer curva bezier");
    return nullptr;
}

void Bezier::Write_File(const std::string &name) {
    printf("Função Write_File a fazer curva bezier");

}

Bezier *Bezier::Read_File(std::ifstream file) {
    printf("Função Read_File a fazer curva bezier");
    return nullptr;
}

std::string Bezier::toString() {
    return "Curva Bezier";
}


void Bezier::loadVBO() {
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glBegin(GL_LINE_STRIP);
    for(int j = 0; j < this->pointsConnections->size();j++)
    {
        // int j2 = j + lim;
        // int j3 = j2 + lim;
        // int j4 = j3 + lim;
        printf("%.2f %.2f %.2f | ",this->pointsConnections->at(j)[0],this->pointsConnections->at(j)[1],this->pointsConnections->at(j)[2]);
        glVertex3f(this->pointsConnections->at(j)[0],this->pointsConnections->at(j)[1],this->pointsConnections->at(j)[2]);
        // if((j / this->lim) % 4 != 3 && j+this->lim < this->pointsConnections->size())
        //     glVertex3f(this->pointsConnections->at(j+this->lim)[0],this->pointsConnections->at(j+this->lim)[1],this->pointsConnections->at(j+this->lim)[2]);
        if(j % this->lim == this->lim-1)
        {
            glEnd();
            glBegin(GL_LINE_STRIP);
        }
        // glVertex3f(this->pointsConnections->at(j2)[0],this->pointsConnections->at(j2)[1],this->pointsConnections->at(j2)[2]);
        // glVertex3f(this->pointsConnections->at(j3)[0],this->pointsConnections->at(j3)[1],this->pointsConnections->at(j3)[2]);
        //glVertex3f(this->pointsConnections->at(j4)[0],this->pointsConnections->at(j4)[1],this->pointsConnections->at(j4)[2]);

        // if(j > 0)
        //     glVertex3f(this->pointsConnections->at(j)[0],this->pointsConnections->at(j)[1],this->pointsConnections->at(j)[2]);
    }
    glEnd();
    glPopMatrix();
}

void calculaPoints2(std::vector<int> indices, std::vector<float> points) {

    /*
    // grau 1 : coordenadas pontos
    // grau 2 : 1 curva
    // grau 3 : todas as curvas
    printf("Entrou\n");
    this->pointsCurve = new std::vector<std::vector<std::vector<float>>>();
    std::vector<float> p1; std::vector<float> p2; std::vector<float> p3; std::vector<float> p4;
    for(int i = 0; i < indices.size();)
    {
        int index_p1 = indices[i++] * 3;
        int index_p2 = indices[i++] * 3;
        int index_p3 = indices[i++] * 3;
        int index_p4 = indices[i++] * 3;
        p1.clear();
        p2.clear();
        p3.clear();
        p4.clear();
        p4.push_back(points[index_p1++]);
        p4.push_back(points[index_p1++]);
        p4.push_back(points[index_p1]);
        p3.push_back(points[index_p2++]);
        p3.push_back(points[index_p2++]);
        p3.push_back(points[index_p2]);
        p2.push_back(points[index_p3++]);
        p2.push_back(points[index_p3++]);
        p2.push_back(points[index_p3]);
        p1.push_back(points[index_p4++]);
        p1.push_back(points[index_p4++]);
        p1.push_back(points[index_p4]);
        this->calculaCurva(p1,p2,p3,p4);
    }
    printf("Calculou Curvas %d\n",this->pointsCurve->size());
    this->curvasreais = this->pointsCurve->size();
    for (int i = 0; i < this->curvasreais;i+=4)
    {
        // primeiro curvas de cima
        // esqueda -> direita
        std::vector<std::vector<float>> curva1 = this->pointsCurve->at(i);
        std::vector<std::vector<float>> curva2 = this->pointsCurve->at(i+1);
        std::vector<std::vector<float>> curva3 = this->pointsCurve->at(i+2);
        std::vector<std::vector<float>> curva4 = this->pointsCurve->at(i+3);
        for(int j = 0; j < curva1.size(); j++)
        {
            this->calculaCurva(curva1[j],curva2[j], curva3[j],curva4[j]);
        }
    }
    this->pointsConnections = new std::vector<std::vector<float>>();
    for (int i = this->curvasreais; i < this->pointsCurve->size()-1;i++)
    {
        if ((i- this->curvasreais) % 24 != 23)
        {
            std::vector<std::vector<float>> curva1 = this->pointsCurve->at(i);
            std::vector<std::vector<float>> curva2 = this->pointsCurve->at(i + 1);
            for(int j = 0; j < curva1.size(); j++)
            {
                p1 = curva1[j];
                p2 = curva2[j];
                this->pointsConnections->push_back(p2);
                this->pointsConnections->push_back(p1);
            }
        }
    }
    // ligar primeira curva -> segunda curva
    // ligar primeira curva -> ultima curva
    std::vector<std::vector<float>> curva1 = this->pointsCurve->at(this->curvasreais);
    std::vector<std::vector<float>> curva3 = this->pointsCurve->at(this->curvasreais+1);
    std::vector<std::vector<float>> curva2 = this->pointsCurve->at(this->pointsCurve->size()-1);
    printf("===================\n");
    for(int j = 0; j < curva1.size(); j++)
    {
        p1 = curva1[j];
        p2 = curva2[j];
        this->pointsConnections->push_back(p1);
        this->pointsConnections->push_back(p2);
    }
    for(int j = 0; j < curva1.size(); j++)
    {
        p1 = curva1[j];
        p2 = curva3[j];
        this->pointsConnections->push_back(p2);
        this->pointsConnections->push_back(p1);
    }
    printf("Acabou Calculo Curvas\n");
    */
}

void Bezier::aplicaFormula(std::vector<float> p1, std::vector<float> p2, std::vector<float> p3, std::vector<float> p4,
                           float t, std::vector<float> *res) {
    float t_um = powf(t,3);
    float t_dois = 3 * powf(t,2) * (1-t);
    float t_tres = 3 * t * powf(1-t,2);
    float t_quatro = powf(1-t,3);
    std::vector<float> paux0;
    std::vector<float> paux1;
    std::vector<float> paux2;
    std::vector<float> paux3;
    multiplicaVetorValor(p1,t_um,&paux0);
    multiplicaVetorValor(p2,t_dois,&paux1);
    multiplicaVetorValor(p3,t_tres,&paux2);
    multiplicaVetorValor(p4,t_quatro,&paux3);
    somaVetores(paux0,paux1,paux2,paux3,res);
}

/*
void Bezier::calculaCurva(std::vector<float> p1, std::vector<float> p2, std::vector<float> p3, std::vector<float> p4) {
    std::vector<std::vector<float>> curva;
    int aux = 6;
    for (int t = 0; t < aux; t++)
    {
        float t_aux = (float) t / aux;
        std::vector<float> res;
        this->aplicaFormula(p1,p2,p3,p4,t_aux,&res);
        curva.push_back(res);
    }
    pointsCurve->push_back(curva);
}
*/

void Bezier::connectPoints(std::vector<std::vector<float>> curva1,std::vector<std::vector<float>> curva2,bool ordem) {
    std::vector<float> p1; std::vector<float> p2;
    for(int j = 0; j < curva1.size(); j++)
    {
        p1 = curva1[j];
        p2 = curva2[j];
        if(ordem)
        {
            this->pointsConnections->push_back(p2);
            this->pointsConnections->push_back(p1);
        }
        else
        {
            this->pointsConnections->push_back(p1);
            this->pointsConnections->push_back(p2);
        }
    }
}

void Bezier::calculapuv(float *u, float *v,std::vector<std::vector<float>> points)
{
    float matriz[4][4] = {{-1,3,-3,1},
            {3,-6,3,0},
            {-3,3,0,0},
            {1,0,0,0 }};

    std::vector<float> p00 = points[0];
    std::vector<float> p01 = points[1];
    std::vector<float> p02 = points[2];
    std::vector<float> p03 = points[3];

    std::vector<float> p10 = points[4];
    std::vector<float> p11 = points[5];
    std::vector<float> p12 = points[6];
    std::vector<float> p13 = points[7];

    std::vector<float> p20 = points[8];
    std::vector<float> p21 = points[9];
    std::vector<float> p22 = points[10];
    std::vector<float> p23 = points[11];

    std::vector<float> p30 = points[12];
    std::vector<float> p31 = points[13];
    std::vector<float> p32 = points[14];
    std::vector<float> p33 = points[15];

    float matrizPontos[4][4][3] = {
            {
                    {p00[0],p00[1],p00[2]},
                     {p10[0],p10[1],p10[2]},
                     {p20[0],p20[1],p20[2]},
                     {p30[0],p30[1],p30[2]}
                },
            {
                {p01[0],p01[1],p01[2]},
                {p11[0],p11[1],p11[2]},
                {p21[0],p21[1],p21[2]},
                {p31[0],p31[1],p31[2]}},
            {
                {p02[0],p02[1],p02[2]},
                {p12[0],p12[1],p12[2]},
                {p22[0],p22[1],p22[2]},
                {p32[0],p32[1],p32[2]}
            },
            {
                {p03[0],p03[1],p03[2]},
                {p13[0],p13[1],p13[2]},
                {p23[0],p23[1],p23[2]},
                {p33[0],p33[1],p33[2]}
            }
    };
}

void Bezier::reorganizaPontos() {
    this->pointsCurve = new std::vector<std::vector<float>>();
    int iteracoes = 3 * this->pointsConnections->size() / 4;
    for(int j = 0; j < this->pointsConnections->size();j++)
    {
        for(int i = 0; i < 3 && j < this->pointsConnections->size()-this->lim; i++)
        {
            std::vector<float> cima = this->pointsConnections->at(j);
            std::vector<float> baixo = this->pointsConnections->at(this->lim+j);
            this->pointsCurve->push_back(cima);
            this->pointsCurve->push_back(baixo);
            j++;
        }
    }
}
