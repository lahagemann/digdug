#include "Cam.h"

Cam::Cam()
{
    camOption = THIRD_PERSON_CAM_OPTION;
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
    player.getPosition().convert_to_xz(&posZ, &posX);
    posY = 1.2f;
    posZ -= 0.2f;

    float xRotation = player.getXRotation();
    float yRotation = player.getYRotation();

    gluLookAt(posX, posY, posZ,
		posX + sin(yRotation*PI/180), posY + cos(xRotation*PI/180), posZ - cos(yRotation*PI/180),
		0.0, 1.0, 0.0);
}

void Cam::setThirdPersonCam(Diglett player)
{
    camOption = THIRD_PERSON_CAM_OPTION;

    float posX, posZ;
    player.getPosition().convert_to_xz(&posX, &posZ);

    float yRotation = player.getYRotation();
    float camXDistance = posX;
    float camYDistance = 1.5f;
    float camZDistance = posZ;

    if(player.getYRotation() == 0.0f)
        camXDistance -= 3.0f;
    else if(player.getYRotation() == 90.0f)
        camZDistance += 3.0f;
    else if(player.getYRotation() == 180.0f)
        camXDistance += 3.0f;
    else if(player.getYRotation() == 270.0f)
        camZDistance -= 3.0f;

    gluLookAt(camXDistance, camYDistance, camZDistance,
		posX, camYDistance - 0.3f, posZ,
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
