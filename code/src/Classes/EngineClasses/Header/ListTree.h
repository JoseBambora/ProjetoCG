#ifndef PROJETOEXEC_LISTTREE_H
#define PROJETOEXEC_LISTTREE_H


#include <vector>
#include <string>
class Node;

class ListTree {
private:
    int level;
    Node *node;
    std::vector<ListTree*> *sons;
    std::string toString(int,int);
public:
    explicit ListTree();
    explicit ListTree(Node *);
    void addNode(Node*);
    void closeLevel();
    void closeLevel(Node*);
    void openLevel();
    void openLevel(Node*);
    ~ListTree();
    std::string toString();
    void execute();
    bool empty();
    void emptyNode();
};


#endif
