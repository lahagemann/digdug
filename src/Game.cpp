#include "Game.h"

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(windowXPos, windowYPos);

	// Store main window id so that glui can send it redisplay events
	mainWindowId = glutCreateWindow(GAME_NAME);
	glutDisplayFunc(mainRender);
	glutReshapeFunc(onWindowReshape);

	// Register mouse events handlers
	glutMouseFunc(onMouseButton);
	glutMotionFunc(onMouseMove);
	glutPassiveMotionFunc(onMousePassiveMove);

	// Register keyboard events handlers
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);
	mainInit();
	glutMainLoop();

    return 0;
}

void Game::mainRender()
{
    updateState();
	renderScene();
	glFlush();
	glutPostRedisplay();
	Sleep(30);
}

void Game::onKeyDown(unsigned char key, int x, int y)
{
    switch(tolower(key))
    {
        case settings.walk_forward:
            walkPressed = true;
            break;
        case settings.walk_back:
            backPressed = true;
            break;
        case settings.rotate_right:
            rotateRightPressed = true;
            break;
        case settings.rotate_left:
            rotateLeftPressed = true;
            break;
        case settings.change_camera:
            changeCamera = true;
            break;
        case settings.make_crack:
            makeCrackPressed = true;
            break;
        case settings.push_enemy:
            pushPressed = true;
            break;
        case settings.pause:
            pausePressed = true;
            break;
        case settings.quit:
            exit(0);
        default:
            break;
    }
}

void Game::onKeyUp(unsigned char key, int x, int y)
{
    switch(tolower(key))
    {
        case settings.walk_forward:
            walkPressed = false;
            break;
        case settings.walk_back:
            backPressed = false;
            break;
        case settings.rotate_right:
            rotateRightPressed = false;
            break;
        case settings.rotate_left:
            rotateLeftPressed = false;
            break;
        case settings.change_camera:
            changeCamera = false;
            break;
        case settings.make_crack:
            makeCrackPressed = false;
            break;
        case settings.push_enemy:
            pushPressed = false;
            break;
        case settings.pause:
            pausePressed = false;
            break;
        case settings.quit:
            exit(0);
        default:
            break;
    }
}

void Game::onMouseButton(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void Game::onMouseMove(int x, int y)
{
    glutPostRedisplay();
}

void Game::onMousePassiveMove(int x, int y)
{
    game_map.player.setXRotation(y - MouseYPosition);
    game_map.player.setYRotation(x - MouseXPosition);

	if(game_map.player.getXRotation() < -128.0)
		game_map.player.getXRotation() = -128.0;

	if(game_map.player.getXRotation() > -45.0)
		game_map.player.getXRotation() = -45.0;

	MouseXPosition = x;
	MouseYPosition = y;
}

void Game::onWindowReshape(int x, int y)
{
    windowWidth = x;
	windowHeight = y;
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);
}

void Game::updateState()
{
    if(walkPressed)
    {
        // atualizar a posi��o do diglett.
    }

    if(backPressed)
    {
        // atualiza a posi��o do diglett.
    }

    if(rotateLeftPressed)
    {

    }

    if(rotateRightPressed)
    {

    }

    if(makeCrackPressed)
    {

    }

    if(pushPressed)
    {

    }
}
