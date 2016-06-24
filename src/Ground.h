#ifndef GROUND_H
#define GROUND_H

#include "CharacterPosition.h"
#include "Model.h"

class Ground
{
    public:
        Ground();
        Ground(int i, int j);
        virtual ~Ground();

        CharacterPosition getPosition();
        void setPosition(int i, int j);

    private:
        CharacterPosition position;
};

#endif // GROUND_H
