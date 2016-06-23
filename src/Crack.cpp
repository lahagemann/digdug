#include "Crack.h"

Crack::Crack() : Ground()
{
    this->setModel("Crack.obj");

}

Crack::Crack(int i, int j) : Ground(i,j)
{
    this->setModel("Crack.obj");
}

Crack::~Crack()
{
    //dtor
}
