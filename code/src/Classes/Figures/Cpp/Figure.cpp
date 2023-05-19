#include <fstream>
#include <iostream>
#include <utility>
#include "../Header/Figure.h"
#include "../Header/Cone.h"
#include "../Header/Sphere.h"
#include "../Header/Box.h"
#include "../Header/Plane.h"
#include "../Header/Donut.h"
#include "../Header/Cylinder.h"
#include "../Header/Bezier.h"
#include "../Header/Basics.h"

// Build a figure, given the exec arguments
// CAN BE NULL
// Each sub class creates the file given automatically, with the information of the figure.
Figure *Figure::Build(int argc, char **argv) {
    Figure *res = nullptr;
    if(argc > 2)
    {
        std::string figure = argv[1];
        if(figure == "sphere")
            res = Sphere::Build(argc,argv);
        else if(figure == "box")
            res = Box::Build(argc,argv);
        else if(figure == "cone")
            res = Cone::Build(argc,argv);
        else if(figure == "plane")
            res = Plane::Build(argc,argv);
        else if(figure == "donut")
            res = Donut::Build(argc,argv);
        else if(figure == "cylinder")
            res = Cylinder::Build(argc,argv);
        else if(figure == "patch")
            res = Bezier::Build(argc,argv);
        else
            printf("Invalid figure. Figure result: nullptr\n");
    }
    return res;
}

// Reads the content from a binary file. It will create a figure, based on the file information.
// CAN BE NULL
Figure *Figure::ReadFile(const std::string& name, std::vector<float> *diffusecolor, std::vector<float> *ambientcolor,
                         std::vector<float> *specularcolor, std::vector<float> *emissivecolor, float shininessvalue,
                         std::string texturefile) {
    int cod;
    Figure *res;
    std::ifstream file;
    file.open(name, std::ios::binary);
    file.read((char *) &cod, sizeof(cod));
    switch (cod) {
        case codBox:
            res = Box::Read_File(std::move(file));
            break;
        case codPlane:
            res = Plane::Read_File(std::move(file));
            break;
        case codSphere:
            res = Sphere::Read_File(std::move(file));
            break;
        case codCone:
            res = Cone::Read_File(std::move(file));
            break;
        case codDonut:
            res = Donut::Read_File(std::move(file));
            break;
        case codCylinder:
            res = Cylinder::Read_File(std::move(file));
            break;
        case codBezierPatch:
            res = Bezier::Read_File(std::move(file));
            break;
        default:
            printf("Invalid file. Result figure = nullptr\n");
            res = nullptr;
    }
    if(res)
    {
        res->fileText = std::move(texturefile);
        res->diffuse = new std::vector<float>(*diffusecolor);
        res->emissive = new std::vector<float>(*emissivecolor);
        res->specular = new std::vector<float>(*specularcolor);
        res->ambient = new std::vector<float>(*ambientcolor);
        res->shininnes = shininessvalue;
    }
    return res;
}

void Figure::drawFigure() {
    // drawVBO(vertices,verticeCount,1.0f,1.0f,1.0f);
    if(this->texturaID != 0)
        glBindTexture(GL_TEXTURE_2D, this->texturaID);
    else
        materialLighting(ambient,diffuse,specular,emissive,shininnes);
    drawVBOIluminacaoTextura(vbos,verticeCount);
}
void Figure::apply() {
    drawFigure();
}
void Figure::undo() {}
void Figure::load() {
    if (this->fileText != "")
    {
        std::cout << "Figura com textura\n";
        this->texturaID = loadTexture(this->fileText);
    }
    else
    {
        std::cout << "Figura sem textura\n";
        this->texturaID = 0;
    }
    loadVBO();
}
void Figure::loadVBO() {}

void Figure::loadVertices(unsigned int * res,int vc) {
    this->verticeCount = vc;
    this->vbos = res;
}

