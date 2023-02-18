#include "World.h"

#include <utility>

World::World(int width, int height,
             int posx, int posy, int posz,
             int lax, int lay, int laz,
             int upx, int upy,int upz,
             int fov, int near, int far) : camera(posx,posy,posz,lax,lay,laz,upx,upy,upz,fov,near,far) {
    this->width = width;
    this->height = height;
    this->group = Group();
}

void World::addModel(std::string model) {
    this->group.insertModel(std::move(model));
}

std::string World::toString()
{
    std::string res;
    res.append("Width: ");
    res.append(std::to_string(this->width));
    res.append("\nHeigth: ");
    res.append(std::to_string(this->height));
    res.append("\n");
    res.append(this->camera.toString());
    res.append(this->group.toString());
    return res;
}
