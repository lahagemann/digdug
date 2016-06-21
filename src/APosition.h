#ifndef APOSITION_H
#define APOSITION_H

#include <stdio.h>

class APosition
{
    public:
        APosition();
        APosition(GLfloat x, GLfloat y, GLfloat z);
        virtual ~APosition();
        GLfloat x;
        GLfloat y;
        GLfloat z;
};

#endif // APOSITION_H
