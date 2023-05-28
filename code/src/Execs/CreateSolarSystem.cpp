#include "../TinyXML/tinyxml2.h"
#include <string>
#include <utility>
#include <vector>

tinyxml2::XMLDocument doc;
std::string modelsphre = "../files/sphere.3d";
std::string modeldonut = "../files/donut.3d";
std::string modelComet = "../files/teapot.3d";

tinyxml2::XMLElement* GenerateCatmullRomCircle(float radius,float time) {
    float raux = radius*0.75*0.55;
    float p[8][3] = {
            {-radius/2,0,0},
            {-raux,0,raux},
            {0,0,radius},
            {raux,0,raux},
            {radius/2,0,0},
            {raux,0,-raux},
            {0,0,-radius},
            {-raux,0,-raux}
    };
    tinyxml2::XMLElement* orbita = doc.NewElement("translate");
    orbita->SetAttribute("time",time);
    orbita->SetAttribute("align","True");
    for(int i = 0; i < 8; i++)
    {
        tinyxml2::XMLElement* ponto1 = doc.NewElement("point");
        ponto1->SetAttribute("x",p[i][0]);
        ponto1->SetAttribute("y",p[i][1]);
        ponto1->SetAttribute("z",p[i][2]);
        orbita->InsertEndChild(ponto1);
    }
    return orbita;
}
tinyxml2::XMLElement* GenerateCatmullRomCircleTransform(float radius,float time) {
    tinyxml2::XMLElement* transform = doc.NewElement("transform");
    tinyxml2::XMLElement* orbita = GenerateCatmullRomCircle(radius,time);
    transform->InsertEndChild(orbita);
    return transform;
}

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
    int cx = 600, cy = 600, cz = 600;
    int lx = 0, ly = 0, lz = 0;
    int ux = 0, uy = 1, uz = 0;
    int fov = 60, near = 1, far = 1750;
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


tinyxml2::XMLElement* createLightPoint(float x, float y, float z)
{
    tinyxml2::XMLElement* light = doc.NewElement("light");
    light->SetAttribute("type","point");
    light->SetAttribute("posx",x);
    light->SetAttribute("posy",y);
    light->SetAttribute("posz",z);
    return light;
}


tinyxml2::XMLElement* createLightDir(float x, float y, float z)
{
    tinyxml2::XMLElement* light = doc.NewElement("light");
    light->SetAttribute("type","directional");
    light->SetAttribute("dirx",x);
    light->SetAttribute("diry",y);
    light->SetAttribute("dirz",z);
    return light;
}

tinyxml2::XMLElement* createLightSL(float x, float y, float z,float dx,float dy,float dz, float co)
{
    tinyxml2::XMLElement* light = doc.NewElement("light");
    light->SetAttribute("type","spotlight");
    light->SetAttribute("posx",x);
    light->SetAttribute("posy",y);
    light->SetAttribute("posz",z);
    light->SetAttribute("dirx",dx);
    light->SetAttribute("diry",dy);
    light->SetAttribute("dirz",dz);
    light->SetAttribute("cutoff",co);
    return light;
}



tinyxml2::XMLElement* createLight()
{
    tinyxml2::XMLElement* lights = doc.NewElement("lights");
    float aux = 120;
    tinyxml2::XMLElement* light0 = createLightPoint(0,0,0);

    tinyxml2::XMLElement* light1 = createLightSL(aux,0,0,-aux,0,0,90);
    tinyxml2::XMLElement* light2 = createLightSL(0,aux,0,0,-aux,0,90);
    tinyxml2::XMLElement* light3 = createLightSL(0,0,aux,0,0,-aux,90);
    tinyxml2::XMLElement* light4 = createLightSL(-aux,0,0,aux,0,0,90);
    tinyxml2::XMLElement* light5 = createLightSL(0,-aux,0,0,aux,0,90);
    tinyxml2::XMLElement* light6 = createLightSL(0,0,-aux,0,0,aux,90);
    lights->InsertEndChild(light0);
    lights->InsertEndChild(light1);
    lights->InsertEndChild(light2);
    lights->InsertEndChild(light3);
    lights->InsertEndChild(light4);
    lights->InsertEndChild(light5);
    lights->InsertEndChild(light6);
    return lights;
}

tinyxml2::XMLElement* createTransform(const std::vector<std::string>& transformations, float sx, float sy, float sz, int tx, int ty, int tz, int angle, int rx, int ry, int rz, bool time)
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
            if(time)
                rotate->SetAttribute("time",angle);
            else
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

tinyxml2::XMLElement* createTexture(std::string elemento)
{
    tinyxml2::XMLElement* texture = doc.NewElement("texture");
    std::string name = "../images/"+elemento + ".jpg";
    texture->SetAttribute("file",name.c_str());
    return texture;
}

