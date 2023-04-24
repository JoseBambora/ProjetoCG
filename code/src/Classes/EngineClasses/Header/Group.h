#ifndef PROJETOEXEC_GROUP_H
#define PROJETOEXEC_GROUP_H

#include <iostream>
#include <list>
class Figure;
class ListTree;
class Transform;

class Group {
public:
    Group(ListTree *tree);
    ListTree *tree;
    std::string toString();
    ~Group();
    void load();
    void execute();
};

#endif
