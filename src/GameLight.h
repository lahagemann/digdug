#ifndef GAMELIGHT_H
#define GAMELIGHT_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "A_RGB.h"

class GameLight
{
    public:
        GameLight();
        virtual ~GameLight();

        void makeLight();

    private:
        const A_RGB skyColor = A_RGB(100, 185, 255);
};

#endif // GAMELIGHT_H
