#ifndef SCYTHER_H
#define SCYTHER_H

#include "Character.h"
#include <stdio.h>

class Scyther : public Character
{
    public:
        Scyther();
        //Scyther(GLfloat x, GLfloat y, GLfloat z);
        Scyther(int i, int j);
        virtual ~Scyther();

    protected:

    private:
};

#endif // SCYTHER_H
