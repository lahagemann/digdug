#include "Snorlax.h"

Snorlax::Snorlax() : Character()
{
    this->setModel("Snorlax.obj");
}


Snorlax::Snorlax(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Snorlax.obj");
}

Snorlax::~Snorlax()
{
    //dtor
}
