#include "Scyther.h"

Scyther::Scyther() : Character()
{
    this->setModel("Scyther.obj");
}

Scyther::Scyther(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Scyther.obj");
}

Scyther::~Scyther()
{
    //dtor
}
