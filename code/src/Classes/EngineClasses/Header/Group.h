#ifndef PROJETOEXEC_GROUP_H
#define PROJETOEXEC_GROUP_H

#include <iostream>
#include <list>
class Figure;

class Group {
public:
    Group();
    void insertModel(const std::string&);
    std::list<Figure*> *models;
    std::string toString();
    ~Group();
    void drawModels(float,float,float);
};

#endif
