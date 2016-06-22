#include "Snorlax.h"

Snorlax::Snorlax() : Character()
{
    this->setModel("Snorlax.obj", 0.5f);
}

/*
Snorlax::Snorlax(GLfloat x, GLfloat y, GLfloat z) : Character(x,y,z)
{
    this->setModel("Snorlax.obj", 0.5f);
}
*/

Snorlax::Snorlax(int i, int j) : Character(i,j)
{
    this->setModel("Snorlax.obj", 0.5f);
}

Snorlax::~Snorlax()
{
    //dtor
}
