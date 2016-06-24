#ifndef DIGLETT_H
#define DIGLETT_H

#include "Character.h"

class Diglett : public Character
{
    public:
        Diglett();
        Diglett(int i, int j);
        virtual ~Diglett();

        void walkIn2DMode(Direction dir);
};

#endif // DIGLETT_H
