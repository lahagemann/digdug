#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdlib.h>
#include <string.h>
#include "CharacterPosition.h"
#include "Model.h"

class Character
{
    public:
        enum Direction {forwards, backwards, rotateLeft, rotateRight};

        Character();
        Character(int i, int j);
        virtual ~Character();

        CharacterPosition getPosition();
        float getXRotation();
        float getYRotation();
        void setPosition(CharacterPosition position);
        void setPosition(int i, int j);
        void setXRotation(float rotation);
        void setYRotation(float rotation);
        void walk(Direction dir);
        void walkIn2DMode(Direction dir);

    private:
        CharacterPosition position;
        float xRotation, yRotation;
};

#endif // CHARACTER_H
