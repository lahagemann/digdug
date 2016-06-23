#include "Floor.h"

Floor::Floor() : Ground()
{
    this->setModel("Floor.obj");

}

Floor::Floor(int i, int j) : Ground(i,j)
{
    this->setModel("Floor.obj");
}

Floor::~Floor()
{
    //dtor
}
