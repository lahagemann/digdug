#include "Diglett.h"

Diglett::Diglett() : Character()
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 270.0f;
    yRotation = 0.0f;
    headPosition = 0.0f;
}

/*
Diglett::Diglett(GLfloat x, GLfloat y, GLfloat z) : Character(x,y,z)
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 270.0f;
    yRotation = 0.0f;
    headPosition = 0.0f;
}
*/

Diglett::Diglett(int i, int j) : Character(i,j)
{
    this->setModel("Diglett.obj", 0.5f);
    xRotation = 270.0f;
    yRotation = 0.0f;
    headPosition = 0.0f;
}

Diglett::~Diglett()
{
    //dtor
}

float Diglett::getHeadPosition()
{
    return headPosition;
}

float Diglett::getXRotation()
{
    return xRotation;
}

void Diglett::setXRotation(float rotation)
{
    xRotation = rotation;
}

float Diglett::getYRotation()
{
    return yRotation;
}

void Diglett::setYRotation(float rotation)
{
    yRotation = rotation;
}

void Diglett::walk(Direction dir)
{
    /* TODO:
            - verificar se o movimento � permitido
            - verificar se o jogador se matou
            - verificar colis�o com inimigos
    */

    switch(dir)
    {
        case forwards:
            if(this->xRotation == 0.0f) // Virado para a direita do mapa
                this->position.j++;
            else if(this->xRotation == 90.0f) // Virado para a parte superior do mapa
                this->position.i++;
            else if(this->xRotation == 180.0f) // Virado para a esquerda do mapa
                this->position.j--;
            else if(this->xRotation == 270.0f) // Virado para a parte inferior do mapa
                this->position.i--;
            break;

        case backwards:
            if(this->xRotation == 0.0f) // Virado para a direita do mapa
                this->position.j--;
            else if(this->xRotation == 90.0f) // Virado para a parte superior do mapa
                this->position.i--;
            else if(this->xRotation == 180.0f) // Virado para a esquerda do mapa
                this->position.j++;
            else if(this->xRotation == 270.0f) // Virado para a parte inferior do mapa
                this->position.i++;
            break;

        case rotateLeft:
            if(this->xRotation == 270.0f)
                this->xRotation = 0.0f;
            else
                this->xRotation += 90.0f;
            break;

        case rotateRight:
            if(this->xRotation == 0.0f)
                this->xRotation = 270.0f;
            else
                this->xRotation -= 90.0f;
            break;
    }
}


