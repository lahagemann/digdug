#include "Crack.h"

Crack::Crack() : Ground()
{
    this->setModel("Cube.obj");

}

Crack::Crack(GLfloat x, GLfloat y, GLfloat z) : Ground(x,y,z)
{
    this->setModel("Cube.obj");
}
