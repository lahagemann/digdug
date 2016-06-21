#ifndef GAME_H
#define GAME_H

#include "GameMap.h"
#include "GameSettings.h"
#include <string>

class Game
{
public:
    Game();
    virtual ~Game();
    GameMap game_map;
    GameSettings settings;
    Cam cam;
    bool walkPressed;
    bool backPressed;
    bool rotateLeftPressed;
    bool rotateRightPressed;
    bool changeCamera;
    bool makeCrackPressed;
    bool pushPressed;
    bool pausePressed;


private:
    const std::string GAME_NAME = "Dig(lett) Dug(trio)";
    int windowWidth = 600;
    int windowHeight = 480;
    int windowXPos = 100;
    int windowYPos = 150;

    int MouseXPosition = 0;
    int MouseYPosition = 0;

    void mainRender();
    void onKeyDown(unsigned char key, int x, int y);
    void onKeyUp(unsigned char key, int x, int y);
    void onMouseButton(int button, int state, int x, int y);
    void onMouseMove(int x, int y);
    void onMousePassiveMove(int x, int y);
    void onWindowReshape(int x, int y);
};

#endif // GAME_H
