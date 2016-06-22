#include "Ground.h"

Ground::Ground()
{
    this->position = APosition();
}

/*
Ground::Ground(GLfloat x, GLfloat y, GLfloat z)
{
    this->position = APosition(x,y,z);
}


APosition Ground::getPosition()
{
    return this->position;
}
*/

Ground::Ground(int i, int j)
{
    this->position = CharacterPosition(i,j);
}

CharacterPosition Ground::getPosition()
{
    return this->position;
}

void Ground::setModel(const char* filename)
{
    model = (GLMmodel *)malloc(sizeof(GLMmodel));
    load_new_model(filename);
}

bool Ground::load_new_model(const char *filename)
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
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0);

    return true;
}

