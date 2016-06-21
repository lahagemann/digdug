#ifndef DIGLETT_H
#define DIGLETT_H

#include "Character.h"
#include <stdio.h>

class Diglett : public Character
{
    public:
        Diglett();
        Diglett(int x, int y, int z);
        virtual ~Diglett();
        void setXRotation(float rotation);
        float getXRotation();
        void setYRotation(float rotation);
        float getYRotation();
        float getHeadPosition();

    private:
        float xRotation, yRotation;
        float headPosition;
};

#endif // DIGLETT_H
