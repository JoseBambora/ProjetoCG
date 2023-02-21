#ifndef PROJETOEXEC_GROUP_H
#define PROJETOEXEC_GROUP_H

#include <iostream>
#include <list>
class Group {
public:
    Group();
    void insertModel(const std::string&);
    std::list<std::string> *models;
    std::string toString();
    ~Group();
};

#endif
