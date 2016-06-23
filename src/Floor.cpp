#include "Floor.h"

Floor::Floor() : Ground()
{
    this->setModel("Cube.obj");

}

Floor::Floor(int i, int j) : Ground(i,j)
{
    this->setModel("Cube.obj");
}

Floor::~Floor()
{
    //dtor
}
