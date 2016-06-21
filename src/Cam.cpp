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

void Cam::updateCam(Diglett player)
{
    if(camOption == UPPER_CAM_OPTION)
        setUpperCam();

    else if(camOption == FIRST_PERSON_CAM_OPTION)
        setFirstPersonCam(player);

    else if(camOption == THIRD_PERSON_CAM_OPTION)
        setThirdPersonCam(player);

    gluLookAt(posX, posY + 0.025 * std::abs(sin(playerHeadPosition*PI/180)), posZ,
		posX + sin(yRotation*PI/180), posY + 0.025 * std::abs(sin(playerHeadPosition*PI/180)) + cos(xRotation*PI/180), posZ -cos(yRotation*PI/180),
		0.0, 1.0, 0.0);
}

void Cam::setUpperCam()
{
    camOption = UPPER_CAM_OPTION;

    posX = 2.0f;
    posY = 2.0f;
    posZ = 2.0f;

    xRotation = 1.0f;
    yRotation = 0.0f;
    playerHeadPosition = 0.0f;
}

void Cam::setFirstPersonCam(Diglett player)
{
    camOption = FIRST_PERSON_CAM_OPTION;

    posX = player.getPosition().x;
    posY = player.getPosition().y;
    posZ = player.getPosition().z;

    // AQUI TEM QUE SETAR AS VARIAVEIS ROT PARA DAR EFEITO DE SOBE E DESCE
    xRotation = 1.0f;
    yRotation = 0.0f;
    playerHeadPosition = player.getHeadPosition();
}

void Cam::setThirdPersonCam(Diglett player)
{
    camOption = THIRD_PERSON_CAM_OPTION;

    posX = player.getPosition().x;
    posY = player.getPosition().y;
    posZ = player.getPosition().z - 2.0f;

    // AQUI TEM QUE SETAR AS VARIAVEIS ROT PARA DAR EFEITO DE SOBE E DESCE
    xRotation = 1.0f;
    yRotation = 0.0f;
    playerHeadPosition = 0.0f;
}
