#ifndef PROJETOEXEC_WORLD_H
#define PROJETOEXEC_WORLD_H

#include <cstdio>
#include <string>

class Camera;
class Group;

class World{
public:
    float width;
    float height;
    Camera *camera;
    Group *group;
    World(float , float, float, float, float, float, float, float, float, float, float, float, float, float);
    void addModel(const std::string&);
    std::string toString();
    ~World();
    void drawWorld();
    static World *instance;
};

#endif