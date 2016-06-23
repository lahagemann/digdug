#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#endif
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdlib.h>

#include "../../src/Cam.h"
#include "../../src/GameLight.h"
#include "../../src/GameMap.h"
#include "../../src/GameSettings.h"

/* function declaration */
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

/* global var declaration */
const char* GAME_NAME = "Dig(lett) Dug(trio)";
int mainWindowId = 0;
int MouseXPosition = 0;
int MouseYPosition = 0;
float planeSize = 31.0f;
GLuint texture;         /* Texture object */
GLenum type;            /* Texture type */
int windowHeight = 480;
int windowWidth = 600;
int windowXPos = 100;
int windowYPos = 150;

/* game objects declaration */
Cam cam;
GameLight light;
GameMap game_map;
GameSettings settings;

/* key pressing verification */
bool backPressed;
bool changeCamera;
bool makeCrackPressed;
bool pausePressed;
bool pushPressed;
bool rotateLeftPressed;
bool rotateRightPressed;
bool walkPressed;

void initTexture()
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

void mainInit()
{
    glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);

	// habilita o z-buffer
	glEnable(GL_DEPTH_TEST);
    initTexture();
}

void mainRender()
{
    updateState();
	renderScene();
	glFlush();
	glutPostRedisplay();
	Sleep(30);
}

void onKeyDown(unsigned char key, int x, int y)
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

void onKeyUp(unsigned char key, int x, int y)
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

void onMouseButton(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void onMouseMove(int x, int y)
{
    glutPostRedisplay();
}

void onMousePassiveMove(int x, int y)
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

void onWindowReshape(int x, int y)
{
    windowWidth = x;
	windowHeight = y;
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);
}

void renderScene()
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

    for(int i = 0; i < game_map.stage_map.size(); i++)
    {
        for(int j = 0; j < game_map.stage_map.at(i).size(); j++)
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

void renderSea()
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

void setViewport(GLint left, GLint right, GLint bottom, GLint top)
{
	glViewport(left, bottom, right - left, top - bottom);
}

void setWindow()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight,0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void updateState()
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
        game_map.push();

    if(changeCamera)
    {
        cam.changeCam(game_map.player);
        changeCamera = false;
    }

    game_map.moveEnemies();

    if(game_map.isPlayerDead())
            //death
}

/* Program entry point */

int main(int argc, char *argv[])
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
