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
    player.getPosition().convert_to_xz(&posX, &posZ);
    posY = 0.7f;

    float xRotation = player.getXRotation();
    float yRotation = player.getYRotation();

    if(yRotation == 0.0f) // Virado para a parte superior do mapa
        posZ += 0.2f;
    else if(yRotation == 90.0f) // Virado para a esquerda do mapa
    {
        yRotation = 270.0f; // Transforma coordenadas mao direita em mao esquerda
        posX += 0.2f;
    }
    else if(yRotation == 180.0f) // Virado para a parte inferior do mapa
        posZ -= 0.2f;
    else if(yRotation == 270.0f) // Virado para a direita do mapa
    {
        yRotation = 90.0f; // Transforma coordenadas mao direita em mao esquerda
        posX -= 0.2f;
    }

    gluLookAt(posX, posY, posZ,
		posX + sin((yRotation+180)*PI/180), posY + cos(xRotation*PI/180), posZ - cos((yRotation+180)*PI/180),
		0.0, 1.0, 0.0);
}

void Cam::setThirdPersonCam(Diglett player)
{
    camOption = THIRD_PERSON_CAM_OPTION;

    float posX, posY, posZ;
    player.getPosition().convert_to_xz(&posX, &posZ);
    posY = 1.5f;

    float xRotation = player.getXRotation();
    float yRotation = player.getYRotation();

    if(yRotation == 0.0f) // Virado para a parte superior do mapa
        posZ -= 3.0f;
    else if(yRotation == 90.0f) // Virado para a esquerda do mapa
    {
        yRotation = 270.0f; // Transforma coordenadas mao direita em mao esquerda
        posX -= 3.0f;
    }
    else if(yRotation == 180.0f) // Virado para a parte inferior do mapa
        posZ += 3.0f;
    else if(yRotation == 270.0f) // Virado para a direita do mapa
    {
        yRotation = 90.0f; // Transforma coordenadas mao direita em mao esquerda
        posX += 3.0f;
    }

    gluLookAt(posX, posY + 0.3, posZ,
		posX + sin((yRotation+180)*PI/180), posY + cos(xRotation*PI/180), posZ - cos((yRotation+180)*PI/180),
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
