#include "Character.h"

Character::Character()
{
    this->position = CharacterPosition();
}

Character::Character(int i, int j)
{
    this->position = CharacterPosition(i,j);
}

Character::~Character()
{
    //dtor
}

CharacterPosition Character::getPosition()
{
    return this->position;
}

float Character::getXRotation()
{
    return xRotation;
}

float Character::getYRotation()
{
    return yRotation;
}

void Character::setPosition(CharacterPosition position)
{
    this->position = position;
}

void Character::setPosition(int i, int j)
{
    this->position.i = i;
    this->position.j = j;
}

void Character::setXRotation(float rotation)
{
    xRotation = rotation;
}


void Character::setYRotation(float rotation)
{
    yRotation = rotation;
}

void Character::walk(Direction dir)
{
    switch(dir)
    {
        case forwards:
            if(this->yRotation == 0.0f) // Virado para a parte superior do mapa
                this->position.i--;
            else if(this->yRotation == 90.0f) // Virado para a esquerda do mapa
                this->position.j++;
            else if(this->yRotation == 180.0f) // Virado para a parte inferior do mapa
                this->position.i++;
            else if(this->yRotation == 270.0f) // Virado para a direita do mapa
                this->position.j--;
            break;

        case backwards:
            if(this->yRotation == 0.0f) // Virado para a parte superior do mapa
                this->position.i++;
            else if(this->yRotation == 90.0f) // Virado para a esquerda do mapa
                this->position.j--;
            else if(this->yRotation == 180.0f) // Virado para a parte inferior do mapa
                this->position.i--;
            else if(this->yRotation == 270.0f) // Virado para a direita do mapa
                this->position.j++;
            break;

        case rotateLeft:
            if(this->yRotation == 270.0f)
                this->yRotation = 0.0f;
            else
                this->yRotation += 90.0f;
            break;

        case rotateRight:
            if(this->yRotation == 0.0f)
                this->yRotation = 270.0f;
            else
                this->yRotation -= 90.0f;
            break;
    }
}

void Character::walkIn2DMode(Direction dir)
{
    switch(dir)
    {
        case forwards:
            this->setYRotation(180.0f);
            this->setPosition(this->getPosition().i+1, this->getPosition().j);
            break;

        case backwards:
            this->setYRotation(0.0f);
            this->setPosition(this->getPosition().i-1, this->getPosition().j);
            break;

        case rotateLeft:
            this->setYRotation(270.0f);
            this->setPosition(this->getPosition().i, this->getPosition().j-1);
            break;

        case rotateRight:
            this->setYRotation(90.0f);
            this->setPosition(this->getPosition().i, this->getPosition().j+1);
            break;
    }
}
