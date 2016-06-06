#include "APosition.h"

APosition::APosition()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

APosition::APosition(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

APosition::~APosition()
{
    //dtor
}
