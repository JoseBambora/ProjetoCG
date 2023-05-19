#include <string>
#include <cstdio>
#include <list>
#include <regex>
#include <iostream>
#include "../TinyXML/tinyxml2.h"
#include "../Classes/EngineClasses/Header/Lights.h"
#include "../Classes/EngineClasses/Header/World.h"
#include "../Classes/EngineClasses/Header/ListTree.h"
#include "../Classes/Transformations/Header/Transformation.h"
#include "../Classes/Transformations/Header/Rotate.h"
#include "../Classes/Transformations/Header/Scale.h"
#include "../Classes/Transformations/Header/Translate.h"
#include "../Classes/Transformations/Header/Transform.h"
#include "../Classes/Figures/Header/Figure.h"
#include "../Classes/Transformations/Header/CatmullRom.h"
const std::string dir = "../../files/";

using namespace tinyxml2;

void trataRGB(XMLElement *xml,std::vector<float>*color)
{
    std::string R, G,B;
    R = xml->Attribute("R");
    G = xml->Attribute("G");
    B = xml->Attribute("B");
    color->push_back(std::stof(R)/ 256);
    color->push_back(std::stof(G)/ 256);
    color->push_back(std::stof(B)/ 256);
    color->push_back(1.0f);
}

void trataColor(XMLElement *color, std::vector<float>*diffusecolor,std::vector<float>*ambientcolor,std::vector<float>*specularcolor,std::vector<float>*emissivecolor,float *shininessvalue)
{
    XMLElement *diffuse = color->FirstChildElement("diffuse");
    XMLElement *ambient = color->FirstChildElement("ambient");
    XMLElement *specular = color->FirstChildElement("specular");
    XMLElement *emissive = color->FirstChildElement("emissive");
    XMLElement *shininess = color->FirstChildElement("shininess");
    trataRGB(diffuse,diffusecolor);
    trataRGB(ambient,ambientcolor);
    trataRGB(specular,specularcolor);
    trataRGB(emissive,emissivecolor);
    *shininessvalue = std::stof(shininess->Attribute("value"));
}

void trataModels(XMLElement *models , ListTree * tree)
{
    XMLElement *model = models->FirstChildElement("model");
    while (model)
    {
        std::vector<float> ambient,specular,diffuse,emissive;
        float shininnes;
        trataColor(model->FirstChildElement("color"),&diffuse,&ambient,&specular,&emissive,&shininnes);
        std::string nameFile = model->Attribute("file");
        // TO DO loadTexture
        Figure *figura = Figure::ReadFile(nameFile,&diffuse,&ambient,&specular,&emissive,shininnes,0);
        tree->addNode(figura);
        model = model->NextSiblingElement("model");
        //printf("Model: %s\n",nameFile.c_str());
    }
}

std::vector<float>* readPoints(XMLElement *translate)
{
    auto* res = new std::vector<float>();
    XMLElement *point = translate->FirstChildElement("point");
    while (point)
    {
        float x = std::stof(point->Attribute("x"));
        float y = std::stof(point->Attribute("y"));
        float z = std::stof(point->Attribute("z"));
        res->push_back(x);
        res->push_back(y);
        res->push_back(z);
        point = point->NextSiblingElement("point");
    }
    return res;
}

void trataTransform(XMLElement *transform, ListTree *tree)
{
    std::regex boolReg("[Tt][Rr][Uu][Ee]");
    XMLElement *child = transform->FirstChildElement();
    auto *transformacao = new Transform();
    bool b = true;
    while(b)
    {
        b = child;
        if (b)
        {
            Transformation *t = nullptr;
            if(std::string(child->Value()) == "translate")
            {
                if(child->Attribute("x"))
                {
                    float x = std::stof(child->Attribute("x"));
                    float y = std::stof(child->Attribute("y"));
                    float z = std::stof(child->Attribute("z"));
                    t = new Translate(x,y,z);
                }
                else
                {
                    float time = std::stof(child->Attribute("time"));
                    bool align = std::regex_match(child->Attribute("align"),boolReg);
                    std::vector<float> *points = readPoints(child);
                    t = new CatmullRom(points,time,align);
                }
                transformacao->addTranformation(t);
            }
            else if(std::string(child->Value()) == "rotate")
            {
                if(child->Attribute("angle"))
                {
                    float x = std::stof(child->Attribute("x"));
                    float y = std::stof(child->Attribute("y"));
                    float z = std::stof(child->Attribute("z"));
                    float angle = std::stof(child->Attribute("angle"));
                    t = new Rotate(angle,x,y,z, true);
                }
                else
                {
                    float x = std::stof(child->Attribute("x"));
                    float y = std::stof(child->Attribute("y"));
                    float z = std::stof(child->Attribute("z"));
                    float time = std::stof(child->Attribute("time"));
                    t = new Rotate(time,x,y,z, false);
                }
                transformacao->addTranformation(t);
            }
            else if(std::string(child->Value()) == "scale")
            {
                float x = std::stof(child->Attribute("x"));
                float y = std::stof(child->Attribute("y"));
                float z = std::stof(child->Attribute("z"));
                t = new Scale(x,y,z);
                transformacao->addTranformation(t);
            }
            child = child->NextSiblingElement();
        }
    }
    tree->addNode(transformacao);
    tree->openLevel();
}

