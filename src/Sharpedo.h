#ifndef SHARPEDO_H
#define SHARPEDO_H

#include "Character.h"


class Sharpedo : public Character
{
    public:
        Sharpedo();
        Sharpedo(int x, int y, int z);
        virtual ~Sharpedo();
        void swim();
};

#endif // SHARPEDO_H
