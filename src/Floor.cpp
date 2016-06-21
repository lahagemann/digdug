#include "Floor.h"

Floor::Floor() : Ground()
{
    this->setModel("Cube.obj");

}

Floor::Floor(int x, int y, int z) : Ground(x,y,z)
{
    this->setModel("Cube.obj");
}


