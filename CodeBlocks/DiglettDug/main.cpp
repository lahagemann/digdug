#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#endif
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../src/Cam.h"
#include "../../src/GameLight.h"
#include "../../src/GameMap.h"
#include "../../src/GameSettings.h"
#include "../../src/Ground.h"
#include "../../src/Model.h"

/* function declaration */
void initTexture(void);
bool load_new_model(const char *pszFilename, GLMmodel **model);
void loadEnemies();
void loadIsland();
void loadPlayer();
void mainRender();
void mainInit();
void miniMapRender();
void onKeyDown(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);
void onMouseButton(int button, int state, int x, int y);
void onMouseMove(int x, int y);
void onMousePassiveMove(int x, int y);
void onWindowReshape(int x, int y);
void renderScene(bool miniMapOption);
void renderSea();
void setViewport(GLint left, GLint right, GLint bottom, GLint top);
void setWindow();
void showGameTime();
void updateState();

/* global var declaration */
const char* GAME_NAME = "Dig(lett) Dug(trio)";
clock_t initialTime;
int mainWindowId = 0;
int subWindowId = 0;
int MouseXPosition = 0;
int MouseYPosition = 0;
float planeSize = 40.0f;
GLuint texture;         /* Texture object */
GLenum type;            /* Texture type */
int windowHeight = 480;
int windowWidth = 600;
int windowXPos = 100;
int windowYPos = 150;

/* game objects declaration */
Cam cam;
Cam miniMapCam;
GameLight light;
GameMap game_map = GameMap();
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

/* static models */
GLMmodel *cube;
GLMmodel *cube_crack;
GLMmodel *cube_hole;
GLMmodel *diglettModel;
GLMmodel *scytherModel;
GLMmodel *sharpedoModel;
GLMmodel *snorlaxModel;

int getGameTime()
{
    return (clock() - initialTime) / (double)CLOCKS_PER_SEC;
}

