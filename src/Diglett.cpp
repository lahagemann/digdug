#include "Diglett.h"

Diglett::Diglett() : Character()
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 270.0f;
    yRotation = 0.0f;
    headPosition = 0.0f;
}

/*
Diglett::Diglett(GLfloat x, GLfloat y, GLfloat z) : Character(x,y,z)
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 270.0f;
    yRotation = 0.0f;
    headPosition = 0.0f;
}
*/

Diglett::Diglett(int i, int j) : Character(i,j)
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 270.0f;
    yRotation = 0.0f;
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