void trataGrupo(XMLElement *group, ListTree*tree)
{
    bool b = true;
    bool havetransform = false;
    XMLElement *child = group->FirstChildElement();
    while(b)
    {
        b = child;
        if(b)
        {
            if(std::string(child->Value()) == "transform")
            {
                trataTransform(child,tree);
                havetransform = true;
            }
            else if (std::string(child->Value()) == "models")
            {
                if(!havetransform)
                {
                    tree->addNode(new Transform());
                    tree->openLevel();
                }
                trataModels(child,tree);
            }
            else if(std::string(child->Value()) == "group")
            {
                if(tree->empty())
                    tree->emptyNode();
                trataGrupo(child,tree);
                tree->closeLevel();
            }
            child = child->NextSiblingElement();
        }
    }
}

void trataCamara(XMLElement *camera, float *px, float *py, float *pz, float *lx, float *ly, float *lz, float *cx,float *cy, float *cz , float *fov, float *near, float*far)
{
    if (camera != nullptr)
    {
        XMLElement *position = camera->FirstChildElement("position");
        if (position != nullptr)
        {
            *px = std::stof(position->Attribute("x"));
            *py = std::stof(position->Attribute("y"));
            *pz = std::stof(position->Attribute("z"));
            //printf("Position: x=%d y=%d z=%d\n",px,py,pz);
        }
        XMLElement *lookAt = camera->FirstChildElement("lookAt");
        if (lookAt != nullptr)
        {
            *lx = std::stof(lookAt->Attribute("x"));
            *ly = std::stof(lookAt->Attribute("y"));
            *lz = std::stof(lookAt->Attribute("z"));
            //printf("LookAt: x=%d y=%d z=%d\n",lx,ly,lz);
        }
        XMLElement *up = camera->FirstChildElement("up");
        if (up != nullptr)
        {
            *cx = std::stof(up->Attribute("x"));
            *cy = std::stof(up->Attribute("y"));
            *cz = std::stof(up->Attribute("z"));
            //printf("Up: x=%d y=%d z=%d\n",cx,cy,cz);
        }
        XMLElement *projection = camera->FirstChildElement("projection");
        if (position != nullptr)
        {
            *fov = std::stof(projection->Attribute("fov"));
            *near = std::stof(projection->Attribute("near"));
            *far = std::stof(projection->Attribute("far"));
            //printf("Projection: fov=%d near=%d far=%d\n",fov,near,far);
        }
    }
}

void trataWindow(XMLElement *window, float *width, float*height)
{
    if (window != nullptr)
    {
        *width = std::stof(window->Attribute("width"));
        *height = std::stof(window->Attribute("height"));
        //printf("Window: width=%d height=%d\n",width,height);
    }
}

void trataLuzes(XMLElement *luzes, std::vector<Lights*> *ligths)
{
    XMLElement *child = luzes->FirstChildElement();
    GLenum luzesGLenum[8] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};
    int i = 0;
    while(child)
    {
        Lights *add;
        auto *vetor = new std::vector<float>();
        std::string type = child->Attribute("type");
        if(type == "point")
        {
            float posx = std::stof(child->Attribute("posx"));
            float posy = std::stof(child->Attribute("posy"));
            float posz = std::stof(child->Attribute("posz"));
            vetor->push_back(posx);
            vetor->push_back(posy);
            vetor->push_back(posz);
            add = new Lights(Lights::point,luzesGLenum[i],vetor);
        }
        else if (type == "directional")
        {
            float dirx = std::stof(child->Attribute("dirx"));
            float diry = std::stof(child->Attribute("diry"));
            float dirz = std::stof(child->Attribute("dirz"));
            vetor->push_back(dirx);
            vetor->push_back(diry);
            vetor->push_back(dirz);
            add = new Lights(Lights::directional,luzesGLenum[i],vetor);
        }
        else
        {
            float posx = std::stof(child->Attribute("posx"));
            float posy = std::stof(child->Attribute("posy"));
            float posz = std::stof(child->Attribute("posz"));
            float dirx = std::stof(child->Attribute("dirx"));
            float diry = std::stof(child->Attribute("diry"));
            float dirz = std::stof(child->Attribute("dirz"));
            float cutoff = std::stof(child->Attribute("cutoff"));
            vetor->push_back(posx);
            vetor->push_back(posy);
            vetor->push_back(posz);
            vetor->push_back(dirx);
            vetor->push_back(diry);
            vetor->push_back(dirz);
            vetor->push_back(cutoff);
            add = new Lights(Lights::spotlight,luzesGLenum[i],vetor);
        }
        i++;
        // delete vetor;
        ligths->push_back(add);
        child = child->NextSiblingElement();
    }
}

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        auto *tree = new ListTree();
        std::string name = argv[1];
        XMLDocument doc;
        doc.LoadFile((name).c_str());
        XMLElement *pRootElement = doc.RootElement();
        float width = 0, height = 0, px = 0, py = 0,pz = 0,lx = 0,ly = 0,lz = 0, cx = 0,cy=0,cz=0, fov=0, near=0, far = 0;
        auto *ligths = new std::vector<Lights*>();
        if (pRootElement != nullptr)
        {
            XMLElement *window = pRootElement->FirstChildElement("window");
            trataWindow(window,&width,&height);
            XMLElement *camera = pRootElement->FirstChildElement("camera");
            trataCamara(camera,&px,&py,&pz,&lx,&ly,&lz,&cx,&cy,&cz,&fov,&near,&far);
            XMLElement *luzes = pRootElement->FirstChildElement("lights");
            trataLuzes(luzes,ligths);
            XMLElement *group = pRootElement->FirstChildElement("group");
            trataGrupo(group,tree);
        }
        doc.Clear();
        auto *w = new World(width,height,px,py,pz,lx,ly,lz,cx,cy,cz,fov,near,far,tree,ligths);
        printf("%s\n",w->toString().c_str());
        w->drawWorld();
        delete w;
    }
    else
        printf("Invalid arguments");
    return 0;
}