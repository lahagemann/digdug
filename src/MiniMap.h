#ifndef MINIMAP_H
#define MINIMAP_H

#include "windows.h"
#include <gl/gl.h>
#include <gl/glut.h>
#include "Cam.h"
#include "Diglett.h"

class MiniMap
{
    public:
        MiniMap();
        MiniMap(int windowWidth, int windowHeight);
        virtual ~MiniMap();

        void showMiniMap(Diglett player);

    private:
        Cam miniMapCam;
        int miniMapHeight, miniMapWidth;
};

#endif // MINIMAP_H
