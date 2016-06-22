#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdlib.h>
#include <string.h>
#include "CharacterPosition.h"
#include "glm.h"

class Character
{
    public:

        Character();
        //Character(GLfloat x, GLfloat y, GLfloat z);
        Character(int i, int j);
        virtual ~Character();
        enum Direction {forwards, backwards, rotateLeft, rotateRight};
        //void setPosition(APosition position);
        //APosition getPosition();
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
        bool load_new_model(const char *filename, GLfloat sFactor);
        GLMmodel *model;
        CharacterPosition position;
        //APosition position
};

#endif // CHARACTER_H
