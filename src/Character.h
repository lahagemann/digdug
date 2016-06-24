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

        GLMmodel* getModel();
        CharacterPosition getPosition();
        float getXRotation();
        float getYRotation();
        void setModel(const char *filename, GLfloat sFactor);
        void setPosition(CharacterPosition position);
        void setPosition(int i, int j);
        void setXRotation(float rotation);
        void setYRotation(float rotation);
        void walk(Direction dir);

    private:
        //bool load_new_model(const char *filename, GLfloat sFactor);

        GLMmodel *model;
        CharacterPosition position;
        float xRotation, yRotation;
};

#endif // CHARACTER_H
