#include "Scyther.h"

Scyther::Scyther() : Character()
{
    //this->setModel("Scyther.obj", 0.5f);
    this->setXRotation(270.0f);
    this->setYRotation(0.0f);
}

Scyther::Scyther(int i, int j) : Character(i,j)
{
    //this->setModel("Scyther.obj", 0.5f);
    this->setXRotation(270.0f);
    this->setYRotation(0.0f);
}

Scyther::~Scyther()
{
    //dtor
}
