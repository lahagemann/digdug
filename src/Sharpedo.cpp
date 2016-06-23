#include "Sharpedo.h"

Sharpedo::Sharpedo() : Character()
{
    this->setModel("Sharpedo.obj", 0.5f);
}

Sharpedo::Sharpedo(int i, int j) : Character(i,j)
{
    this->setModel("Sharpedo.obj", 0.5f);
}

Sharpedo::~Sharpedo()
{
    //dtor
}
