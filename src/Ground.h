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

        GLMmodel* getModel();
        CharacterPosition getPosition();
        void setModel(const char *filename);

    private:
        bool load_new_model(const char *filename);

        CharacterPosition position;
        GLMmodel *model;
};

#endif // GROUND_H
