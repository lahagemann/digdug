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
        void setXRotation(float rotation);
        float getXRotation();
        void setYRotation(float rotation);
        float getYRotation();
        float getHeadPosition();

        void walk(Direction dir);

        const enum Direction {forwards, backwards, rotateLeft, rotateRight};

    private:
        float xRotation, yRotation;
        float headPosition;


};

#endif // DIGLETT_H
