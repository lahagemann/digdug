#ifndef SCYTHER_H
#define SCYTHER_H

#include "Character.h"
#include <stdio.h>

class Scyther : public Character
{
    public:
        Scyther();
        Scyther(int i, int j);
        virtual ~Scyther();
};

#endif // SCYTHER_H
