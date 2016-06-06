#include "Diglett.h"

Diglett::Diglett() : Character()
{
    this->setModel("Diglett.obj");
    headPosition = 0.0;
}

Diglett::Diglett(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Diglett.obj");
    headPosition = 0.0;
}

Diglett::~Diglett()
{
    //dtor
}

float Diglett::getHeadPosition()
{
    return headPosition;
}
