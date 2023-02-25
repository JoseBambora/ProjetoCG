#include <fstream>
#include "../Header/Figure.h"
#include "../Header/Cone.h"
#include "../Header/Sphere.h"
#include "../Header/Box.h"
#include "../Header/Plane.h"

// Build a figure, given the exec arguments
// CAN BE NULL
// Each sub class creates the file given automatically, with the information of the figure.
Figure *Figure::Build(int argc, char **argv) {
    Figure *res = nullptr;
    if(argc > 2)
    {
        std::string figure = argv[1];
        if(figure == "sphere")
            res = Sphere::Build(argc,argv);
        else if(figure == "box")
            res = Box::Build(argc,argv);
        else if(figure == "cone")
            res = Cone::Build(argc,argv);
        else if(figure == "plane")
            res = Plane::Build(argc,argv);
        else
            printf("Invalid figure. Figure result: nullptr\n");
    }
    return res;
}

// Reads the content from a binary file. It will create a figure, based on the file information.
// CAN BE NULL
Figure *Figure::ReadFile(const std::string& name) {
    int cod;
    Figure *res;
    std::ifstream file;
    file.open(name, std::ios::binary);
    file.read((char *) &cod, sizeof(cod));
    switch (cod) {
        case codBox:
            res = Box::Read_File(std::move(file));
            break;
        case codPlane:
            res = Plane::Read_File(std::move(file));
            break;
        case codSphere:
            res = Sphere::Read_File(std::move(file));
            break;
        case codCone:
            res = Cone::Read_File(std::move(file));
            break;
        default:
            printf("Invalid file. Result figure = nullptr\n");
            res = nullptr;
    }
    return res;
}

void Figure::drawFigure(float, float, float) {

}