#include "Snorlax.h"

Snorlax::Snorlax() : Character()
{
    this->setXRotation(90.0f);
    this->setYRotation(270.0f);
}

Snorlax::Snorlax(int i, int j) : Character(i,j)
{
    this->setXRotation(90.0f);
    this->setYRotation(270.0f);
}

Snorlax::~Snorlax()
{
    //dtor
}
