#ifndef HOLE_H
#define HOLE_H

#include "Ground.h"

class Hole : public Ground
{
public:
    Hole();
    //Hole(GLfloat x, GLfloat y, GLfloat z);
    Hole(int i, int j);
    virtual ~Hole();
};

#endif // HOLE_H
