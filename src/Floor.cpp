#include "Floor.h"

Floor::Floor() : Ground()
{
    this->setModel("Scyther.obj");

}

Floor::Floor(int i, int j) : Ground(i,j)
{
    this->setModel("Scyther.obj");
}

Floor::~Floor()
{
    //dtor
}
