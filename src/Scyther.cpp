#include "Scyther.h"

Scyther::Scyther() : Character()
{
    this->setXRotation(90.0f);
    this->setYRotation(0.0f);
}

Scyther::Scyther(int i, int j) : Character(i,j)
{
    this->setXRotation(90.0f);
    this->setYRotation(0.0f);
}

Scyther::~Scyther()
{
    //dtor
}
