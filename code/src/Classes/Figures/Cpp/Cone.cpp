#include <fstream>
#include <vector>
#include "../Header/Cone.h"
#include "GL/glut.h"
#include "../Header/Basics.h"

const int Figure::codCone;

void Cone::calculatePoints(float radius, float height, int slices, int stacks)
{
    this->base = getPointsCircumference(0,0,0,radius,slices);
    float reduz = radius * (height/(float) stacks)/ height;
    float raio = radius - reduz;
    float aumento = height/(float) stacks;
    float y = aumento;
    this->superficielateral = std::vector<std::vector<float>>();
    for(int i = 0; i < stacks; i++)
    {
        this->superficielateral.push_back(getPointsCircumference(0,y,0,raio,slices));
        y+= aumento;
        raio -= reduz;
    }
    this->coordsTopo = std::vector<float>();
    coordsTopo.push_back(0);
    coordsTopo.push_back(height);
    coordsTopo.push_back(0);
}

Cone* Cone::Build(int argc, char **argv) {
    Cone *c = new Cone();
    if(argc == 7)
    {
        float radius = std::stof(argv[2]);
        float height = std::stof(argv[3]);
        int slices = std::stoi(argv[4]);
        int stacks = std::stoi(argv[5]);
        c->calculatePoints(radius,height,slices,stacks);
        std::string name = argv[6];
        c->Write_File(name);
    }
    else
        printf("Invalid arguments for cone. Creating a cone with default values.\n");
    return c;
}

/**
 * 1ª linha - coodenadas da base
 * n linhas - circunferências laterais
 * ultima linha - coordenadas vertice topo
 */
void Cone::Write_File(const std::string &name) {
    std::vector<std::vector<float>> write = this->superficielateral;
    write.insert(write.begin(),this->base);
    write.push_back(this->coordsTopo);
    writePoints(write, name, Figure::codCone);
}

Cone* Cone::Read_File(std::ifstream file) {
    Cone *res = new Cone();
    std::vector<std::vector<float>> read = readPoints(std::move(file));
    res->base = read[0];
    res->superficielateral = std::vector<std::vector<float>>(read.begin()+1, read.end()-1);
    res->coordsTopo = read[read.size()-1];
    return res;
}

std::string Cone::toString() {
    std::string res = "Cone";
    // res.append("\t\tVertice Superior:");
    // res.append("(");
    // res.append(std::to_string(this->coordsTopo[0]));
    // res.append(",");
    // res.append(std::to_string(this->coordsTopo[1]));
    // res.append(",");
    // res.append(std::to_string(this->coordsTopo[2]));
    // res.append(")\n");
    // res.append("\t\tNúmero circunferências laterais:");
    // res.append(std::to_string(this->superficielateral.size()));
    return res;
}

void Cone::drawFigure() {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    //this->calculatePoints();
    drawPyramid(base,0,0,0, false,1.0f,1.0f,1.0f);
    std::vector<float> anterior = base;
    for(int i = 0; i < this->superficielateral.size()-1; i++)
    {
        drawSideFora(anterior,superficielateral[i],1.0f,1.0f,1.0f);
        anterior = superficielateral[i];
    }
    std::vector<float> topo = this->superficielateral[this->superficielateral.size()-1];
    drawPyramid(anterior,topo[0],topo[1],topo[2], true,1.0f,1.0f,1.0f);

}
Cone::~Cone() = default;
