#ifndef CHARACTERPOSITION_H
#define CHARACTERPOSITION_H

#include <stdio.h>

class CharacterPosition
{
    public:
        CharacterPosition();
        CharacterPosition(int i, int j);
        virtual ~CharacterPosition();
        int i;
        int j;

        bool equals(int i, int j);
        void convert_to_xz(float *x, float *z);
};


#endif // CHARACTERPOSITION_H
