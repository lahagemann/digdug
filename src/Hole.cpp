#include "Hole.h"

Hole::Hole() : Ground()
{
    this->setModel("Cube.obj");
}

Hole::Hole(int i, int j) : Ground(i,j)
{
    this->setModel("Cube.obj");
}

Hole::~Hole()
{
    //dtor
}
