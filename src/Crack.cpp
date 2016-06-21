#include "Crack.h"

Crack::Crack() : Ground()
{
    this->setModel("Cube.obj");

}

Crack::Crack(int x, int y, int z) : Ground(x,y,z)
{
    this->setModel("Cube.obj");
}
