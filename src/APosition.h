#ifndef APOSITION_H
#define APOSITION_H

#include <stdio.h>

class APosition
{
    public:
        APosition();
        APosition(int x, int y, int z);
        virtual ~APosition();
        int x;
        int y;
        int z;
};

#endif // APOSITION_H
