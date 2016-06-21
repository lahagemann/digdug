#ifndef GAMELIGHT_H
#define GAMELIGHT_H

#include <gl/gl.h>
#include <gl/glut.h>

class GameLight
{
    public:
        GameLight();
        virtual ~GameLight();

    private:
        const A_RGB skyColor = A_RGB(0, 185, 255);
};

#endif // GAMELIGHT_H
