#ifndef GROUND_H
#define GROUND_H

class Ground
{
public:
    Ground();
    Ground(int x, int y, int z);
    virtual ~Ground();
    APosition getPosition();
    void setModel(const char *filename);

private:
    bool load_new_model(const char *filename);
    APosition position;
    GLMmodel *model;
};

#endif // GROUND_H
