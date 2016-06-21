#include "Character.h"

Character::Character()
{
    this->position = APosition();
}

Character::Character(GLfloat x, GLfloat y, GLfloat z)
{
    this->position = APosition(x,y,z);
}

Character::~Character()
{
    //dtor
}

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

void Character::setModel(const char *filename, GLfloat sFactor)
{
    model = (GLMmodel *)malloc(sizeof(GLMmodel));
    load_new_model(filename, sFactor);
}

GLMmodel* Character::getModel()
{
    return model;
}

void Character::setPosition(APosition position)
{
    this->position = position;
}

APosition Character::getPosition()
{
    return position;
}

