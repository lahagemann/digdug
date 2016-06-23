#include "Snorlax.h"

Snorlax::Snorlax() : Character()
{
    this->setModel("Snorlax.obj", 0.5f);
    this->setXRotation(270.0f);
    this->setYRotation(0.0f);
}

Snorlax::Snorlax(int i, int j) : Character(i,j)
{
    this->setModel("Snorlax.obj", 0.5f);
    this->setXRotation(270.0f);
    this->setYRotation(0.0f);
}

Snorlax::~Snorlax()
{
    //dtor
}
