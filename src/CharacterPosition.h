#ifndef CHARACTERPOSITION_H
#define CHARACTERPOSITION_H

#include <stdio.h>

class CharacterPosition
{
    public:
        CharacterPosition();
        CharacterPosition(int i, int j);
        virtual ~CharacterPosition();

        void convert_to_xz(float *x, float *z);
        bool equals(int i, int j);

        int i;
        int j;
};


#endif // CHARACTERPOSITION_H
