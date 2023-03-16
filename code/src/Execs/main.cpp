#include "../Classes/EngineClasses/Header/ListTree.h"
int main()
{
    auto *aux = new ListTree(0);
    aux->openLevel();
    aux->addNode(2);
    aux->openLevel();
    aux->addNode(3);
    aux->addNode(5);
    aux->addNode(7);
    aux->closeLevel();
    aux->addNode(1);
    aux->addNode(2);
    aux->addNode(3);
    aux->addNode(4);
    aux->openLevel();
    aux->addNode(10);
    aux->addNode(40);
    aux->closeLevel();
    aux->addNode(15);
    aux->openLevel();
    aux->addNode(30);
    aux->openLevel(55);
    aux->addNode(10);
    aux->addNode(35);
    aux->closeLevel();
    aux->addNode(67);
    aux->openLevel(34);
    printf("%s\n",aux->toString().c_str());
    delete aux;
}
