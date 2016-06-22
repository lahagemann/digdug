#include "GameMap.h"

GameMap::GameMap()
{
    load_models();
}

GameMap::~GameMap()
{
    //dtor
}

bool GameMap::checkEnemyCollision()
{
    A_RGB rgb = characters_map.at(player.getPosition().i).at(player.getPosition().j);

    if(rgb.isYellow())
        return true;
    else
        return false;
}

bool GameMap::checkObstacleCollision(Diglett::Direction direction)
{
    int i = player.getPosition().i;
    int j = player.getPosition().j;

    if(direction == Diglett::Direction::forwards)
    {
        if(player.getXRotation() == 0.0f)
        {
            A_RGB rgb = characters_map.at(i).at(j+1);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
        else if(player.getXRotation() == 90.0f)
        {
            A_RGB rgb = characters_map.at(i-1).at(j);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
        else if(player.getXRotation() == 180.0f)
        {
            A_RGB rgb = characters_map.at(i).at(j-1);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
        else if(player.getXRotation() == 270.0f)
        {
            A_RGB rgb = characters_map.at(i+1).at(j);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
    }
    else if(direction == Diglett::Direction::backwards)
    {
        if(player.getXRotation() == 0.0f)
        {
            A_RGB rgb = characters_map.at(i).at(j-1);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
        else if(player.getXRotation() == 90.0f)
        {
            A_RGB rgb = characters_map.at(i+1).at(j);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
        else if(player.getXRotation() == 180.0f)
        {
            A_RGB rgb = characters_map.at(i).at(j+1);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
        else if(player.getXRotation() == 270.0f)
        {
            A_RGB rgb = characters_map.at(i-1).at(j);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
    }

    return false;
}

bool GameMap::isPlayerAboveHole()
{
    A_RGB currentPositionColor = stage_map.at(player.getPosition().i).at(player.getPosition().j);

    if(currentPositionColor.isBlack())
        return true;
    else
        return false;
}

bool GameMap::isPlayerAboveWater()
{
    A_RGB rgb = stage_map.at(player.getPosition().i).at(player.getPosition().j);

    if(rgb.isBlue())
        return true;
    else
        return false;
}

bool GameMap::isPlayerDead()
{
    if(checkEnemyCollision())
        return true;
    else if(isPlayerAboveWater())
        return true;

    return false;
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
        std::vector<A_RGB> charRGBLine;
        characters_map.push_back(charRGBLine);

        std::vector<A_RGB> stageRGBLine;
        stage_map.push_back(stageRGBLine);

        std::vector<Character> charLine;
        characters.push_back(charLine);

        std::vector<Ground> groundLine;
        ground.push_back(groundLine);

        for(int j = 0; j < info->bmiHeader.biWidth; j++, ptr += 3)
        {
            int r = ptr[2];
            int g = ptr[1];
            int b = ptr[0];

            A_RGB rgb = A_RGB(r,g,b);
            characters_map.at(i).push_back(rgb);

            if(rgb.isBlack()) //hole
            {
                Hole hole = Hole(j,GROUND_HEIGHT,31-i);
                ground.at(i).push_back(hole);
                stage_map.at(i).push_back(rgb);

            }
            else if(rgb.isRed()) //crack
            {
                Crack crack = Crack(j,GROUND_HEIGHT, 31-i);
                ground.at(i).push_back(crack);
                stage_map.at(i).push_back(rgb);

            }
            else if(rgb.isGreen()) //ground
            {
                Floor floor = Floor(j,GROUND_HEIGHT, 31-i);
                ground.at(i).push_back(floor);
                stage_map.at(i).push_back(rgb);
            }
            else if(rgb.isBlue()) //sea
            {
                //Sea sea = Sea(j,SEA_HEIGHT, 31-i);
                //ground.at(i).push_back(sea);
                stage_map.at(i).push_back(rgb);

            }
            else if(rgb.isYellow()) //enemy
            {
                Scyther enemy = Scyther(j,GROUND_HEIGHT,31-i);
                Floor floor = Floor(j, GROUND_HEIGHT, 31-i);

                characters.at(i).push_back(enemy);
                ground.at(i).push_back(floor);

                A_RGB green = A_RGB(0,255,0);
                stage_map.at(i).push_back(green);
                characters_map.push_back(rgb);

            }
            else if(rgb.isMagenta()) //snorlax
            {
                Snorlax obstacle = Snorlax(j,GROUND_HEIGHT,31-i);
                Floor floor = Floor(j, GROUND_HEIGHT, 31-i);

                characters.at(i).push_back(obstacle);
                ground.at(i).push_back(floor);

                A_RGB green = A_RGB(0,255,0);
                stage_map.at(i).push_back(green);
                characters_map.push_back(rgb);
            }
            else if(rgb.isCyan()) //sharpedo
            {
                Sharpedo sharpedo = Sharpedo(j,SEA_HEIGHT,31-i);
                //Sea sea = Sea(j,SEA_HEIGHT, 31-i);

                characters.at(i).push_back(sharpedo);
                //ground.at(i).push_back(sea);

                A_RGB blue = A_RGB(0,0,255);
                characters_map.at(i).push_back(rgb);
                stage_map.at(i).push_back(blue);
            }
            else if(rgb.isWhite()) //player
            {
                this->player = Diglett(j,GROUND_HEIGHT,31-i);

                A_RGB green = A_RGB(0,255,0);
                ground.at(i).push_back(green);
            }
        }
    }
	std::cout << "Models ok." << std::endl << std::endl;
}

void GameMap::makeCrack()
{
    if(isAboveHole())
    {
        if(player.getXRotation() == 0.0f) // Virado para a direita do mapa
        {
            int iterationPosition = player.getPosition().j + 1;
            A_RGB currentPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);

            while(currentPositionColor.isGreen())
            {
                iterationPosition++;
                currentPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);
            }

            if(currentPositionColor.isBlack() || currentPositionColor.isRed())
            {
                currentPositionColor.setRed();
                for(int k = player.getPosition().j + 1; k < iterationPosition; k++)
                    stage_map.at(player.getPosition().i).at(k) = currentPositionColor;
            }
        }
        else if(player.getXRotation() == 90.0f) // Virado para a parte superior do mapa
        {
            int iterationPosition = player.getPosition().i + 1;
            A_RGB currentPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);

            while(currentPositionColor.isGreen())
            {
                iterationPosition++;
                currentPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);
            }

            if(currentPositionColor.isBlack() || currentPositionColor.isRed())
            {
                currentPositionColor.setRed();
                for(int k = player.getPosition().i + 1; k < iterationPosition; k++)
                    stage_map.at(k).at(player.getPosition().j) = currentPositionColor;
            }
        }
        else if(player.getXRotation() == 180.0f) // Virado para a esquerda do mapa
        {
            int iterationPosition = player.getPosition().j - 1;
            A_RGB currentPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);

            while(currentPositionColor.isGreen())
            {
                iterationPosition--;
                currentPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);
            }

            if(currentPositionColor.isBlack() || currentPositionColor.isRed())
            {
                currentPositionColor.setRed();
                for(int k = player.getPosition().j - 1; k > iterationPosition; k--)
                    stage_map.at(player.getPosition().i).at(k) = currentPositionColor;
            }
        }
        else if(player.getXRotation() == 270.0f) // Virado para a parte inferior do mapa
        {
            int iterationPosition = player.getPosition().i - 1;
            A_RGB currentPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);

            while(currentPositionColor.isGreen())
            {
                iterationPosition--;
                currentPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);
            }

            if(currentPositionColor.isBlack() || currentPositionColor.isRed())
            {
                currentPositionColor.setRed();
                for(int k = player.getPosition().i - 1; k > iterationPosition; k--)
                    stage_map.at(k).at(player.getPosition().j) = currentPositionColor;
            }
        }
    }
}
