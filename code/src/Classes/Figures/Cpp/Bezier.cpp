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

void readInfoPatch(int *numpatchs, int *controlpoints,std::vector<int>* indices,std::vector<float>* points, const std::string& filename)
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
            getNumbers(std::move(iss),indices);
        else if (i == np + 1)
            iss >> cp;
        else
            getNumbers(std::move(iss),points);
    }
    *numpatchs = np;
    *controlpoints = cp;
}

Bezier::Bezier(const char *filename) {
    std::string file = filename;
    int numpatchs;
    int controlpoints;
    std::vector<int> indices;
    std::vector<float> points;
    readInfoPatch(&numpatchs,&controlpoints,&indices,&points,file);
    this->calculaPoints(indices,points);
    // pointscurve, pontos de cada curva.
    //
    printf("Construtor por fazer curva bezier");

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

    /*
    for(int j = this->curvasreais; j < this->pointsCurve->size(); j++)
    {
        glBegin(GL_LINE_LOOP);
        std::vector<std::vector<float>> curva = this->pointsCurve->at(j);
        for(int i = 0; i < curva.size(); i++)
        {
            // printf(" (%d,%d) %.2f %.2f %.2f\n",j,i,curva.at(i)[0],curva.at(i)[1],curva.at(i)[2]);
            glVertex3f(curva.at(i)[0],curva.at(i)[1],curva.at(i)[2]);
        }
        for(int i = curva.size()-1; i>=0 ; i--)
        {
            glVertex3f(curva.at(i)[0],curva.at(i)[1],curva.at(i)[2]);
        }
        glEnd();
    }
    */
    glBegin(GL_TRIANGLE_STRIP);
    for(int j = 0; j < this->pointsConnections->size();j++)
    {
        printf("%.2f %.2f %.2f\n",this->pointsConnections->at(j)[0],this->pointsConnections->at(j)[1],this->pointsConnections->at(j)[2]);
        glVertex3f(this->pointsConnections->at(j)[0],this->pointsConnections->at(j)[1],this->pointsConnections->at(j)[2]);
    }
    glEnd();

    glPopMatrix();
}

void Bezier::calculaPoints(std::vector<int> indices, std::vector<float> points) {

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
