/**
Laboratorio FCG - Pratica 4
Ultima modificacao: 09/05/2016 - Acompanha bibliotecas: bitmap.c(.h), glm.cpp,
glmimg.cpp, Texture.cpp(Texture.h)

Implementa a movimenta��o simples de uma camera em primeira pessoa para um personagem que anda
sobre um plano. Utiliza a biblioteca bitmap para carregamento simples de texturas, glm
para modelos OBJ e glmimg + Texture para aplicacao de texturas TGA sobre os modelos carregados

Tarefas:

1 - Adicionar neblina � cena ao implementar a fun��o enableFog() com os par�metros de habilita��o de fog em OpenGL;
2 - Usar uma imagem no formato BMP como mapa pra posicionar objetos 3D na cena. Use a cor de cada pixel para definir
qual modelo ser� colocado e a posi��o do pixel para definir a posi��o do modelo no espa�o. Pixels pretos n�o representam
nenhum modelo, fazendo com que a posi��o fique vazia na cena;
3 - Mudar as configura��es da fonte de luz da cena, j� implementada no c�digo base dado, para que
seja uma spotlight;
4 - Adicionar uma segunda fonte de luz que fique girando ao redor do cen�rio.
*/

#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <gl/glut.h>

#include "glm.h"

//openal (sound lib)
#include <al/alut.h>

//bitmap class to load bitmaps for textures
#include "bitmap.h"

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

#define PI 3.14159265

// sound stuff
#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

#define SMOOTH 0
#define SMOOTH_MATERIAL 1
#define SMOOTH_MATERIAL_TEXTURE 2

void mainInit();
void initSound();
void initTexture();
void initModel();
void initLight();
void enableFog();
void createGLUI();
void mainRender();
void mainCreateMenu();
void onMouseButton(int button, int state, int x, int y);
void onMouseMove(int x, int y);
void onKeyDown(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);
void onGLUIEvent(int id);
void onWindowReshape(int x, int y);
void mainIdle();
int main(int argc, char **argv);
void setWindow();
void setViewport(GLint left, GLint right, GLint bottom, GLint top);
void updateState();
void renderFloor();
void updateCam();

/**
Screen dimensions
*/
int windowWidth = 600;
int windowHeight = 480;

/**
Screen position
*/
int windowXPos = 100;
int windowYPos = 150;

int mainWindowId = 0;

double xOffset = -1.9;
double yOffset = -1.3;
int mouseLastX = 0;
int mouseLastY = 0;

float roty = 0.0f;
float rotx = 90.0f;
float sphereYRot = 0.0f;

int angle;

bool rightPressed = false;
bool leftPressed = false;
bool upPressed = false;
bool downPressed = false;

bool spacePressed = false;

float speedX = 0.0f;
float speedY = 0.0f;
float speedZ = 0.0f;

float posX = 0.0f;
float posY = 0.0f;
float posZ = 2.0f;

/*
variavel auxiliar pra dar varia��o na altura do ponto de vista ao andar.
*/
float headPosAux = 0.0f;

float maxSpeed = 0.25f;

float planeSize = 20.0f;

// more sound stuff (position, speed and orientation of the listener)
ALfloat listenerPos[]={0.0,0.0,4.0};
ALfloat listenerVel[]={0.0,0.0,0.0};
ALfloat listenerOri[]={0.0,0.0,1.0,
						0.0,1.0,0.0};

// now the position and speed of the sound source
ALfloat source0Pos[]={ -2.0, 0.0, 0.0};
ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

// buffers for openal stuff
ALuint  buffer[NUM_BUFFERS];
ALuint  source[NUM_SOURCES];
ALuint  environment[NUM_ENVIRONMENTS];
ALsizei size,freq;
ALenum  format;
ALvoid  *data;



