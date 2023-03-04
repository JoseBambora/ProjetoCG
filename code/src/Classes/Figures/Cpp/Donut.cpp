
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
    // circunferência central
    std::vector<float> cin = getPointsCircumference(0,0,0,this->radiusin,this->slices);
    // circunferência exterior
    std::vector<float> cout = getPointsCircumference(0,0,0,this->radiusout,this->slices);
    // circunferência meio cima
    float raiointermedio = (this->radiusout-this->radiusin)/2;
    std::vector<float> cmtop = getPointsCircumference(0,raiointermedio,0,raiointermedio,this->slices);
    // circunferência meio baixo
    std::vector<float> cmdown = getPointsCircumference(0,-raiointermedio,0,raiointermedio,this->slices);
    float aumento = M_PI_2/this->stacks;
    float alfa = aumento;
    std::vector<float> anteriorcimaint = cin;
    std::vector<float> anteriorbaixoint = cin;
    std::vector<float> anteriorcimaext = cout;
    std::vector<float> anteriorbaixoext = cout;
    for(int i = 0; i < this->stacks; i++)
    {
        float cosalfa = std::cos(alfa);
        float yc = std::sin(alfa) * raiointermedio;
        float rint = this->radiusin + (raiointermedio - cosalfa * raiointermedio);
        float rext = this->radiusin + (raiointermedio + cosalfa * raiointermedio);
        std::vector<float> ccimaint = getPointsCircumference(0,yc,0,rint,this->slices);
        std::vector<float> cbaixoint = getPointsCircumference(0,-yc,0,rint,this->slices);
        std::vector<float> ccimaext = getPointsCircumference(0,yc,0,rext,this->slices);
        std::vector<float> cbaixoext = getPointsCircumference(0,-yc,0,rext,this->slices);
        alfa += aumento;
        drawSide(anteriorcimaint,ccimaint,1.0f,1.0f,1.0f);
        drawSide(ccimaext,anteriorcimaext,1.0f,1.0f,1.0f);
        drawSide(cbaixoint,anteriorbaixoint,1.0f,1.0f,1.0f);
        drawSide(anteriorbaixoext,cbaixoext,1.0f,1.0f,1.0f);
        anteriorbaixoint = cbaixoint;
        anteriorbaixoext = cbaixoext;
        anteriorcimaext = ccimaext;
        anteriorcimaint = ccimaint;
    }

}