tinyxml2::XMLElement* createColor(std::string elemento)
{
    tinyxml2::XMLElement* color = doc.NewElement("color");
    tinyxml2::XMLElement* diffuse = doc.NewElement("diffuse");
    if(elemento == "Sol")
    {
        diffuse->SetAttribute("R",254);
        diffuse->SetAttribute("G",221);
        diffuse->SetAttribute("B",0);
    }
    else if (elemento == "Moon" || elemento == "Cometa" || elemento == "Mercurio")
    {
        diffuse->SetAttribute("R",100);
        diffuse->SetAttribute("G",100);
        diffuse->SetAttribute("B",100);
    }
    else if ( elemento == "Terra" || elemento == "Urano" || elemento == "Neptuno")
    {
        diffuse->SetAttribute("R",0);
        diffuse->SetAttribute("G",0);
        diffuse->SetAttribute("B",100);
    }
    else if(elemento == "Marte")
    {
        diffuse->SetAttribute("R",100);
        diffuse->SetAttribute("G",0);
        diffuse->SetAttribute("B",0);
    }
    else if(elemento == "Jupiter" || elemento == "Saturno" || elemento == "Venus")
    {
        diffuse->SetAttribute("R",154);
        diffuse->SetAttribute("G",121);
        diffuse->SetAttribute("B",0);
    }
    tinyxml2::XMLElement* ambient = doc.NewElement("ambient");
    ambient->SetAttribute("R",0);
    ambient->SetAttribute("G",0);
    ambient->SetAttribute("B",0);
    tinyxml2::XMLElement* specular = doc.NewElement("specular");
    specular->SetAttribute("R",0);
    specular->SetAttribute("G",0);
    specular->SetAttribute("B",0);
    tinyxml2::XMLElement* emissive = doc.NewElement("emissive");
    if(elemento == "Sol")
    {
        emissive->SetAttribute("R",254);
        emissive->SetAttribute("G",221);
        emissive->SetAttribute("B",0);
    }
    else
    {
        emissive->SetAttribute("R",0);
        emissive->SetAttribute("G",0);
        emissive->SetAttribute("B",0);

    }
    tinyxml2::XMLElement* shininess = doc.NewElement("shininess");
    shininess->SetAttribute("value",0);
    color->InsertEndChild(diffuse);
    color->InsertEndChild(ambient);
    color->InsertEndChild(specular);
    color->InsertEndChild(emissive);
    color->InsertEndChild(shininess);
    return color;
}

tinyxml2::XMLElement* createModel(std::string name,std::string namefiletexture)
{
    tinyxml2::XMLComment* comment = doc.NewComment(("generator sphere 1 15 15 ../files/sphere.3d " + name).c_str());
    tinyxml2::XMLElement* models = doc.NewElement("models");
    tinyxml2::XMLElement* planet = doc.NewElement("model");
    planet->SetAttribute("file", modelsphre.c_str());
    planet->LinkEndChild(comment);
    planet->InsertEndChild(createTexture(std::move(namefiletexture)));
    planet->InsertEndChild(createColor(name));
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
    t2.emplace_back("rotate");
    t2.emplace_back("translate");
    t2.emplace_back("scale");
    tinyxml2::XMLElement *moon = doc.NewElement("group");
    tinyxml2::XMLElement* moonTransform = createTransform(t2,std::abs(sx/4),std::abs(sy/4),std::abs(sz/4),sx * 1.3,sy * 1.3, sz *1.3,sx*10,0,1,0,
                                                          true);
    // moonTransform->InsertEndChild(GenerateCatmullRomCircle(3*sx/4,100));
    moon->InsertEndChild(moonTransform);
    moon->InsertEndChild(createModel("Moon","moon"));
    return moon;
}

tinyxml2::XMLElement* createAnel(std::string planet)
{
    std::vector<std::string> scaleVector = std::vector<std::string>();
    scaleVector.emplace_back("scale");
    tinyxml2::XMLElement* group = doc.NewElement("group");
    tinyxml2::XMLElement* scale = createTransform(scaleVector,1,0.01f,1,0,0,0,0,0,0,0,true);
    tinyxml2::XMLElement* models = doc.NewElement("models");
    tinyxml2::XMLElement* anel = doc.NewElement("model");
    tinyxml2::XMLComment* comment = doc.NewComment("generator donut 1.5 1.75 15 5 ../files/donut.3d");
    anel->SetAttribute("file", modeldonut.c_str());
    anel->LinkEndChild(comment);
    anel->InsertEndChild(createTexture(planet+ "ring"));
    anel->InsertEndChild(createColor("Moon"));
    models->InsertEndChild(anel);
    group->InsertEndChild(scale);
    group->InsertEndChild(models);
    return group;
}

