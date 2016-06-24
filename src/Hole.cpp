#include "Hole.h"

Hole::Hole() : Ground()
{
    this->setModel("Snorlax.obj");
}

Hole::Hole(int i, int j) : Ground(i,j)
{
    this->setModel("Snorlax.obj");
}

Hole::~Hole()
{
    //dtor
}
