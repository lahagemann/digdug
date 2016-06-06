#include "Sharpedo.h"

Sharpedo::Sharpedo() : Character()
{
    this->setModel("Sharpedo.obj");
}

Sharpedo::Sharpedo(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Sharpedo.obj");
}

Sharpedo::~Sharpedo()
{
    //dtor
}
