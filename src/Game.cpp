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

void Game::initTexture()
{
    BITMAPINFO	*info;           /* Bitmap information */
    GLubyte	    *rgba;           /* RGBA pixel buffer */
    GLubyte	    *rgbaptr;        /* Pointer into RGBA buffer */

    // Load a texture object (256x256 true color)
    bits = LoadDIBitmap("tiledbronze.bmp", &info);
    if (bits == (GLubyte *)0)
		return;

    // Figure out the type of texture
    if (info->bmiHeader.biHeight == 1)
      type = GL_TEXTURE_1D;
    else
      type = GL_TEXTURE_2D;

    // Create and bind a texture object
    glGenTextures(1, &texture);
	glBindTexture(type, texture);

    // Create an RGBA image
    rgba = (GLubyte *)malloc(info->bmiHeader.biWidth * info->bmiHeader.biHeight * 4);

    int i = info->bmiHeader.biWidth * info->bmiHeader.biHeight;
    for( rgbaptr = rgba, ptr = bits;  i > 0; i--, rgbaptr += 4, ptr += 3)
    {
            rgbaptr[0] = ptr[2];     // windows BMP = BGR
            rgbaptr[1] = ptr[1];
            rgbaptr[2] = ptr[0];
            rgbaptr[3] = (ptr[0] + ptr[1] + ptr[2]) / 3;
    }

	// Set texture parameters
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(type, 0, 4, info->bmiHeader.biWidth, info->bmiHeader.biHeight,
                  0, GL_RGBA, GL_UNSIGNED_BYTE, rgba );
}

void Game::mainInit()
{
    glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);

	// habilita o z-buffer
	glEnable(GL_DEPTH_TEST);
    initTexture();
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

    float x, z;
	// loading player...

	game_map.player.getPosition().convert_to_xz(&x, &z);

	glPushMatrix();
        glTranslatef(x,0.0f,z);
        glmDraw(game_map.player.getModel(), GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    glPopMatrix();

    // loading enemies...
    for(int i = 0; i < game_map.characters.size(); i++)
    {
        Character c = game_map.characters.at(i);
        c.getPosition().convert_to_xz(&x, &z);

        glPushMatrix();
            glTranslatef(x,0.0f,z);
            glmDraw(c.getModel(), GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
        glPopMatrix();
    }

    for(int i = 0; i < game_map.stage_map.size())
    {
        for(int j = 0; j < game_map.stage_map.at(i).size())
        {
            A_RGB rgb = game_map.stage_map.at(i).at(j);
            if(rgb.isBlack())
            {
                Hole hole = Hole(i,j);
                hole.getPosition().convert_to_xz(&x, &z);

                glPushMatrix();
                    glTranslatef(x,-0.5f,z);
                    glmDraw(hole.getModel(), GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            }
            else if(rgb.isGreen())
            {
                Floor floor = Floor(i,j);
                floor.getPosition().convert_to_xz(&x, &z);

                glPushMatrix();
                    glTranslatef(x,-0.5f,z);
                    glmDraw(floor.getModel(), GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            }
            else if(rgb.isRed())
            {
                Crack crack = Crack(i,j);
                crack.getPosition().convert_to_xz(&x, &z);

                glPushMatrix();
                    glTranslatef(x,-0.5f,z);
                    glmDraw(crack.getModel(), GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            }
        }
    }

    glBindTexture(type, texture);

	renderSea();
}

void Game::renderSea()
{
    // set things up to render the floor with the texture
	glShadeModel(GL_SMOOTH);
	glEnable(type);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

    glTranslatef(-(float)planeSize/2.0f, 0.0f, -(float)planeSize/2.0f);

	float textureScaleX = 10.0;
	float textureScaleY = 10.0;
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    int xQuads = 40;
    int zQuads = 40;
    for (int i = 0; i < xQuads; i++) {
        for (int j = 0; j < zQuads; j++) {
            glBegin(GL_QUADS);
                glTexCoord2f(1.0f, 0.0f);   // coords for the texture
                glNormal3f(0.0f,1.0f,0.0f);
                glVertex3f(i * (float)planeSize/xQuads, 0.0f, (j+1) * (float)planeSize/zQuads);

                glTexCoord2f(0.0f, 0.0f);  // coords for the texture
                glNormal3f(0.0f,1.0f,0.0f);
                glVertex3f((i+1) * (float)planeSize/xQuads, 0.0f, (j+1) * (float)planeSize/zQuads);

                glTexCoord2f(0.0f, 1.0f);  // coords for the texture
                glNormal3f(0.0f,1.0f,0.0f);
                glVertex3f((i+1) * (float)planeSize/xQuads, 0.0f, j * (float)planeSize/zQuads);

                glTexCoord2f(1.0f, 1.0f);  // coords for the texture
                glNormal3f(0.0f,1.0f,0.0f);
                glVertex3f(i * (float)planeSize/xQuads, 0.0f, j * (float)planeSize/zQuads);

            glEnd();
        }
    }

	glDisable(type);
	glPopMatrix();
}

void Game::setViewport(GLint left, GLint right, GLint bottom, GLint top)
{
	glViewport(left, bottom, right - left, top - bottom);
}

void Game::setWindow()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight,0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
        // verifica a direção para a qual o player está virado
        // se há um inimigo na célula ao lado, desloca a posição do inimigo em 2 células na direção da rotação do player.
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
