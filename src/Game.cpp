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

void Game::renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // limpar o depth buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCam();

	// loading player...
	float playerX, playerZ;
	game_map.player.getPosition().convert_to_xz(&playerX, &playerZ);

	glPushMatrix();
        glTranslatef(playerX,0.0f,playerZ);
        glmDraw(game_map.player.getModel(), GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    glPopMatrix();

    // loading enemies...
    for(int i = 0; i < game_map.characters.size(); i++)
    {
        Character c = game_map.characters.at(i);
        float enemyX, enemyZ;
        c.getPosition().convert_to_xz(&enemyX, &enemyZ);

        glPushMatrix();
            glTranslatef(enemyX,0.0f,enemyZ);
            glmDraw(c.getModel(), GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
        glPopMatrix();
    }

    for(int i = 0; i < game_map.stage_map.size())
    {
        for(int j = 0; j < game_map.stage_map.at(i).size())
        {
            A_RGB rgb = game_map.stage_map.at(i).at(j);
        }
    }

}

void Game::updateState()
{
    if(walkPressed)
    {
        if(!game_map.checkObstacleCollision())
            game_map.player.walk(Diglett::Direction::forwards);
    }


    if(backPressed)
    {
        if(!game_map.checkObstacleCollision())
            game_map.player.walk(Diglett::Direction::forwards);
    }

    if(rotateLeftPressed)
        game_map.player.walk(Diglett::Direction::rotateLeft);

    if(rotateRightPressed)
        game_map.player.walk(Diglett::Direction::rotateRight);

    if(makeCrackPressed)
        game_map.makeCrack();

    if(pushPressed)
    {
        game_map.push();
        // verifica a dire��o para a qual o player est� virado
        // se h� um inimigo na c�lula ao lado, desloca a posi��o do inimigo em 2 c�lulas na dire��o da rota��o do player.
    }

    if(changeCamera)
    {
        cam.changeCam(game_map.player);
        changeCamera = false;
    }

    game_map.moveEnemies();

    if(game_map.isPlayerDead())
            //death
}
