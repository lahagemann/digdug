#include "GameLight.h"

GameLight::GameLight()
{
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

GameLight::~GameLight()
{
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void GameLight::makeLight()
{
    glClearColor(skyColor.r/255.0f, skyColor.g/255.0f, skyColor.b/255.0f, 1.0);

    GLfloat light_ambient[] = {skyColor.r/255.0f, skyColor.g/255.0f, skyColor.b/255.0f, 1.0};
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat light_direction[] = {0.0, 0.0, -1.0, 1.0};

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
}
