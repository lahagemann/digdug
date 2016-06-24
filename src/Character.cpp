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

GLMmodel* Character::getModel()
{
    return model;
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

void Character::setModel(const char *filename, GLfloat sFactor)
{
    model = (GLMmodel *)malloc(sizeof(GLMmodel));
    //load_new_model(filename, sFactor);
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
    /* TODO:
            - verificar se o movimento é permitido
            - verificar se o jogador se matou
            - verificar colisão com inimigos
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
/*
bool Character::load_new_model(const char *filename, GLfloat sFactor)
{
    char aszFilename[256];
    strcpy(aszFilename, filename);

    if(model)
    {
        free(model);
        model = NULL;
    }

    model = glmReadOBJ(aszFilename);
    if(!model)
        return false;

    glmUnitize(model);
    glmScale(model,sFactor);
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0);

    return true;
}
*/
