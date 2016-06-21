#ifndef FLOOR_H
#define FLOOR_H

#include "Ground.h"

class Floor : public Ground
{
public:
    Floor();
    Floor(GLfloat x, GLfloat y, GLfloat z);
    virtual ~Floor();
};

#endif // FLOOR_H
