#include "Crack.h"

Crack::Crack() : Ground()
{
    this->setModel("Cube.obj");

}

Crack::Crack(int i, int j) : Ground(i,j)
{
    this->setModel("Cube.obj");
}

Crack::~Crack()
{
    //dtor
}
