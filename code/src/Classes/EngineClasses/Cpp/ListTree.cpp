#include "../Header/ListTree.h"
#include "../Header/Node.h"
#include "../Header/DefaultNode.h"
#include "../../Transformations/Header/Transform.h"

ListTree::ListTree() {
    this->tree = -1;
    this->level = -1;
    this->node = nullptr;
    this->sons = nullptr;
}


ListTree::ListTree(Node * node) {
    this->tree = -1;
    this->level = 0;
    this->node = node;
    this->sons = nullptr;

}

void ListTree::addNode(Node* node)
{
    if(level == -1)
    {
        this->level = 0;
        if(dynamic_cast<Transform*>(node))
        {
            this->node = node;
        }
        else
        {
            this->node = new DefaultNode();
            openLevel(node);
        }
    }
    else
    {
        ListTree *add = this;
        for(int n = 0; n < level-1; n++)
            add = add->sons->at(add->tree);
        add->tree+=1;
        add->sons->push_back(new ListTree(node));
    }
}

void ListTree::closeLevel() {
    this->level--;
}

void ListTree::closeLevel(Node* node) {
    this->closeLevel();
    this->addNode(node);
}

void ListTree::openLevel() {
    ListTree *add = this;
    this->level+=1;
    while(add->sons != nullptr)
    {
        add = add->sons->at(add->tree);
    }
    add->sons = new std::vector<ListTree*>();
}

void ListTree::openLevel(Node* node) {
    this->openLevel();
    this->addNode(node);
}

void ListTree::execute() {
    this->node->apply();
    if(this->sons)
    {
        for(ListTree *n : *this->sons)
        {
            n->execute();
        }
    }
    this->node->undo();
}

std::string ListTree::toString(int tabs,int level) {
    std::string res = '(' + this->node->toString() + ',' + std::to_string(level) + ')';
    if(this->sons != nullptr)
    {
        res += '\n';
        for (ListTree *son : *this->sons)
        {
            res += std::string(tabs,'\t') + son->toString(tabs+1,level+1);
            if (son->sons == nullptr)
                res += '\n';
        }
    }
    return res;
}

std::string ListTree::toString() {
    return this->toString(1,1);
}

ListTree::~ListTree() {
    for(ListTree *son : *this->sons)
    {
        delete son;
    }
    delete this->sons;
}

bool ListTree::empty() {
    return !this->node;
}

void ListTree::emptyNode() {
    this->node = new DefaultNode();
    this->level = 1;
    this->sons = new std::vector<ListTree*>();
}
