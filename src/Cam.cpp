#include "Cam.h"

Cam::Cam()
{
    camOption = THIRD_PERSON_CAM_OPTION;
}

Cam::Cam(Diglett player)
{
    camOption = THIRD_PERSON_CAM_OPTION;
    updateCam(player);
}

Cam::~Cam()
{
    //dtor
}

void Cam::changeCam(Diglett player)
{
    if(camOption == UPPER_CAM_OPTION)
        setThirdPersonCam(player);

    else if(camOption == FIRST_PERSON_CAM_OPTION)
        setUpperCam();

    else if(camOption == THIRD_PERSON_CAM_OPTION)
        setFirstPersonCam(player);
}

int Cam::getCurrentCamOption()
{
    return this->camOption;
}

bool Cam::isUpperCam()
{
    if(camOption == UPPER_CAM_OPTION)
        return true;
    else
        return false;
}

void Cam::setFirstPersonCam(Diglett player)
{
    camOption = FIRST_PERSON_CAM_OPTION;

    float posX, posY, posZ;
    player.getPosition().convert_to_xz(&posX, &posZ);
    posY = 1.2f;
    posZ -= 0.2f;

    float xRotation = player.getXRotation();
    float yRotation = player.getYRotation();

    gluLookAt(posX, posY + 0.025 * std::abs(sin(player.getHeadPosition()*PI/180)), posZ,
		posX + sin(yRotation*PI/180), posY + 0.025 * std::abs(sin(player.getHeadPosition()*PI/180)) + cos(xRotation*PI/180), posZ -cos(yRotation*PI/180),
		0.0, 1.0, 0.0);
}

void Cam::setThirdPersonCam(Diglett player)
{
    camOption = THIRD_PERSON_CAM_OPTION;

    float posX, posY, posZ;
    player.getPosition().convert_to_xz(&posX, &posZ);
    posY = 1.5f;
    posZ += 3.0f;

    float xRotation = player.getXRotation();
    float yRotation = player.getYRotation();

    gluLookAt(posX, posY, posZ,
		posX + sin(yRotation*PI/180), posY + cos(xRotation*PI/180), posZ - cos(yRotation*PI/180),
		0.0, 1.0, 0.0);
}

void Cam::setUpperCam()
{
    camOption = UPPER_CAM_OPTION;

    gluLookAt(0.0, 30.0, 10.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

void Cam::updateCam(Diglett player)
{
    if(camOption == UPPER_CAM_OPTION)
        setUpperCam();

    else if(camOption == FIRST_PERSON_CAM_OPTION)
        setFirstPersonCam(player);

    else if(camOption == THIRD_PERSON_CAM_OPTION)
        setThirdPersonCam(player);
}
