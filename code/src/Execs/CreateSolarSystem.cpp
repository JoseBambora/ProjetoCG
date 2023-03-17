#include "../TinyXML/tinyxml2.h"
#include <string>
#include <vector>

tinyxml2::XMLDocument doc;
std::string modelsphre = "../files/sphere.3d";
std::string modeldonut = "../files/donut.3d";

tinyxml2::XMLElement* createWindow()
{
    int width = 1000, height = 1000;
    tinyxml2::XMLElement* window = doc.NewElement("window");
    window->SetAttribute("width",width);
    window->SetAttribute("height",height);
    return window;
}

tinyxml2::XMLElement* createCamera()
{
    int cx = -120, cy = 120, cz = 120;
    int lx = 0, ly = 0, lz = 0;
    int ux = 0, uy = 1, uz = 0;
    int fov = 60, near = 1, far = 1000;
    tinyxml2::XMLElement* camera = doc.NewElement("camera");
    tinyxml2::XMLElement* position = doc.NewElement("position");
    tinyxml2::XMLElement* lookat = doc.NewElement("lookat");
    tinyxml2::XMLElement* up = doc.NewElement("up");
    tinyxml2::XMLElement* projection = doc.NewElement("projection");

    position->SetAttribute("x",cx);
    position->SetAttribute("y",cy);
    position->SetAttribute("z",cz);
    lookat->SetAttribute("x",lx);
    lookat->SetAttribute("y",ly);
    lookat->SetAttribute("z",lz);
    up->SetAttribute("x",ux);
    up->SetAttribute("y",uy);
    up->SetAttribute("z",uz);
    projection->SetAttribute("fov",fov);
    projection->SetAttribute("near",near);
    projection->SetAttribute("far",far);

    camera->InsertEndChild(position);
    camera->InsertEndChild(lookat);
    camera->InsertEndChild(up);
    camera->InsertEndChild(projection);
    return camera;
}

tinyxml2::XMLElement* createTransform(const std::vector<std::string>& transformations, int sx, int sy, int sz, int tx, int ty, int tz)
{
    int angle = 50, rx = 0, ry = 1, rz = 0;
    tinyxml2::XMLElement* transform = doc.NewElement("transform");
    for(const std::string& t : transformations)
    {
        if(t == "translate")
        {
            tinyxml2::XMLElement* translate = doc.NewElement("translate");
            translate->SetAttribute("x",tx);
            translate->SetAttribute("y",ty);
            translate->SetAttribute("z",tz);
            transform->InsertEndChild(translate);
        }
        else if(t == "rotate")
        {
            tinyxml2::XMLElement* rotate = doc.NewElement("rotate");
            rotate->SetAttribute("angle",angle);
            rotate->SetAttribute("x",rx);
            rotate->SetAttribute("y",ry);
            rotate->SetAttribute("z",rz);
            transform->InsertEndChild(rotate);
        }
        else if(t == "scale")
        {
            tinyxml2::XMLElement* scale = doc.NewElement("scale");
            scale->SetAttribute("x",sx);
            scale->SetAttribute("y",sy);
            scale->SetAttribute("z",sz);
            transform->InsertEndChild(scale);
        }
    }
    return transform;
}

tinyxml2::XMLElement* createModel(bool saturno)
{
    tinyxml2::XMLComment* comment = doc.NewComment("generator sphere 1 15 15 ../files/sphere.3d");
    tinyxml2::XMLElement* models = doc.NewElement("models");
    tinyxml2::XMLElement* planet = doc.NewElement("model");
    planet->SetAttribute("file", modelsphre.c_str());
    planet->LinkEndChild(comment);
    models->InsertEndChild(planet);
    if(saturno)
    {
        tinyxml2::XMLElement* anel = doc.NewElement("model");
        comment = doc.NewComment("generator donut 1.5 1.75 15 5 ../files/donut.3d");
        anel->SetAttribute("file", modeldonut.c_str());
        anel->LinkEndChild(comment);
        models->InsertEndChild(anel);
    }
    return models;
}

std::vector<int> planetScales()
{
    std::vector<int> scales = std::vector<int>();
    // Mercury
    scales.push_back(1); scales.push_back(1); scales.push_back(1);
    // Venus
    scales.push_back(3); scales.push_back(3); scales.push_back(3);
    // Earth
    scales.push_back(4); scales.push_back(4); scales.push_back(4);
    // Venus
    scales.push_back(2); scales.push_back(2); scales.push_back(2);
    // Jupiter
    scales.push_back(8); scales.push_back(8); scales.push_back(8);
    // Saturn
    scales.push_back(7); scales.push_back(7); scales.push_back(7);
    // Uranus
    scales.push_back(5); scales.push_back(5); scales.push_back(5);
    // Neptune
    scales.push_back(6); scales.push_back(6); scales.push_back(6);
    return scales;
}

tinyxml2::XMLElement* createWorld()
{
    std::vector<int> scales = planetScales();
    std::vector<std::string> t1 = std::vector<std::string>();
    t1.emplace_back("rotate");
    std::vector<std::string> t2 = std::vector<std::string>();
    t2.emplace_back("translate");
    t2.emplace_back("scale");
    tinyxml2::XMLElement* mainGroup = doc.NewElement("group");
    tinyxml2::XMLElement* sun = doc.NewElement("group");
    tinyxml2::XMLElement* planets = doc.NewElement("group");
    sun->InsertEndChild(createTransform(t2,10,10,10,0,0,0));
    sun->InsertEndChild(createModel(false));
    mainGroup->InsertEndChild(sun);
    mainGroup->InsertEndChild(planets);
    int j = 0;
    int tx = 15, tz = 15,ty = 0;
    for(int i = 1; i < 9; i++)
    {
        tinyxml2::XMLElement* transform = createTransform(t1,0,0,0,0,0,0);
        tinyxml2::XMLElement* planet = doc.NewElement("group");
        tinyxml2::XMLElement* planetTransform = createTransform(t2,scales[j],scales[j+1],scales[j+2],tx,ty,tz);
        tinyxml2::XMLElement* planetModel = createModel(i == 6);
        planet->InsertEndChild(planetTransform);
        planet->InsertEndChild(planetModel);
        planets->InsertEndChild(transform);
        planets->InsertEndChild(planet);
        if(i < 8)
        {
            tinyxml2::XMLElement* otherPlanets = doc.NewElement("group");
            planets->InsertEndChild(otherPlanets);
            planets = otherPlanets;
        }
        j+=3;
        tx+=15;
        tz+=15;
    }
    return mainGroup;
}

int main()
{
    tinyxml2::XMLElement* world = doc.NewElement("world");
    doc.InsertEndChild(world);
    world->InsertEndChild(createWindow());
    world->InsertEndChild(createCamera());
    world->InsertEndChild(createWorld());
    doc.SaveFile("../xmlFiles/SolarSystemEx.xml");
    return 0;
}