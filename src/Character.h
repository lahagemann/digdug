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
        Character(int x, int y, int z);
        virtual ~Character();

        void setModel(const char *filename, GLfloat sFactor);
        GLMmodel* getModel();
        void setPosition(APosition position);
        APosition getPosition();

    private:
        bool load_new_model(const char *filename, GLfloat sFactor);
        GLMmodel *model;
        APosition position;
};

#endif // CHARACTER_H
