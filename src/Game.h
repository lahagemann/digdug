#ifndef GAME_H
#define GAME_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
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
    int windowWidth = 600;
    int windowHeight = 480;
    int windowXPos = 100;
    int windowYPos = 150;

    int MouseXPosition = 0;
    int MouseYPosition = 0;
    int mainWindowId = 0;

    GLenum type;            /* Texture type */
    GLuint texture;         /* Texture object */
    float planeSize = 15.5f;

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
