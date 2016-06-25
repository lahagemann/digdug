#include "MiniMap.h"

MiniMap::MiniMap()
{
    miniMapWidth = 150;
    miniMapHeight = 120;
}

MiniMap::MiniMap(int windowWidth, int windowHeight)
{
    miniMapWidth = windowWidth/4;
    miniMapHeight = windowHeight/4;
}

MiniMap::~MiniMap()
{
    //dtor
}

void MiniMap::showMiniMap(Diglett player)
{
    glViewport(10, 10, miniMapWidth, miniMapHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, miniMapWidth/miniMapHeight, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    miniMapCam.setUpperCam();
    miniMapCam.updateCam(player);
}
