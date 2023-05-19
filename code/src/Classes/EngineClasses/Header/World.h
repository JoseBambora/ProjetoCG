#ifndef PROJETOEXEC_WORLD_H
#define PROJETOEXEC_WORLD_H

#include <cstdio>
#include <string>
#include <vector>
class Camera;
class Group;
class ListTree;
class Lights;

class World{
public:
    float width;
    float height;
    Camera *camera;
    Group *group;
    std::vector<Lights*> *ligths;
    World(float , float, float, float, float, float, float, float, float, float, float, float, float, float, ListTree*,std::vector<Lights*> *);
    std::string toString();
    ~World();
    void drawWorld();
    static World *instance;
};

#endif