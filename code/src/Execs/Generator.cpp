#include <string>
#include <fstream>
#include <cstdio>
#include "../Classes/Figures/Box.h"
#include "../Classes/Figures/Sphere.h"
#include "../Classes/Figures/Cone.h"
#include "../Classes/Figures/Plane.h"
const std::string dir = "../files/";
void testeescrita()
{
    std::string name1 = dir + "box.3d";
    std::string name2 = dir + "cone.3d";
    std::string name3 = dir + "plane.3d";
    std::string name4 = dir + "sphere.3d";
    std::ifstream file1;
    std::ifstream file2;
    std::ifstream file3;
    std::ifstream file4;
    file1.open(name1, std::ios::binary);
    file2.open(name2, std::ios::binary);
    file3.open(name3, std::ios::binary);
    file4.open(name4, std::ios::binary);
    int cod1;
    file1.read((char *) &cod1, sizeof(cod1));
    file2.read((char *) &cod1, sizeof(cod1));
    file3.read((char *) &cod1, sizeof(cod1));
    file4.read((char *) &cod1, sizeof(cod1));
    Box b = Box();
    b.Read_File(std::move(file1));
    Cone c = Cone();
    c.Read_File(std::move(file2));
    Plane p = Plane();
    p.Read_File(std::move(file3));
    Sphere s = Sphere();
    s.Read_File(std::move(file4));
    printf("%s\n",b.toString().c_str());
    printf("%s\n",c.toString().c_str());
    printf("%s\n",p.toString().c_str());
    printf("%s\n",s.toString().c_str());
}

int main(int argc, char** argv)
{
    if(argc > 2)
    {
        std::string figure = argv[1];
        if(figure == "sphere")
        {
            Sphere *s = Sphere::Build(argc,argv);
            delete s;
        }
        else if(figure == "box")
        {
            Box *b = Box::Build(argc,argv);
            delete b;
        }
        else if(figure == "cone")
        {
            Cone *c = Cone::Build(argc,argv);
            delete c;
        }
        else if(figure == "plane")
        {
            Plane *p = Plane::Build(argc,argv);
            delete p;
        }
        else
        {
            printf("Invalid figure\n");
        }
    }
    return 0;
}