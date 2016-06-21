#include "Snorlax.h"

Snorlax::Snorlax() : Character()
{
    this->setModel("Snorlax.obj", 0.5f);
}


Snorlax::Snorlax(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Snorlax.obj", 0.5f);
}

Snorlax::~Snorlax()
{
    //dtor
}
