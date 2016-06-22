#ifndef CRACK_H
#define CRACK_H

#include "Ground.h"

class Crack : public Ground
{
public:
    Crack();
    //Crack(int x, int y, int z);
    Crack(int i, int j);
    virtual ~Crack();
};

#endif // CRACK_H
