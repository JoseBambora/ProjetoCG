#include <string>
#include <cstdio>
#include <list>
#include <regex>
#include "../TinyXML/tinyxml2.h"
#include "../Classes/EngineClasses/Header/World.h"
#include "../Classes/EngineClasses/Header/ListTree.h"
#include "../Classes/Transformations/Header/Transformation.h"
#include "../Classes/Transformations/Header/Rotate.h"
#include "../Classes/Transformations/Header/Scale.h"
#include "../Classes/Transformations/Header/Translate.h"
#include "../Classes/Transformations/Header/Transform.h"
#include "../Classes/Figures/Header/Figure.h"
#include "../Classes/EngineClasses/Header/CatmullRom.h"
const std::string dir = "../../files/";

using namespace tinyxml2;

void trataModels(XMLElement *models , ListTree * tree)
{
    XMLElement *model = models->FirstChildElement("model");
    while (model)
    {
        std::string nameFile = model->Attribute("file");
        Figure *figura = Figure::ReadFile(nameFile);
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
                    printf("entrou\n");
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
    XMLElement *child = group->FirstChildElement();
    while(b)
    {
        b = child;
        if(b)
        {
            if(std::string(child->Value()) == "transform")
                trataTransform(child,tree);
            else if (std::string(child->Value()) == "models")
                trataModels(child,tree);
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
        if (pRootElement != nullptr)
        {
            XMLElement *window = pRootElement->FirstChildElement("window");
            trataWindow(window,&width,&height);
            XMLElement *camera = pRootElement->FirstChildElement("camera");
            trataCamara(camera,&px,&py,&pz,&lx,&ly,&lz,&cx,&cy,&cz,&fov,&near,&far);
            XMLElement *group = pRootElement->FirstChildElement("group");
            trataGrupo(group,tree);
        }
        doc.Clear();
        printf("%s\n",tree->toString().c_str());
        auto *w = new World(width,height,px,py,pz,lx,ly,lz,cx,cy,cz,fov,near,far,tree);
        printf("%s\n",w->toString().c_str());
        w->drawWorld();
        delete w;
    }
    else
        printf("Invalid arguments");
    return 0;
}