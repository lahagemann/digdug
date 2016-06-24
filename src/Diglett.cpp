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

void Diglett::walkIn2DMode(Direction dir)
{
    switch(dir)
    {
        case forwards:
            this->setPosition(this->getPosition().i+1, this->getPosition().j);
            break;

        case backwards:
            this->setPosition(this->getPosition().i-1, this->getPosition().j);
            break;

        case rotateLeft:
            this->setPosition(this->getPosition().i, this->getPosition().j-1);
            break;

        case rotateRight:
            this->setPosition(this->getPosition().i, this->getPosition().j+1);
            break;
    }
}
