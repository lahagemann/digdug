#ifndef CAM_H
#define CAM_H

#include <cmath>
#include "Diglett.h"

class Cam
{
    public:
        Cam();
        virtual ~Cam();

        void changeCam(Diglett player);
        int getCurrentCamOption();
        bool isInitialCam();
        bool isUpperCam();
        void setFirstPersonCam(Diglett player);
        void setInitialCam(Diglett player);
        void setMiniMapCam();
        void setThirdPersonCam(Diglett player);
        void setUpperCam();
        void updateCam(Diglett player);

    private:
        const static int INITIAL_CAM = 0;
        const static int UPPER_CAM_OPTION = 1;
        const static int FIRST_PERSON_CAM_OPTION = 2;
        const static int THIRD_PERSON_CAM_OPTION = 3;
        const static float PI = 3.14159265;

        int camOption;
        float begginingCamXPosition;
        float begginingCamYPosition;
        float begginingCamZPosition;
};

#endif // CAM_H
