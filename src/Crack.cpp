#include "Crack.h"

Crack::Crack() : Ground()
{
    this->setModel("Diglett.obj");

}

Crack::Crack(int i, int j) : Ground(i,j)
{
    this->setModel("Diglett.obj");
}

Crack::~Crack()
{
    //dtor
}
