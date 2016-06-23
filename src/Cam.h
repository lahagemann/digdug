#ifndef CAM_H
#define CAM_H

#include <cmath>
#include "Diglett.h"

class Cam
{
    public:
        Cam();
        Cam(Diglett player);
        virtual ~Cam();

        void changeCam(Diglett player);
        void setFirstPersonCam(Diglett player);
        void setThirdPersonCam(Diglett player);
        void setUpperCam();
        void updateCam(Diglett player);

    private:
        const int UPPER_CAM_OPTION = 1;
        const int FIRST_PERSON_CAM_OPTION = 2;
        const int THIRD_PERSON_CAM_OPTION = 3;
        const float PI = 3.14159265;

        float posX, posY, posZ;
        float xRotation, yRotation, playerHeadPosition;
        int camOption;
};

#endif // CAM_H
