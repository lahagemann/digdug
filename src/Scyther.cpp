#include "Scyther.h"

Scyther::Scyther() : Character()
{
    this->setModel("Scyther.obj", 0.5f);
}

Scyther::Scyther(int i, int j) : Character(i,j)
{
    this->setModel("Scyther.obj", 0.5f);
}

Scyther::~Scyther()
{
    //dtor
}
