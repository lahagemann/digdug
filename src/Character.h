#ifndef CHARACTER_H
#define CHARACTER_H

#include <stdlib.h>
#include <string.h>
#include "APosition.h"
#include "glm.h"

class Character
{
    public:

        Character();
        //Character(GLfloat x, GLfloat y, GLfloat z);
        Character(int i, int j);
        virtual ~Character();

        void setModel(const char *filename, GLfloat sFactor);
        GLMmodel* getModel();
        //void setPosition(APosition position);
        //APosition getPosition();
        CharacterPosition getPosition();
        void setPosition(CharacterPosition position);
        void setPosition(int i, int j);

    private:
        bool load_new_model(const char *filename, GLfloat sFactor);
        GLMmodel *model;
        CharacterPosition position;
        //APosition position
};

#endif // CHARACTER_H
