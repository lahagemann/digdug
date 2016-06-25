#include "Diglett.h"

Diglett::Diglett() : Character()
{
    this->setXRotation(90.0f);
    this->setYRotation(0.0f);
}

Diglett::Diglett(int i, int j) : Character(i,j)
{
    this->setXRotation(90.0f);
    this->setYRotation(0.0f);
}

Diglett::~Diglett()
{
    //dtor
}
