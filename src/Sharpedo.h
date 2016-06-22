#ifndef SHARPEDO_H
#define SHARPEDO_H

#include "Character.h"


class Sharpedo : public Character
{
    public:
        Sharpedo();
        //Sharpedo(GLfloat x, GLfloat y, GLfloat z);
        Sharpedo(int i, int j);
        virtual ~Sharpedo();
        void swim();
};

#endif // SHARPEDO_H
