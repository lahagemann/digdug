#ifndef SCYTHER_H
#define SCYTHER_H

#include "Character.h"
#include <stdio.h>

class Scyther : public Character
{
    public:
        Scyther();
        Scyther(int x, int y, int z);
        virtual ~Scyther();

    protected:

    private:
};

#endif // SCYTHER_H
