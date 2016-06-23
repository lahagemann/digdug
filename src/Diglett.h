#ifndef DIGLETT_H
#define DIGLETT_H

#include "Character.h"

class Diglett : public Character
{
    public:
        Diglett();
        Diglett(int i, int j);
        virtual ~Diglett();

        float getHeadPosition();

    private:
        float headPosition;
};

#endif // DIGLETT_H
