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

tinyxml2::XMLElement* createTransform(const std::vector<std::string>& transformations, float sx, float sy, float sz, int tx, int ty, int tz, int angle, int rx, int ry, int rz)
{
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

tinyxml2::XMLElement* createModel()
{
    tinyxml2::XMLComment* comment = doc.NewComment("generator sphere 1 15 15 ../files/sphere.3d");
    tinyxml2::XMLElement* models = doc.NewElement("models");
    tinyxml2::XMLElement* planet = doc.NewElement("model");
    planet->SetAttribute("file", modelsphre.c_str());
    planet->LinkEndChild(comment);
    models->InsertEndChild(planet);
    return models;
}

std::vector<float> planetScales()
{
    // 0.383    0.949    1    0.2724    0.532    11.21    9.45    4.01    3.88
    std::vector<float> scales = std::vector<float>();
    // Mercury
    scales.push_back(1); scales.push_back(1); scales.push_back(1);
    // Venus
    scales.push_back(3); scales.push_back(3); scales.push_back(3);
    // Earth
    scales.push_back(4); scales.push_back(4); scales.push_back(4);
    // Mars
    scales.push_back(2); scales.push_back(2); scales.push_back(2);
    // Jupiter
    scales.push_back(11.21f); scales.push_back(11.21f); scales.push_back(11.21f);
    // Saturn
    scales.push_back(9.45f); scales.push_back(9.45f); scales.push_back(9.45f);
    // Uranus
    scales.push_back(6); scales.push_back(6); scales.push_back(6);
    // Neptune
    scales.push_back(5); scales.push_back(5); scales.push_back(5);
    return scales;
}

tinyxml2::XMLElement* createMoon(float sx, float sy, float sz)
{
    std::vector<std::string> t2 = std::vector<std::string>();
    t2.emplace_back("translate");
    t2.emplace_back("scale");
    tinyxml2::XMLElement *moon = doc.NewElement("group");
    tinyxml2::XMLElement* moonTransform = createTransform(t2,std::abs(sx/4),std::abs(sy/4),std::abs(sz/4),(int) sx + 3,(int) sy + 3,(int) sz + 3,0,0,0,0);
    moon->InsertEndChild(moonTransform);
    moon->InsertEndChild(createModel());
    return moon;
}

tinyxml2::XMLElement* createAnel()
{
    std::vector<std::string> scaleVector = std::vector<std::string>();
    scaleVector.emplace_back("scale");
    tinyxml2::XMLElement* group = doc.NewElement("group");
    tinyxml2::XMLElement* scale = createTransform(scaleVector,1,0.01f,1,0,0,0,0,0,0,0);
    tinyxml2::XMLElement* models = doc.NewElement("models");
    tinyxml2::XMLElement* anel = doc.NewElement("model");
    tinyxml2::XMLComment* comment = doc.NewComment("generator donut 1.5 1.75 15 5 ../files/donut.3d");
    anel->SetAttribute("file", modeldonut.c_str());
    anel->LinkEndChild(comment);
    models->InsertEndChild(anel);
    group->InsertEndChild(scale);
    group->InsertEndChild(models);
    return group;
}

tinyxml2::XMLElement* createWorld()
{
    std::vector<float> scales = planetScales();
    std::vector<std::string> t1 = std::vector<std::string>();
    t1.emplace_back("rotate");
    std::vector<std::string> t2 = std::vector<std::string>();
    t2.emplace_back("translate");
    t2.emplace_back("scale");
    std::vector<std::string> t3 = std::vector<std::string>();
    t3.emplace_back("translate");
    t3.emplace_back("rotate");
    t3.emplace_back("scale");
    std::vector<std::string> t4 = std::vector<std::string>();
    t4.emplace_back("translate");
    std::vector<std::string> t5 = std::vector<std::string>();
    t5.emplace_back("scale");
    std::vector<std::string> t6 = std::vector<std::string>();
    t6.emplace_back("rotate");
    t6.emplace_back("scale");
    tinyxml2::XMLElement* mainGroup = doc.NewElement("group");
    tinyxml2::XMLElement* sun = doc.NewElement("group");
    tinyxml2::XMLElement* planets = doc.NewElement("group");
    sun->InsertEndChild(createTransform(t2,50,50,50,0,0,0,0,0,0,0));
    sun->InsertEndChild(createModel());
    mainGroup->InsertEndChild(sun);
    mainGroup->InsertEndChild(planets);
    int j = 0;
    int tx = 60, tz = 60,ty = 0;
    for(int i = 1; i < 9; i++)
    {
        tinyxml2::XMLElement* transform = createTransform(t1,0,0,0,0,0,0,50,0,1,0);

        tinyxml2::XMLElement* planetGroup = doc.NewElement("group");
        tinyxml2::XMLElement* planetGroupTranslate = createTransform(t4,0,0,0,tx,ty,tz,0,0,0,0);

        tinyxml2::XMLElement* planetTransform;
        if(i!= 7)
            planetTransform = createTransform(t5,scales[j],scales[j+1],scales[j+2],0,0,0,0,0,0,0);
        else
            planetTransform = createTransform(t6,scales[j],scales[j+1],scales[j+2],0,0,0,90,0,0,1);

        tinyxml2::XMLElement *planet = doc.NewElement("group");
        tinyxml2::XMLElement* planetModel = createModel();

        planet->InsertEndChild(planetTransform);
        planet->InsertEndChild(planetModel);
        if(i == 6 || i == 7)
            planet->InsertEndChild(createAnel());

        planetGroup->InsertEndChild(planetGroupTranslate);
        if (i > 2)
        {
            float sx = scales[j];
            float sy = scales[j+1];
            float sz = scales[j+2];
            switch (i)
            {
                case 3:
                    planetGroup->InsertEndChild(createMoon(sx,sy,sz));
                    break;
                case 4:
                    planetGroup->InsertEndChild(createMoon(sx,sy,sz));
                    planetGroup->InsertEndChild(createMoon(-sx,sy,sz));
                    break;
                case 5:
                    planetGroup->InsertEndChild(createMoon(sx,sy,sz));
                    planetGroup->InsertEndChild(createMoon(-sx,-sy,sz));
                    planetGroup->InsertEndChild(createMoon(sx,sy,-sz));
                    planetGroup->InsertEndChild(createMoon(sx,-sy,sz));
                    planetGroup->InsertEndChild(createMoon(-sx,-sy,-sz));
                    break;
                case 6:
                    planetGroup->InsertEndChild(createMoon(sx,sy,sz));
                    planetGroup->InsertEndChild(createMoon(-sx,sy,-sz));
                    planetGroup->InsertEndChild(createMoon(sx,sy,-sz));
                    planetGroup->InsertEndChild(createMoon(sx,-sy,sz));
                    break;
                case 7:
                case 8:
                    planetGroup->InsertEndChild(createMoon(sx,-sy,sz));
                    planetGroup->InsertEndChild(createMoon(-sx,sy,sz));
                    planetGroup->InsertEndChild(createMoon(sx,sy,-sz));
                    break;
                default:
                    break;
            }
        }
        planetGroup->InsertEndChild(planet);
        planets->InsertEndChild(transform);
        planets->InsertEndChild(planetGroup);
        if(i < 8)
        {
            tinyxml2::XMLElement* otherPlanets = doc.NewElement("group");
            planets->InsertEndChild(otherPlanets);
            planets = otherPlanets;
        }
        j+=3;
        tx+=30;
        tz+=30;
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