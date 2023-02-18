#include <string>

class Camera{
public:
    Camera(int,int,int,int,int,int,int,int,int,int,int,int);
    int posx;
    int posy;
    int posz;
    int lax;
    int lay;
    int laz;
    int upx;
    int upy;
    int upz;
    int profov;
    int pronear;
    int profar;
    std::string toString() const;
};
