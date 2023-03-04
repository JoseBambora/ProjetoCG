#include <fstream>
#include <vector>
#include "../Header/Cone.h"
#include "GL/glut.h"
#include "../Header/Basics.h"

const int Figure::codCone;

Cone* Cone::Build(int argc, char **argv) {
    Cone *c = new Cone();
    if(argc == 7)
    {
        c->radius = std::stof(argv[2]);
        c->height = std::stof(argv[3]);
        c->slices = std::stoi(argv[4]);
        c->stacks = std::stoi(argv[5]);
        std::string name = argv[6];
        c->Write_File(name);
    }
    else
        printf("Invalid arguments for cone. Creating a cone with default values.\n");
    return c;
}

void Cone::Write_File(const std::string &name) {
    std::ofstream myfile;
    myfile.open (name,std::ios::binary | std::fstream::out);
    myfile.write((char *) &Figure::codCone,sizeof(Figure::codCone));
    myfile.write((char *) &radius,sizeof(radius));
    myfile.write((char *) &height,sizeof(height));
    myfile.write((char *) &slices,sizeof(slices));
    myfile.write((char *) &stacks,sizeof(stacks));
    myfile.close();
}

Cone* Cone::Read_File(std::ifstream file) {
    Cone *res = new Cone();
    float d3,d4;
    int d5,d6;
    file.read((char *) &d3, sizeof(d3));
    file.read((char *) &d4, sizeof(d4));
    file.read((char *) &d5, sizeof(d5));
    file.read((char *) &d6, sizeof(d6));
    res->radius = d3;
    res->height = d4;
    res->slices = d5;
    res->stacks = d6;
    return res;
}

std::string Cone::toString() {
    std::string res = "\tCone:\n";
    res.append("\t\tRadius: ");
    res.append(std::to_string(this->radius));
    res.append("\n\t\tHeight: ");
    res.append(std::to_string(this->height));
    res.append("\n\t\tSlices: ");
    res.append(std::to_string(this->slices));
    res.append("\n\t\tStacks: ");
    res.append(std::to_string(this->stacks));
    return res;
}

void Cone::drawFigure() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    std::vector<float> base = getPointsCircumference(0,0,0,this->radius,this->slices);
    // Desenha base, pirâmide com altura 0
    drawPyramid(base,0,0,0, false,1.0f,1.0f,1.0f);
    // Quantidade a reduzir com base no raio (semelhança de triângulos)
    float reduz = this->radius * (this->height/this->stacks)/ this->height;
    float raio = this->radius - reduz;
    // circunferência anterior para conectar
    std::vector<float> anterior = base;
    // aumento do y das circunferências intermédias
    float aumento = this->height/(float) this->stacks;
    // Y das circunferências intermédias
    float y = aumento;
    for(int i = 0; i < this->stacks; i++)
    {
        std::vector<float> circ = getPointsCircumference(0,y,0,raio,this->slices);
        y+= aumento;
        raio -= reduz;
        drawSide(anterior,circ,1.0f,1.0f,1.0f);
        anterior = circ;
    }
    drawPyramid(anterior,0,this->height,0, false,1.0f,1.0f,1.0f);

}
Cone::~Cone() = default;