// parte de c�digo extra�do de "texture.c" por Michael Sweet (OpenGL SuperBible)
// texture buffers and stuff
int i;                       /* Looping var */
BITMAPINFO	*info;           /* Bitmap information */
BITMAPINFO	*position;           /* Bitmap information */
GLubyte	    *bits;           /* Bitmap RGB pixels */
GLubyte     *ptr;            /* Pointer into bit buffer */
GLubyte	    *rgba;           /* RGBA pixel buffer */
GLubyte	    *rgbaptr;        /* Pointer into RGBA buffer */
GLubyte	    *pos;           /* RGBA pixel buffer */
GLubyte	    *posptr;        /* Pointer into RGBA buffer */
GLubyte     temp;            /* Swapping variable */
GLenum      type;            /* Texture type */
GLuint      texture;         /* Texture object */



bool crouched = false;
bool running = false;
bool jumping = false;
float jumpSpeed = 0.06;
float gravity = 0.004;
float heightLimit = 0.2;
float posYOffset = 0.2;

float backgrundColor[4] = {0.0f,0.0f,0.0f,1.0f};

typedef struct Magikarp {
    int x;
    int z;
    GLMmodel *model;
};

typedef struct Snorlax {
    int x;
    int z;
    GLMmodel *model;
};

Magikarp magikarps[400];
Snorlax snorlaxes[400];

GLMmodel *modelSphere;

// Aux function to load the object using GLM and apply some functions
bool C3DObject_Load_New(const char *pszFilename, GLMmodel **model)
{
    char aszFilename[256];
    strcpy(aszFilename, pszFilename);

    if (*model) {

    free(*model);
    *model = NULL;
    }

    *model = glmReadOBJ(aszFilename);
    if (!(*model))
    return false;

    glmUnitize(*model);
    //glmScale(model,sFactor); // USED TO SCALE THE OBJECT
    glmFacetNormals(*model);
    glmVertexNormals(*model, 90.0);

    return true;
}

void setWindow() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)windowWidth/(GLfloat)windowHeight,0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(posX,posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
		posX + sin(roty*PI/180),posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
		0.0,1.0,0.0);
}

/**
Atualiza a posi��o e orienta��o da camera
*/
void updateCam() {

	gluLookAt(posX,posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)),posZ,
		posX + sin(roty*PI/180),posY + posYOffset + 0.025 * std::abs(sin(headPosAux*PI/180)) + cos(rotx*PI/180),posZ -cos(roty*PI/180),
		0.0,1.0,0.0);

	// atualiza a posi��o do listener e da origen do som, s�o as mesmas da camera, j� que os passos vem de onde o personagem est�
	listenerPos[0] = posX;
	listenerPos[1] = posY;
	listenerPos[2] = posZ;
	source0Pos[0] = posX;
	source0Pos[1] = posY;
	source0Pos[2] = posZ;

    GLfloat light_position1[] = {posX, posY, posZ, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);


}

void initLight() {
    glEnable(GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable(GL_LIGHT1);

	GLfloat light_ambient[] = { backgrundColor[0], backgrundColor[1], backgrundColor[2], backgrundColor[3] };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position1[] = {0.0, 1.0, 0.0, 1.0 };
	GLfloat mat_emission[] = {10.0, 10.0, 0.0, 0.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
   // Cut off angle is 60 degrees
    glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,15.0f);
// Fairly shiny spot
    glLightf(GL_LIGHT0,GL_SPOT_EXPONENT,350.0f);


    //enable wiresphere light
	GLfloat light_position2[] = {0.0, 2.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

// Fairly shiny spot
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,550.0f);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);




}

void setViewport(GLint left, GLint right, GLint bottom, GLint top) {
	glViewport(left, bottom, right - left, top - bottom);
}


/**
Initialize
*/
void mainInit() {
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);

	// habilita o z-buffer
	glEnable(GL_DEPTH_TEST);

    initSound();

    initTexture();

	initModel();

	initLight();

	enableFog();

	printf("w - andar \n");
	printf("s - ir pra tras \n");
	printf("mouse - direcao \n");
	printf("r - correr \n");
	printf("c - abaixar \n");
	printf("espaco - pular \n");

}

