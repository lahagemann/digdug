#include "Ground.h"

Ground::Ground()
{
    this->position = CharacterPosition();
}

Ground::Ground(int i, int j)
{
    this->position = CharacterPosition(i,j);
}

Ground::~Ground()
{
    //dtor
}

CharacterPosition Ground::getPosition()
{
    return this->position;
}

void Ground::setPosition(int i, int j)
{
    this->position = CharacterPosition(i,j);
}
