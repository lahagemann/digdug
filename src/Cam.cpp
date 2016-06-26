#include "Cam.h"

Cam::Cam()
{
    camOption = INITIAL_CAM;
    begginingCamXPosition = 8.0f;
    begginingCamYPosition = 5.0f;
    begginingCamZPosition = sqrt(begginingCamXPosition);
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

bool Cam::isInitialCam()
{
    if(camOption == INITIAL_CAM)
        return true;
    else
        return false;
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

void Cam::setInitialCam(Diglett player)
{
    if(begginingCamXPosition > 1.0f)
        begginingCamXPosition -= 0.5f;

    if(begginingCamYPosition > 1.5f)
        begginingCamYPosition -= 0.25f;

    if(begginingCamZPosition < -3.0f)
        begginingCamZPosition += sqrt(begginingCamXPosition);
    else
        begginingCamZPosition = -3.0f;

    float posX, posY, posZ;
    player.getPosition().convert_to_xz(&posX, &posZ);
    posY = 0.7f;

    gluLookAt((posX - sin(player.getXRotation()*PI/180)) + begginingCamXPosition,
              posY + begginingCamYPosition,
              (posZ + cos(player.getYRotation()*PI/180)) + begginingCamZPosition,
        posX, posY, posZ,
		0.0, 1.0, 0.0);

    if(begginingCamXPosition == 1.0f && begginingCamYPosition == 1.5f && begginingCamZPosition == -3.0f)
        camOption = THIRD_PERSON_CAM_OPTION;
}

void Cam::setMiniMapCam()
{
    gluLookAt(0.0, 33.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0);
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

    else if(camOption == INITIAL_CAM)
        setInitialCam(player);
}
