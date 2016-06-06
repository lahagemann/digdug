#include "GameMap.h"

GameMap::GameMap()
{
    load_models();
    load_stage();
}

GameMap::~GameMap()
{
    //dtor
}

void GameMap::load_models()
{
    std::cout << "Loading models..." << std::endl;

    BITMAPINFO	*info;           /* Bitmap information */
    GLubyte     *ptr, *bits;            /* Pointer into bit buffer */

    bits = LoadDIBitmap("bitmap.bmp", &info);
    if(bits == (GLubyte *)0)
    {
		std::cout << "Error loading!" << std::endl << std::endl;
		return;
	}

    for(int i = 0; i < info->bmiHeader.biHeight; i++)
    {
        std::vector<A_RGB> newLine;
        characters_map.push_back(newLine);
        for(int j = 0; j < info->bmiHeader.biWidth; j++, ptr += 3){
            int r = ptr[2];
            int g = ptr[1];
            int b = ptr[0];

            A_RGB rgb = A_RGB(r,g,b);
            characters_map.at(i).push_back(rgb);

            if(rgb.isBlack()) {              //hole

            } else if(rgb.isRed()) {       //crack

            } else if(rgb.isGreen()) {       //ground

            } else if(rgb.isBlue()) {

            } else if(rgb.isYellow()) {    //enemy
                Scyther enemy = Scyther(j,GROUND_HEIGHT,31-i);
                enemies.push_back(enemy);
            } else if(rgb.isMagenta()) {   //snorlax
                Snorlax obstacle = Snorlax(j,GROUND_HEIGHT,31-i);
                rocks.push_back(obstacle);
            } else if(rgb.isCyan()) {     //sharpedo
                Sharpedo sharpedo = Sharpedo(j,SEA_HEIGHT,31-i);
            } else if(rgb.isWhite()) {   //player
                this->player = Diglett(j,GROUND_HEIGHT,31-i);
            }
        }
    }

	std::cout << "Models ok." << std::endl << std::endl;
}

void GameMap::load_stage()
{
    std::cout << "Loading stage..." << std::endl;

    BITMAPINFO	*info;           /* Bitmap information */
    GLubyte     *ptr, *bits;            /* Pointer into bit buffer */

    bits = LoadDIBitmap("bitmap.bmp", &info);
    if (bits == (GLubyte *)0) {
		std::cout << "Error loading!" << std::endl << std::endl;
		return;
	}

    ptr = bits;

    for(int i = 0; i < info->bmiHeader.biHeight; i++){
        std::vector<A_RGB> newLine;
        stage_map.push_back(newLine);
        for(int j = 0; j < info->bmiHeader.biWidth; j++, ptr += 3){
            int r = ptr[2];
            int g = ptr[1];
            int b = ptr[0];

            A_RGB rgb = A_RGB(r,g,b);
            stage_map.at(i).push_back(rgb);

            if(rgb.isBlack()) {              //hole

            } else if(rgb.isRed()) {       //crack

            } else if(rgb.isGreen()) {       //ground

            } else if(rgb.isBlue()) {       //sea

            } else if(rgb.isYellow()) {    //enemy

            } else if(rgb.isMagenta()) {   //snorlax

            } else if(rgb.isCyan()) {     //sharpedo

            } else if(rgb.isWhite()) {   //player

            }
        }
    }

    original_map = stage_map;
    std::cout << "Stage ok." << std::endl << std::endl;
}
