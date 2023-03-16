#ifndef PROJETOEXEC_WORLD_H
#define PROJETOEXEC_WORLD_H

#include <cstdio>
#include <string>

class Camera;
class Group;
class ListTree;
class World{
public:
    float width;
    float height;
    Camera *camera;
    Group *group;
    World(float , float, float, float, float, float, float, float, float, float, float, float, float, float, ListTree*);
    std::string toString();
    ~World();
    void drawWorld();
    static World *instance;
};

#endif