void initTexture()
{
    BITMAPINFO	*info;           /* Bitmap information */
    GLubyte	    *bits;           /* Bitmap RGB pixels */
    GLubyte     *ptr;            /* Pointer into bit buffer */
    GLubyte	    *rgba;           /* RGBA pixel buffer */
    GLubyte	    *rgbaptr;        /* Pointer into RGBA buffer */

    // Load a texture object (256x256 true color)
    bits = LoadDIBitmap("Textures\\Sea.bmp", &info);
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

bool load_new_model(const char *pszFilename, GLMmodel **model)
{
    char aszFilename[256];
    strcpy(aszFilename, pszFilename);

    if (*model)
    {
        free(*model);
        *model = NULL;
    }

    *model = glmReadOBJ(aszFilename);
    if (!(*model))
        return false;

    glmUnitize(*model);
    glmFacetNormals(*model);
    glmVertexNormals(*model, 90.0);

    return true;
}

void loadEnemies()
{
    float x, z;

    for(int i = 0; i < game_map.getScythers().size(); i++)
    {
        Scyther schyther = game_map.getScythers().at(i);
        schyther.getPosition().convert_to_xz(&x, &z);

        glPushMatrix();
            glTranslatef(x,0.5f,z);
            glRotatef(schyther.getYRotation(),0.0f,1.0f,0.0f);
            glmDraw(scytherModel, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
        glPopMatrix();
    }

    for(int i = 0; i < game_map.getSharpedos().size(); i++)
    {
        Sharpedo sharpedo = game_map.getSharpedos().at(i);
        sharpedo.getPosition().convert_to_xz(&x, &z);

        glPushMatrix();
            glTranslatef(x,-0.5f,z);
            glRotatef(sharpedo.getYRotation(),0.0f,1.0f,0.0f);
            glmDraw(sharpedoModel, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
        glPopMatrix();
    }

    for(int i = 0; i < game_map.getSnorlaxs().size(); i++)
    {
        Snorlax snorlax = game_map.getSnorlaxs().at(i);
        snorlax.getPosition().convert_to_xz(&x, &z);

        glPushMatrix();
            glTranslatef(x,0.2f,z);
            glRotatef(snorlax.getYRotation(),0.0f,1.0f,0.0f);
            glRotatef(270.0f,1.0f,0.0f,0.0f);
            glmDraw(snorlaxModel, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
        glPopMatrix();
    }
}

void loadIsland()
{
    float x, z;

    for(int i = 0; i < game_map.getStageMap().size(); i++)
    {
        for(int j = 0; j < game_map.getStageMap().at(i).size(); j++)
        {
            A_RGB rgb = game_map.getStageMap().at(i).at(j);
            if(rgb.isBlack())
            {
                Ground hole = Ground(i,j);
                hole.getPosition().convert_to_xz(&x, &z);

                glPushMatrix();
                    glTranslatef(x,-0.5f,z);
                    glScalef(0.5f,0.5f,0.5f);
                    glmDraw(cube_hole, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            }
            else if(rgb.isGreen())
            {
                Ground floor = Ground(i,j);
                floor.getPosition().convert_to_xz(&x, &z);

                glPushMatrix();
                    glTranslatef(x,-0.5f,z);
                    glScalef(0.5f,0.5f,0.5f);
                    glmDraw(cube, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            }
            else if(rgb.isRed())
            {
                Ground crack = Ground(i,j);
                crack.getPosition().convert_to_xz(&x, &z);

                glPushMatrix();
                    glTranslatef(x,-0.5f,z);
                    glScalef(0.5f,0.5f,0.5f);
                    glmDraw(cube_crack, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
                glPopMatrix();
            }
        }
    }
}

void loadPlayer()
{
    float x, z;

    game_map.player.getPosition().convert_to_xz(&x, &z);

    glPushMatrix();
        glTranslatef(x,0.3f,z);
        glRotatef(game_map.player.getYRotation(),0.0f,1.0f,0.0f);
        glScalef(0.5f,0.5f,0.5f);
        glmDraw(diglettModel, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    glPopMatrix();
}

void mainIdle() {
	glutSetWindow(mainWindowId);
	glutPostRedisplay();
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

    // inicializa todos os modelos 3D que serão multiplicados
    diglettModel = (GLMmodel*)malloc(sizeof(GLMmodel));
    scytherModel = (GLMmodel*)malloc(sizeof(GLMmodel));
    sharpedoModel = (GLMmodel*)malloc(sizeof(GLMmodel));
    snorlaxModel = (GLMmodel*)malloc(sizeof(GLMmodel));
    cube = (GLMmodel*)malloc(sizeof(GLMmodel));
    cube_hole = (GLMmodel*)malloc(sizeof(GLMmodel));
    cube_crack = (GLMmodel*)malloc(sizeof(GLMmodel));

    load_new_model("Diglett.obj", &diglettModel);
    load_new_model("Scyther.obj", &scytherModel);
    load_new_model("Sharpedo.obj", &sharpedoModel);
    load_new_model("Snorlax.obj", &snorlaxModel);
    load_new_model("cube.obj", &cube);
    load_new_model("cube_hole.obj", &cube_hole);
    load_new_model("cube_crack.obj", &cube_crack);
}

void mainRender()
{
    updateState();
	renderScene(false);
	glFlush();
	glutPostRedisplay();
	Sleep(30);
}

void miniMapRender()
{
    if(!cam.isUpperCam())
    {
        glutSetWindow(subWindowId);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        renderScene(true);
        glFlush();
        glutPostRedisplay();
    }
}

void onKeyDown(unsigned char key, int x, int y)
{
    if(tolower(key) == settings.walk_forward)
        walkPressed = true;

    else if(tolower(key) == settings.walk_back)
        backPressed = true;

    else if(tolower(key) == settings.rotate_right)
        rotateRightPressed = true;

    else if(tolower(key) == settings.rotate_left)
        rotateLeftPressed = true;

    else if(tolower(key) == settings.change_camera)
        changeCamera = true;

    else if(tolower(key) == settings.make_crack)
        makeCrackPressed = true;

    else if(tolower(key) == settings.push_enemy)
        pushPressed = true;

    else if(tolower(key) == settings.pause)
        pausePressed = true;

    else if(tolower(key) == settings.quit)
        exit(0);
}

void onKeyUp(unsigned char key, int x, int y)
{
    if(tolower(key) == settings.walk_forward)
        walkPressed = false;

    else if(tolower(key) == settings.walk_back)
        backPressed = false;

    else if(tolower(key) == settings.rotate_right)
        rotateRightPressed = false;

    else if(tolower(key) == settings.rotate_left)
        rotateLeftPressed = false;

    else if(tolower(key) == settings.change_camera)
        changeCamera = false;

    else if(tolower(key) == settings.make_crack)
        makeCrackPressed = false;

    else if(tolower(key) == settings.push_enemy)
        pushPressed = false;

    else if(tolower(key) == settings.pause)
        pausePressed = false;

    else if(tolower(key) == settings.quit)
        exit(0);
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
    if(cam.getCurrentCamOption() == 2)
    {
        game_map.player.setXRotation(y - MouseYPosition);
        game_map.player.setYRotation(x - MouseXPosition);

        if(game_map.player.getXRotation() < -128.0)
            game_map.player.setXRotation(-128.0);

        if(game_map.player.getXRotation() > -45.0)
            game_map.player.setXRotation(-45.0);

        MouseXPosition = x;
        MouseYPosition = y;
    }

}

void onWindowReshape(int x, int y)
{
    windowWidth = x;
	windowHeight = y;
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);
}

void renderScene(bool miniMapOption)
{
    light.makeLight();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // limpar o depth buffer

    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(miniMapOption)
        miniMapCam.setMiniMapCam();
    else
        cam.updateCam(game_map.player);

	loadPlayer();
	loadEnemies();
	loadIsland();
    glBindTexture(type, texture);
	renderSea();
	showGameTime();
}

void renderSea()
{
    // set things up to render the floor with the texture
	glShadeModel(GL_SMOOTH);
	glEnable(type);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glPushMatrix();

    glTranslatef(-(float)planeSize/2.0f, 0.2f, -(float)planeSize/2.0f);

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
                glVertex3f(i * (float)planeSize/xQuads, -1.0f, (j+1) * (float)planeSize/zQuads);

                glTexCoord2f(0.0f, 0.0f);  // coords for the texture
                glNormal3f(0.0f,1.0f,0.0f);
                glVertex3f((i+1) * (float)planeSize/xQuads, -1.0f, (j+1) * (float)planeSize/zQuads);

                glTexCoord2f(0.0f, 1.0f);  // coords for the texture
                glNormal3f(0.0f,1.0f,0.0f);
                glVertex3f((i+1) * (float)planeSize/xQuads, -1.0f, j * (float)planeSize/zQuads);

                glTexCoord2f(1.0f, 1.0f);  // coords for the texture
                glNormal3f(0.0f,1.0f,0.0f);
                glVertex3f(i * (float)planeSize/xQuads, -1.0f, j * (float)planeSize/zQuads);

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

void showGameTime()
{
    /*char* cronometer;
    sprintf(cronometer, "Time: %d\0", getGameTime());

    glLoadIdentity();
    glRasterPos2f(1500, 1500);
    for(int i = 0; i < strlen(cronometer); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cronometer[i]);
    glPopMatrix();*/
}

void updateState()
{
    if(walkPressed)
        if(!game_map.checkObstacleCollision(Character::forwards))
            game_map.player.walk(Character::forwards);

    if(backPressed)
        if(!game_map.checkObstacleCollision(Character::backwards))
            game_map.player.walk(Character::backwards);

    if(rotateLeftPressed)
        game_map.player.walk(Character::rotateLeft);

    if(rotateRightPressed)
        game_map.player.walk(Character::rotateRight);

    if(makeCrackPressed)
        game_map.makeCrack();

    if(pushPressed)
        game_map.push(getGameTime());

    if(changeCamera)
    {
        cam.changeCam(game_map.player);
        changeCamera = false;
    }

    game_map.moveEnemies();

    if(game_map.isPlayerDead())
        exit(0);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    initialTime = clock();

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

	subWindowId = glutCreateSubWindow(mainWindowId, 0, 0,(windowWidth/3) - 40, (windowHeight/3) - 40);
	glutDisplayFunc(miniMapRender);
    mainInit();

	glutMainLoop();

    return 0;
}
