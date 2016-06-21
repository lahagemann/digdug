#include "Diglett.h"

Diglett::Diglett() : Character()
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 0.0f;
    yRotation = 0.0f;
    headPosition = 0.0f;
}

Diglett::Diglett(int x, int y, int z) : Character(x,y,z)
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 0.0f;
    yRotation = 0.0f;
    headPosition = 0.0f;
}

Diglett::~Diglett()
{
    //dtor
}

void Diglett::setXRotation(float rotation)
{
    xRotation = rotation;
}

float Diglett::getXRotation()
{
    return xRotation;
}

void Diglett::setYRotation(float rotation)
{
    yRotation = rotation;
}

float Diglett::getYRotation()
{
    return yRotation;
}

float Diglett::getHeadPosition()
{
    return headPosition;
}