void initModel() {
    printf("Loading models.. \n");

    bits = LoadDIBitmap("bitmap.bmp", &position);
    if (bits == (GLubyte *)0) {
		printf ("Error loading!\n\n");
		return;
	}
    // Figure out the type of texture
    if (position->bmiHeader.biHeight == 1)
      type = GL_TEXTURE_1D;
    else
      type = GL_TEXTURE_2D;

    // Create an RGBA image
    pos = (GLubyte *)malloc(position->bmiHeader.biWidth * position->bmiHeader.biHeight * 4);

    int karps = 0;
    int snore = 0;

    i = position->bmiHeader.biWidth * position->bmiHeader.biHeight-1;
    for( posptr = pos, ptr = bits;  i >= 0; i--, posptr += 4, ptr += 3)
    {
            posptr[0] = ptr[2];     // windows BMP = BGR
            posptr[1] = ptr[1];
            posptr[2] = ptr[0];
            posptr[3] = (ptr[0] + ptr[1] + ptr[2]) / 3;


            int r = posptr[0];
            int g = posptr[1] ;
            int b = posptr[2];

            //printf("r: %d g: %d b: %d\n",r,g,b);

            if(r == 255) {
                Magikarp karpa;
                karpa.x = 19 - (i/20);
                karpa.z = i%20;
                karpa.model = (GLMmodel *)malloc(sizeof(GLMmodel));
                C3DObject_Load_New("Magikarp.obj",&karpa.model);
                magikarps[karps] = karpa;
                karps++;
            }

            if(b == 255) {
                Snorlax big;
                big.x = 19 - (i/20);
                big.z = i%20;
                big.model = (GLMmodel *)malloc(sizeof(GLMmodel));
                C3DObject_Load_New("Snorlax.obj",&big.model);
                snorlaxes[snore] = big;
                snore++;
            }
    }

	printf("Models ok. \n \n \n");
}

/**
Initialize openal and check for errors
*/
void initSound() {

	printf("Initializing OpenAl \n");

	// Init openAL
	alutInit(0, NULL);

	alGetError(); // clear any error messages

    // Generate buffers, or else no sound will happen!
    alGenBuffers(NUM_BUFFERS, buffer);

    if(alGetError() != AL_NO_ERROR)
    {
        printf("- Error creating buffers !!\n");
        exit(1);
    }
    else
    {
        printf("init() - No errors yet.\n");
    }

	alutLoadWAVFile("Footsteps.wav",&format,&data,&size,&freq,false);
    alBufferData(buffer[0],format,data,size,freq);

	alGetError(); /* clear error */
    alGenSources(NUM_SOURCES, source);

    if(alGetError() != AL_NO_ERROR)
    {
        printf("- Error creating sources !!\n");
        exit(2);
    }
    else
    {
        printf("init - no errors after alGenSources\n");
    }

	listenerPos[0] = posX;
	listenerPos[1] = posY;
	listenerPos[2] = posZ;

	source0Pos[0] = posX;
	source0Pos[1] = posY;
	source0Pos[2] = posZ;

	alListenerfv(AL_POSITION,listenerPos);
    alListenerfv(AL_VELOCITY,listenerVel);
    alListenerfv(AL_ORIENTATION,listenerOri);

	alSourcef(source[0], AL_PITCH, 1.0f);
    alSourcef(source[0], AL_GAIN, 1.0f);
    alSourcefv(source[0], AL_POSITION, source0Pos);
    alSourcefv(source[0], AL_VELOCITY, source0Vel);
    alSourcei(source[0], AL_BUFFER,buffer[0]);
    alSourcei(source[0], AL_LOOPING, AL_TRUE);

	printf("Sound ok! \n\n");
}

/**
Initialize the texture using the library bitmap
*/
void initTexture(void)
{
    printf ("\nLoading texture..\n");
    // Load a texture object (256x256 true color)
    bits = LoadDIBitmap("tiledbronze.bmp", &info);
    if (bits == (GLubyte *)0) {
		printf ("Error loading texture!\n\n");
		return;
	}
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

    i = info->bmiHeader.biWidth * info->bmiHeader.biHeight;
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


    printf("Textura %d\n", texture);
	printf("Textures ok.\n\n", texture);

}

