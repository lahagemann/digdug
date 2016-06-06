#ifndef DIGLETT_H
#define DIGLETT_H

#include "Character.h"
#include <stdio.h>

class Diglett : public Character
{
    public:
        Diglett();
        Diglett(int x, int y, int z);
        virtual ~Diglett();
        float getHeadPosition();
        //ver como vamos organizar os parâmetros que vamos passar.
        //shove();
        //walk();
        //crack();

    private:
        float headPosition;
};

#endif // DIGLETT_H
