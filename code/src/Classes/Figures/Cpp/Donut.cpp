
#include <fstream>
#include <vector>
#include "../Header/Donut.h"
#include "../Header/Basics.h"
#include <cmath>
#include "GL/glut.h"

const int Figure::codDonut;

Donut* Donut::Build(int argc, char **argv)
{
    auto *res = new Donut();
    if(argc == 7)
    {
        float rin = std::stof(argv[2]);
        float rout = std::stof(argv[3]);
        int slices = std::stoi(argv[4]);
        int stacks = std::stoi(argv[5]);
        std::string name = argv[6];
        res->radiusin = rin;
        res->radiusout = rout;
        res->stacks= stacks;
        res->slices = slices;
        res->Write_File(name);
    }
    else
        printf("Invalid arguments for donut. Creating a donut with default values.\n");
    return res;
}

void Donut::Write_File(const std::string &name) {
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &Figure::codDonut,sizeof(Figure::codDonut));
    myfile.write((char *) &radiusin,sizeof(radiusin));
    myfile.write((char *) &radiusout,sizeof(radiusout));
    myfile.write((char *) &slices,sizeof(slices));
    myfile.write((char *) &stacks,sizeof(stacks));
    myfile.close();
}

Donut *Donut::Read_File(std::ifstream file) {
    auto *res = new Donut();
    float rin,rout,altura;
    int slices,stacks;
    file.read((char *) &rin, sizeof(rin));
    file.read((char *) &rout, sizeof(rout));
    file.read((char *) &slices, sizeof(slices));
    file.read((char *) &stacks, sizeof(stacks));
    res->radiusin = rin;
    res->radiusout = rout;
    res->slices = slices;
    res->stacks = stacks;
    return res;
}

std::string Donut::toString() {
    std::string res = "\tDonut:\n";
    res.append("\t\tRadius Inside: ");
    res.append(std::to_string(this->radiusin));
    res.append("\n\t\tRadius Outside: ");
    res.append(std::to_string(this->radiusout));
    res.append("\n\t\tSlices: ");
    res.append(std::to_string(this->slices));
    res.append("\n\t\tStacks: ");
    res.append(std::to_string(this->stacks));
    return res;
}

Donut::~Donut() {

}

void Donut::drawFigure() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    float raiointermedio = (this->radiusout-this->radiusin)/2;
    // circunferência meio baixo
    std::vector<float> cmdown = getPointsCircumference(0,-raiointermedio,0,raiointermedio+this->radiusin,this->slices);
    float aumento = M_PI/this->stacks;
    float alfa = -M_PI_2;
    std::vector<float> anteriorint = cmdown;
    std::vector<float> anteriorext = cmdown;
    for(int i = 0; i < this->stacks+1; i++)
    {
        float cosalfa = std::cos(alfa);
        float yc = std::sin(alfa) * raiointermedio;
        float rint = this->radiusin + (raiointermedio - cosalfa * raiointermedio);
        float rext = this->radiusin + (raiointermedio + cosalfa * raiointermedio);
        std::vector<float> cint = getPointsCircumference(0,yc,0,rint,this->slices);
        std::vector<float> cext = getPointsCircumference(0,yc,0,rext,this->slices);
        alfa += aumento;
        drawSideDentro(anteriorint,cint,1.0f,1.0f,1.0f);
        drawSideFora(anteriorext,cext,1.0f,1.0f,1.0f);
        anteriorint = cint;
        anteriorext = cext;
    }
}
