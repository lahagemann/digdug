#include "Snorlax.h"

Snorlax::Snorlax() : Character()
{
    this->setModel("Snorlax.obj", 0.5f);
}


Snorlax::Snorlax(GLfloat x, GLfloat y, GLfloat z) : Character(x,y,z)
{
    this->setModel("Snorlax.obj", 0.5f);
}

Snorlax::~Snorlax()
{
    //dtor
}
