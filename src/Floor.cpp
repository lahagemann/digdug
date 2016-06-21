#include "Floor.h"

Floor::Floor() : Ground()
{
    this->setModel("Cube.obj");

}

Floor::Floor(GLfloat x, GLfloat y, GLfloat z) : Ground(x,y,z)
{
    this->setModel("Cube.obj");
}


