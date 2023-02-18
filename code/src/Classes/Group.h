#include <iostream>
#include <list>
class Group {
public:
    Group();
    void insertModel(std::string);
    std::list<std::string> models;
    std::string toString();

};
