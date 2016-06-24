#include "Diglett.h"

Diglett::Diglett() : Character()
{
    //this->setModel("Diglett.obj", 0.5f);
    this->setXRotation(90.0f);
    this->setYRotation(0.0f);
    headPosition = 0.0f;
}

Diglett::Diglett(int i, int j) : Character(i,j)
{
    //this->setModel("Diglett.obj", 0.5f);
    this->setXRotation(90.0f);
    this->setYRotation(0.0f);
    headPosition = 0.0f;
}

Diglett::~Diglett()
{
    //dtor
}

float Diglett::getHeadPosition()
{
    return headPosition;
}
