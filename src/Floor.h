#ifndef FLOOR_H
#define FLOOR_H

#include "Ground.h"

class Floor : public Ground
{
public:
    Floor();
    Floor(int x, int y, int z);
    virtual ~Floor();
};

#endif // FLOOR_H
