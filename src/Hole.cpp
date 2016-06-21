#include "Hole.h"

Hole::Hole() : Ground()
{
    this->setModel("Cube.obj");

}

Hole::Hole(int x, int y, int z) : Ground(x,y,z)
{
    this->setModel("Cube.obj");
}
