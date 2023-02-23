#ifndef PROJETOEXEC_WORLD_H
#define PROJETOEXEC_WORLD_H

#include <cstdio>
#include <string>

class Camera;
class Group;

class World{
public:
    int width;
    int height;
    Camera *camera;
    Group *group;
    World(int, int, int, int, int, int, int, int, int, int, int, int, int, int);
    void addModel(const std::string&);
    std::string toString();
    ~World();
};

#endif