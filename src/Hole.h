#ifndef HOLE_H
#define HOLE_H

#include "Ground.h"

class Hole : public Ground
{
public:
    Hole();
    Hole(int x, int y, int z);
    virtual ~Hole();
};

#endif // HOLE_H
