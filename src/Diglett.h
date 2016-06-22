#ifndef DIGLETT_H
#define DIGLETT_H

#include "Character.h"
#include <stdio.h>

class Diglett : public Character
{
    public:
        Diglett();
        //Diglett(GLfloat x, GLfloat y, GLfloat z);
        Diglett(int i, int j)
        virtual ~Diglett();
        float getHeadPosition();

    private:
        float xRotation, yRotation;
        float headPosition;


};

#endif // DIGLETT_H
