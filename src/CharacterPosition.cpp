
#include "CharacterPosition.h"

CharacterPosition::CharacterPosition()
{
    this->i = 0;
    this->j = 0;
}

CharacterPosition::CharacterPosition(int i, int j)
{
    this->i = i;
    this->j = j;
}

CharacterPosition::~CharacterPosition()
{
    //dtor
}

bool CharacterPosition::equals(int i, int j)
{
    if(i == this->i && j == this->j)
        return true;

    return false;
}
