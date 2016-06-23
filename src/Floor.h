#ifndef FLOOR_H
#define FLOOR_H

#include "Ground.h"

class Floor : public Ground
{
public:
    Floor();
    Floor(int i, int j);
    virtual ~Floor();
};

#endif // FLOOR_H