void enableFog(void)
{
    GLfloat density = 0.3;
    GLfloat fogColor[4] = {0.0, 0.0, 0.0, 1.0};
    glEnable(GL_FOG);
    glFogi (GL_FOG_MODE, GL_EXP2);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST);
}

void renderFloor() {
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

void renderScene() {
	glClearColor(backgrundColor[0],backgrundColor[1],backgrundColor[2],backgrundColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // limpar o depth buffer

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCam();

	/*
    glPushMatrix();
        glTranslatef(0.0,0.5,0.0);
        glScalef(0.5,0.5,0.5);
        glmDraw(modelSphere, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
	glPopMatrix();
    */
	int i;
	for(i=0;i<400;i++){
        Magikarp karp = magikarps[i];
        if(karp.model) {
            GLdouble pX,pZ;
            if(karp.x <= 9) {
                pX = -10.0 + double(karp.x);
                pX = pX + 0.5;
            } else {
                pX = double(karp.x) - 10.0 + 1.0;
                pX = pX - 0.5;
            }

            if(karp.z <= 9) {
                pZ = 10.0 - double(karp.z);
                pZ = pZ - 0.5;
            } else {
                pZ = 10.0 - double(karp.z) - 1.0;
                pZ = pZ + 0.5;
            }
            //printf("orig x %d curr x %f orig z %d curr z %f\n",karp.x, pX, karp.z, pZ);

            glPushMatrix();
                glTranslatef(pX,0.5,pZ);
                glScalef(0.5,0.5,0.5);
                glmDraw(karp.model, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
            glPopMatrix();
        }

        Snorlax snorlax = snorlaxes[i];
        if(snorlax.model) {
            GLdouble sX,sZ;
            if(snorlax.x <= 9) {
                sX = -10.0 + double(snorlax.x);
                sX = sX + 0.5;
            } else {
                sX = double(snorlax.x) - 10.0 + 1.0;
                sX = sX - 0.5;
            }

            if(snorlax.z <= 9) {
                sZ = 10.0 - double(snorlax.z);
                sZ = sZ - 0.5;
            } else {
                sZ = 10.0 - double(snorlax.z) - 1.0;
                sZ = sZ + 0.5;
            }
            //printf("orig x %d curr x %f orig z %d curr z %f\n",karp.x, pX, karp.z, pZ);

            glPushMatrix();
                glTranslatef(sX,0.5,sZ);
                glScalef(0.5,0.5,0.5);
                glmDraw(snorlax.model, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
            glPopMatrix();
        }
	}

	glColor3f(1.0f,1.0f,1.0f);
	GLfloat light_position2[] = {0.0, 2.0, 1.0, 0.0 };

	glPushMatrix();
        glRotatef(sphereYRot, 0.0f,1.0f,0.0f);
        glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
        glTranslatef(0.0f,2.0f,2.0f);
        glutWireSphere (0.2, 20, 20);
    glPopMatrix();

    sphereYRot += 2.0f;

    // binds the bmp file already loaded to the OpenGL parameters
    glBindTexture(type, texture);

	renderFloor();
}

void updateState() {

	if (upPressed || downPressed) {

		if (running) {
			speedX = 0.05 * sin(roty*PI/180) * 2;
			speedZ = -0.05 * cos(roty*PI/180) * 2;
		} else {
			speedX = 0.05 * sin(roty*PI/180);
			speedZ = -0.05 * cos(roty*PI/180);
		}

		// efeito de "sobe e desce" ao andar
		headPosAux += 8.5f;
		if (headPosAux > 180.0f) {
			headPosAux = 0.0f;
		}

        if (upPressed) {
            posX += speedX;
            posZ += speedZ;
        } else {
            posX -= speedX;
            posZ -= speedZ;
        }

	} else {
		// parou de andar, para com o efeito de "sobe e desce"
		headPosAux = fmod(headPosAux, 90) - 1 * headPosAux / 90;
		headPosAux -= 4.0f;
		if (headPosAux < 0.0f) {
			headPosAux = 0.0f;
		}
	}

	posY += speedY;
	if (posY < heightLimit) {
		posY = heightLimit;
		speedY = 0.0f;
		jumping = false;
	} else {
		speedY -= gravity;
	}

	if (crouched) {
		posYOffset -= 0.01;
		if (posYOffset < 0.1) {
			posYOffset = 0.1;
		}
	} else {
		posYOffset += 0.01;
		if (posYOffset > 0.2) {
			posYOffset = 0.2;
		}
	}

}

/**
Render scene
*/
void mainRender() {
	updateState();
	renderScene();
	glFlush();
	glutPostRedisplay();
	Sleep(30);
}

/**
Handles events from the mouse right button menu
*/
void mainHandleMouseRightButtonMenuEvent(int option) {
	switch (option) {
		case 1 :
			exit(0);
			break;
		default:
			break;
	}
}

/**
Create mouse button menu
*/
void mainCreateMenu() {
	glutCreateMenu(mainHandleMouseRightButtonMenuEvent);
	glutAddMenuEntry("Quit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
Mouse button event handler
*/
void onMouseButton(int button, int state, int x, int y) {
	//printf("onMouseButton button: %d \n", button);
	glutPostRedisplay();
}

/**
Mouse move while button pressed event handler
*/
void onMouseMove(int x, int y) {

	/*mouseLastX = x;
	mouseLastY = y;*/

	glutPostRedisplay();
}

/**
Mouse move with no button pressed event handler
*/
void onMousePassiveMove(int x, int y) {

	roty += (x - mouseLastX);

	rotx -= (y - mouseLastY);

	if (rotx < -128.0) {
		rotx = -128.0;
	}

	if (rotx > -45.0) {
		rotx = -45.0;
	}

	mouseLastX = x;
	mouseLastY = y;

	//glutPostRedisplay();
}

/**
Key press event handler
*/
void onKeyDown(unsigned char key, int x, int y) {
	//printf("%d \n", key);
	switch (key) {
		case 32: //space
			if (!spacePressed && !jumping) {
				jumping = true;
				speedY = jumpSpeed;
			}
			spacePressed = true;
			break;
		case 119: //w
			if (!upPressed) {
				alSourcePlay(source[0]);
			}
			upPressed = true;
			break;
		case 115: //s
			downPressed = true;
			break;
		case 97: //a
			leftPressed = true;
			break;
		case 100: //d
			rightPressed = true;
			break;
		case 99: //c
			crouched = true;
			break;
		case 114: //r
			running = true;
			break;
		default:
			break;
	}

	//glutPostRedisplay();
}

/**
Key release event handler
*/
void onKeyUp(unsigned char key, int x, int y) {
	switch (key) {
		case 32: //space
			spacePressed = false;
			break;
		case 119: //w
			if (upPressed) {
				alSourceStop(source[0]);
			}
			upPressed = false;
			break;
		case 115: //s
			downPressed = false;
			break;
		case 97: //a
			leftPressed = false;
			break;
		case 100: //d
			rightPressed = false;
			break;
		case 99: //c
			crouched = false;
			break;
		case 114: //r
			running = false;
			break;
		case 27:
			exit(0);
			break;
		default:
			break;
	}

	//glutPostRedisplay();
}

void onWindowReshape(int x, int y) {
	windowWidth = x;
	windowHeight = y;
	setWindow();
	setViewport(0, windowWidth, 0, windowHeight);
}

/**
Glut idle funtion
*/
void mainIdle() {
	/**
	Set the active window before send an glutPostRedisplay call
	so it wont be accidently sent to the glui window
	*/

	glutSetWindow(mainWindowId);
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(windowXPos,windowYPos);

	/**
	Store main window id so that glui can send it redisplay events
	*/
	mainWindowId = glutCreateWindow("FPS");

	glutDisplayFunc(mainRender);

	glutReshapeFunc(onWindowReshape);

	/**
	Register mouse events handlers
	*/
	glutMouseFunc(onMouseButton);
	glutMotionFunc(onMouseMove);
	glutPassiveMotionFunc(onMousePassiveMove);

	/**
	Register keyboard events handlers
	*/
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);

	mainInit();

	glutMainLoop();

    return 0;
}
