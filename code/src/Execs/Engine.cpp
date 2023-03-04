#include <string>
#include <cstdio>
#include <list>
#include "../TinyXML/tinyxml2.h"
#include "../Classes/EngineClasses/Header/World.h"
const std::string dir = "../../files/";

using namespace tinyxml2;

int main(int argc, char** argv)
{
    if(argc == 2)
    {
        std::string name = argv[1];
        XMLDocument doc;
        doc.LoadFile((name).c_str());
        XMLElement *pRootElement = doc.RootElement();
        float width = 0, height = 0, px = 0, py = 0,pz = 0,lx = 0,ly = 0,lz = 0, cx = 0,cy=0,cz=0, fov=0, near=0, far = 0;
        std::list<std::string> modelsList = std::list<std::string>();
        if (pRootElement != nullptr)
        {
            XMLElement *window = pRootElement->FirstChildElement("window");
            if (window != nullptr)
            {
                width = std::stof(window->Attribute("width"));
                height = std::stof(window->Attribute("height"));
                //printf("Window: width=%d height=%d\n",width,height);
            }
            XMLElement *camera = pRootElement->FirstChildElement("camera");
            if (camera != nullptr)
            {
                XMLElement *position = camera->FirstChildElement("position");
                if (position != nullptr)
                {
                    px = std::stof(position->Attribute("x"));
                    py = std::stof(position->Attribute("y"));
                    pz = std::stof(position->Attribute("z"));
                    //printf("Position: x=%d y=%d z=%d\n",px,py,pz);
                }
                XMLElement *lookAt = camera->FirstChildElement("lookAt");
                if (lookAt != nullptr)
                {
                    lx = std::stof(lookAt->Attribute("x"));
                    ly = std::stof(lookAt->Attribute("y"));
                    lz = std::stof(lookAt->Attribute("z"));
                    //printf("LookAt: x=%d y=%d z=%d\n",lx,ly,lz);
                }
                XMLElement *up = camera->FirstChildElement("up");
                if (up != nullptr)
                {
                    cx = std::stof(up->Attribute("x"));
                    cy = std::stof(up->Attribute("y"));
                    cz = std::stof(up->Attribute("z"));
                    //printf("Up: x=%d y=%d z=%d\n",cx,cy,cz);
                }
                XMLElement *projection = camera->FirstChildElement("projection");
                if (position != nullptr)
                {
                    fov = std::stof(projection->Attribute("fov"));
                    near = std::stof(projection->Attribute("near"));
                    far = std::stof(projection->Attribute("far"));
                    //printf("Projection: fov=%d near=%d far=%d\n",fov,near,far);
                }
            }
            XMLElement *group = pRootElement->FirstChildElement("group");
            if (group != nullptr)
            {
                XMLElement *models = group->FirstChildElement("models");
                if (models != nullptr)
                {
                    XMLElement *model = models->FirstChildElement("model");
                    while (model)
                    {
                        std::string nameFile = model->Attribute("file");
                        modelsList.push_back(nameFile);
                        model = model->NextSiblingElement("model");
                        //printf("Model: %s\n",nameFile.c_str());
                    }
                }
            }
        }
        auto *w = new World(width,height,px,py,pz,lx,ly,lz,cx,cy,cz,fov,near,far);
        for(const std::string& str : modelsList)
            w->addModel(str);
        printf("%s\n",w->toString().c_str());
        w->drawWorld();
        delete w;
    }
    else
        printf("Invalid arguments");
    return 0;
}