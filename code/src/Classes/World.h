#include "Camera.h"
#include "Group.h"
class World{
public:
    int width;
    int height;
    Camera camera;
    Group group;
    World(int, int, int, int, int, int, int, int, int, int, int, int, int, int);
    void addModel(std::string);
    std::string toString();
};