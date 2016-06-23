#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdlib.h>
#include "Cam.h"
#include "GameLight.h"
#include "GameMap.h"
#include "GameSettings.h"


class Game
{
public:
    Game();
    virtual ~Game();
    Cam cam;
    GameLight light;
    GameMap game_map;
    GameSettings settings;

    bool backPressed;
    bool changeCamera;
    bool makeCrackPressed;
    bool pausePressed;
    bool pushPressed;
    bool rotateLeftPressed;
    bool rotateRightPressed;
    bool walkPressed;

private:
    const char* GAME_NAME = "Dig(lett) Dug(trio)";
    int windowWidth;
    int windowHeight;
    int windowXPos;
    int windowYPos;
    int mainWindowId;

    int MouseXPosition;
    int MouseYPosition;

    GLenum type;            /* Texture type */
    GLuint texture;         /* Texture object */
    float planeSize;

    void initTexture(void);

    void mainRender();
    void mainInit();
    void onKeyDown(unsigned char key, int x, int y);
    void onKeyUp(unsigned char key, int x, int y);
    void onMouseButton(int button, int state, int x, int y);
    void onMouseMove(int x, int y);
    void onMousePassiveMove(int x, int y);
    void onWindowReshape(int x, int y);

    void renderScene();
    void renderSea();
    void setViewport(GLint left, GLint right, GLint bottom, GLint top);
    void setWindow();

    void updateState();

};

#endif // GAME_H
