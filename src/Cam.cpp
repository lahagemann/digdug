#include "Cam.h"

Cam::Cam(Diglett player)
{
    camOption = THIRD_PERSON_CAM_OPTION;
    updateCam(player);
}

Cam::~Cam()
{
    //dtor
}

void Cam::updateCam(Diglett player)
{
    if(camOption == UPPER_CAM_OPTION)
        setUpperCam();

    else if(camOption == FIRST_PERSON_CAM_OPTION)
        setFirstPersonCam(player);

    else if(camOption == THIRD_PERSON_CAM_OPTION)
        setThirdPersonCam(player);

    /*gluLookAt(posX, posY + 0.025 * std::abs(sin(player.getHeadPosition()*PI/180)), posZ,
		posX + sin(rotY*PI/180), posY + 0.025 * std::abs(sin(player.getHeadPosition()*PI/180)) + cos(rotX*PI/180), posZ -cos(rotY*PI/180),
		0.0, 1.0, 0.0);*/
}

void Cam::setUpperCam()
{
    camOption = UPPER_CAM_OPTION;

    posX = 1;
    posY = 1;
    posZ = 1;
}

void Cam::setFirstPersonCam(Diglett player)
{
    camOption = FIRST_PERSON_CAM_OPTION;

    posX = player.getPosition().x;
    posY = player.getPosition().y;
    posZ = player.getPosition().z;
}

void Cam::setThirdPersonCam(Diglett player)
{
    camOption = THIRD_PERSON_CAM_OPTION;

    posX = player.getPosition().x;
    posY = player.getPosition().y;
    posZ = player.getPosition().z;
}
