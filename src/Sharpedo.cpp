#include "Sharpedo.h"

Sharpedo::Sharpedo() : Character()
{
    this->setModel("Sharpedo.obj", 0.5f);
}

Sharpedo::Sharpedo(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Sharpedo.obj", 0.5f);
}

Sharpedo::~Sharpedo()
{
    //dtor
}
