#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>

const int planeCod = 0;
const int sphereCod = 1;
const int boxCod = 2;
const int coneCod = 3;
const std::string dir = "../../files/";

void plane(int argc, char** argv)
{
    if(argc == 5)
    {
        long length = strtol(argv[2], nullptr,10);
        long division = strtol(argv[3], nullptr,10);
        std::string name = dir + argv[4];
        std::ofstream myfile;
        myfile.open (name,std::ios::binary | std::fstream::out);
        myfile.write((char *) &planeCod,sizeof(planeCod));
        myfile.write((char *) &length,sizeof(length));
        myfile.write((char *) &division,sizeof(division));
        myfile.close();
    }
    else
        printf("Invalid arguments for plane\n");
}

void box(int argc, char** argv)
{
    if(argc == 5)
    {
        long length = strtol(argv[2], nullptr,10);
        long dimension = strtol(argv[3], nullptr,10);
        std::string name = dir + argv[4];
        std::ofstream myfile;
        myfile.open (name,std::ios::binary | std::fstream::out);
        myfile.write((char *) &boxCod,sizeof(boxCod));
        myfile.write((char *) &length,sizeof(length));
        myfile.write((char *) &dimension,sizeof(dimension));
        myfile.close();
    }
    else
        printf("Invalid arguments for box\n");
}

void sphere(int argc, char** argv)
{
    if(argc == 6)
    {
        long radius = strtol(argv[2], nullptr,10);
        long slices = strtol(argv[3], nullptr,10);
        long stacks = strtol(argv[4], nullptr,10);
        std::string name = dir + argv[5];
        std::ofstream myfile;
        myfile.open (name,std::ios::binary | std::fstream::out);
        myfile.write((char *) &sphereCod,sizeof(sphereCod));
        myfile.write((char *) &radius,sizeof(radius));
        myfile.write((char *) &slices,sizeof(slices));
        myfile.write((char *) &stacks,sizeof(stacks));
        myfile.close();
    }
    else
        printf("Invalid arguments for sphere\n");
}

void cone(int argc, char** argv)
{
    if(argc == 7)
    {
        long radius = strtol(argv[2], nullptr,10);
        long height = strtol(argv[3], nullptr,10);
        long slices = strtol(argv[4], nullptr,10);
        long stacks = strtol(argv[5], nullptr,10);
        std::string name = dir + argv[6];
        std::ofstream myfile;
        myfile.open (name,std::ios::binary | std::fstream::out);
        myfile.write((char *) &coneCod,sizeof(coneCod));
        myfile.write((char *) &radius,sizeof(radius));
        myfile.write((char *) &height,sizeof(height));
        myfile.write((char *) &slices,sizeof(slices));
        myfile.write((char *) &stacks,sizeof(stacks));
        myfile.close();
    }
    else
        printf("Invalid arguments for cone\n");
}

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
    int cod1, cod2, cod3, cod4;
    long d1, d2;
    file1.read((char *) &cod1, sizeof(cod1));
    file1.read((char *) &d1, sizeof(d1));
    file1.read((char *) &d2, sizeof(d2));
    long d3,d4,d5,d6;
    file2.read((char *) &cod2, sizeof(cod2));
    file2.read((char *) &d3, sizeof(d3));
    file2.read((char *) &d4, sizeof(d4));
    file2.read((char *) &d5, sizeof(d5));
    file2.read((char *) &d6, sizeof(d6));
    long d7,d8;
    file3.read((char *) &cod3, sizeof(cod3));
    file3.read((char *) &d7, sizeof(d7));
    file3.read((char *) &d8, sizeof(d8));
    long d9,d10,d11;
    file4.read((char *) &cod4, sizeof(cod4));
    file4.read((char *) &d9, sizeof(d9));
    file4.read((char *) &d10, sizeof(d10));
    file4.read((char *) &d11, sizeof(d11));
    file1.close();
    file2.close();
    file3.close();
    file4.close();
    printf("box:   code: %d | %ld | %ld\n",cod1,d1,d2);
    printf("cone:  code: %d | %ld | %ld | %ld | %ld\n",cod2,d3,d4,d5,d6);
    printf("plane: code: %d | %ld | %ld\n",cod3,d7,d8);
    printf("sphere code: %d | %ld | %ld | %ld\n",cod4,d9,d10,d11);
}

int main(int argc, char** argv)
{
    testeescrita();
    if(argc > 2)
    {
        std::string figure = argv[1];
        if(figure == "sphere")
            sphere(argc,argv);
        else if(figure == "box")
            box(argc,argv);
        else if(figure == "cone")
            cone(argc,argv);
        else if(figure == "plane")
            plane(argc,argv);
        else
        {
            printf("Invalid figure\n");
        }
    }
}