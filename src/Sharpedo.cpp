#include "Sharpedo.h"

Sharpedo::Sharpedo() : Character()
{
    this->setModel("Sharpedo.obj", 0.5f);
    this->setXRotation(270.0f);
    this->setYRotation(0.0f);
}

Sharpedo::Sharpedo(int i, int j) : Character(i,j)
{
    this->setModel("Sharpedo.obj", 0.5f);
    this->setXRotation(270.0f);
    this->setYRotation(0.0f);
}

Sharpedo::~Sharpedo()
{
    //dtor
}
