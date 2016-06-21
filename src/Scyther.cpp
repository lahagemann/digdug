#include "Scyther.h"

Scyther::Scyther() : Character()
{
    this->setModel("Scyther.obj", 0.5f);
}

Scyther::Scyther(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Scyther.obj", 0.5f);
}

Scyther::~Scyther()
{
    //dtor
}
