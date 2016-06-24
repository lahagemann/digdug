#include "Sharpedo.h"

Sharpedo::Sharpedo() : Character()
{
    this->setXRotation(90.0f);
    this->setYRotation(270.0f);
}

Sharpedo::Sharpedo(int i, int j) : Character(i,j)
{
    this->setXRotation(90.0f);
    this->setYRotation(270.0f);
}

Sharpedo::~Sharpedo()
{
    //dtor
}
