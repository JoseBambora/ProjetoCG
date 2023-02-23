#include <string>
#include <cstdio>
#include "../Classes/Figures/Header/Box.h"

const std::string dir = "../files/";
void testeescrita()
{
    std::string name1 = dir + "box.3d";
    std::string name2 = dir + "cone.3d";
    std::string name3 = dir + "plane.3d";
    std::string name4 = dir + "sphere.3d";
    Figure *b = Figure::ReadFile(name1);
    Figure *c = Figure::ReadFile(name2);
    Figure *p = Figure::ReadFile(name3);
    Figure *s = Figure::ReadFile(name4);
    printf("%s\n",b->toString().c_str());
    printf("%s\n",c->toString().c_str());
    printf("%s\n",p->toString().c_str());
    printf("%s\n",s->toString().c_str());
    delete b;
    delete c;
    delete p;
    delete s;
}

int main(int argc, char** argv)
{
    if(argc > 2)
    {
        Figure *figure = Figure::Build(argc,argv);
        printf("Figure created\n");
        printf("%s\n",figure->toString().c_str());
        delete figure;
    }
    return 0;
}