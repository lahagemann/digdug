#include "Hole.h"

Hole::Hole() : Ground()
{
    this->setModel("Hole.obj");
}

Hole::Hole(int i, int j) : Ground(i,j)
{
    this->setModel("Hole.obj");
}

Hole::~Hole()
{
    //dtor
}