void createComets(float tx,tinyxml2::XMLElement*planets)
{
    float t = tx-30;
    float time = 5;
    for(int i = 0; i < 7; i++)
    {
        tinyxml2::XMLElement* transform = GenerateCatmullRomCircleTransform(t,time);
        t+=3;
        tinyxml2::XMLElement* group = doc.NewElement("group");
        tinyxml2::XMLElement* models = doc.NewElement("models");
        tinyxml2::XMLElement* model = doc.NewElement("model");
        tinyxml2::XMLComment* comment = doc.NewComment("generator patch ../teapot.patch 10 ../files/teapot.3d");
        model->SetAttribute("file", modelComet.c_str());
        model->LinkEndChild(comment);
        model->InsertEndChild(createTexture("moon"));
        model->InsertEndChild(createColor("Cometa"));
        models->InsertEndChild(model);
        group->InsertEndChild(transform);
        group->InsertEndChild(models);
        planets->InsertEndChild(group);
        time +=2;
    }
}

tinyxml2::XMLElement* createWorld()
{
    std::vector<float> scales = planetScales();
    std::vector<std::string> t1 = std::vector<std::string>();
    t1.emplace_back("rotate");
    std::vector<std::string> t2 = std::vector<std::string>();
    t2.emplace_back("rotate");
    t2.emplace_back("translate");
    t2.emplace_back("scale");
    std::vector<std::string> t3 = std::vector<std::string>();
    t3.emplace_back("translate");
    t3.emplace_back("rotate");
    t3.emplace_back("scale");
    std::vector<std::string> t4 = std::vector<std::string>();
    t4.emplace_back("rotate");
    t4.emplace_back("translate");
    t4.emplace_back("rotate");
    std::vector<std::string> t5 = std::vector<std::string>();
    t5.emplace_back("scale");
    std::vector<std::string> t6 = std::vector<std::string>();
    t6.emplace_back("rotate");
    t6.emplace_back("scale");
    tinyxml2::XMLElement* mainGroup = doc.NewElement("group");
    tinyxml2::XMLElement* sun = doc.NewElement("group");
    tinyxml2::XMLElement* planets = doc.NewElement("group");
    sun->InsertEndChild(createTransform(t2,50,50,50,0,0,0,10,0,1,0, true));
    sun->InsertEndChild(createModel("Sol","sun"));
    mainGroup->InsertEndChild(sun);
    mainGroup->InsertEndChild(planets);
    int j = 0;
    int tx = 60, tz = 60,ty = 0;
    int time = 5;
    std::string planetas[8] = {"Mercurio", "Venus", "Terra", "Marte", "Jupiter", "Saturno", "Urano", "Neptuno"};
    std::string names[8] = {"mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"};
    for(int i = 1; i < 9; i++)
    {
        // tinyxml2::XMLElement* transform = createTransform(t1,0,0,0,0,0,0,time,0,1,0);

        tinyxml2::XMLElement* planetGroup = doc.NewElement("group");
        // planetGroup->InsertEndChild(GenerateCatmullRomCircleTransform(tx,10));
        tinyxml2::XMLElement* planetGroupTranslate = createTransform(t4,0,0,0,tx,ty,tz,time,0,1,0,true);
        time += 2;
        tinyxml2::XMLElement* planetTransform;
        if(i!= 7)
            planetTransform = createTransform(t5,scales[j],scales[j+1],scales[j+2],0,0,0,0,0,0,0, true);
        else
            planetTransform = createTransform(t6,scales[j],scales[j+1],scales[j+2],0,0,0,90,0,0,1, false);

        tinyxml2::XMLElement *planet = doc.NewElement("group");
        tinyxml2::XMLElement* planetModel = createModel(planetas[i-1],names[i-1]);

        planet->InsertEndChild(planetTransform);
        planet->InsertEndChild(planetModel);
        if(i == 6 || i == 7)
            planet->InsertEndChild(createAnel(names[i-1]));

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
        //planets->InsertEndChild(transform);
        planets->InsertEndChild(planetGroup);
        if(i < 8)
        {
            tinyxml2::XMLElement* otherPlanets = doc.NewElement("group");
            planets->InsertEndChild(otherPlanets);
            planets = otherPlanets;
        }
        if(i == 4)
        {
            tx+=70;
            tz+=70;
            createComets(tx,planets);
        }
        else
        {
            tx+=50;
            tz+=50;
        }
        j+=3;
    }
    return mainGroup;
}

int main()
{
    tinyxml2::XMLElement* world = doc.NewElement("world");
    doc.InsertEndChild(world);
    world->InsertEndChild(createWindow());
    world->InsertEndChild(createCamera());
    world->InsertEndChild(createLight());
    world->InsertEndChild(createWorld());
    doc.SaveFile("../xmlFiles/sistemasolar.xml");
    return 0;
}