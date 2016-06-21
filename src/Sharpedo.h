#ifndef SHARPEDO_H
#define SHARPEDO_H

#include "Character.h"


class Sharpedo : public Character
{
    public:
        Sharpedo();
        Sharpedo(GLfloat x, GLfloat y, GLfloat z);
        virtual ~Sharpedo();
        void swim();
};

#endif // SHARPEDO_H
