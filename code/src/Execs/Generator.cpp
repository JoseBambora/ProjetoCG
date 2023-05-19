#include <string>
#include <cstdio>
#include "../Classes/Figures/Header/Box.h"

const std::string dir = "../files/";

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