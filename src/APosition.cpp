#include "APosition.h"

APosition::APosition()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

APosition::APosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

APosition::~APosition()
{
    //dtor
}
