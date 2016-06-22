#ifndef GROUND_H
#define GROUND_H

class Ground
{
public:
    Ground();
    //Ground(GLfloat x, GLfloat y, GLfloat z);
    Ground(int i, int j);
    virtual ~Ground();
    //APosition getPosition();
    CharacterPosition getPosition();
    void setModel(const char *filename);

private:
    bool load_new_model(const char *filename);
    //APosition position;
    CharacterPosition position;
    GLMmodel *model;
};

#endif // GROUND_H
