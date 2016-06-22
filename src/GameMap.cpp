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

        for(int j = 0; j < info->bmiHeader.biWidth; j++, ptr += 3)
        {
            int r = ptr[2];
            int g = ptr[1];
            int b = ptr[0];

            A_RGB rgb = A_RGB(r,g,b);
            //characters_map.at(i).push_back(rgb);

            if(rgb.isBlack()) //hole
            {
                stage_map.at(i).push_back(rgb);
                characters_map.at(i).push_back(rgb.setBlue());
            }
            else if(rgb.isRed()) //crack
            {
                stage_map.at(i).push_back(rgb);
                characters_map.at(i).push_back(rgb.setBlue());
            }
            else if(rgb.isGreen()) //ground
            {
                stage_map.at(i).push_back(rgb);
                characters_map.at(i).push_back(rgb.setBlue());
            }
            else if(rgb.isBlue()) //sea
            {
                stage_map.at(i).push_back(rgb);
                characters_map.at(i).push_back(rgb.setBlue());
            }
            else if(rgb.isYellow()) //enemy
            {
                Scyther enemy = Scyther(i,31-j);
                characters.push_back(enemy);

                characters_map.push_back(rgb);
                stage_map.at(i).push_back(rgb.setGreen());

            }
            else if(rgb.isMagenta()) //snorlax
            {
                Snorlax obstacle = Snorlax(i,31-j);
                characters.push_back(obstacle);

                characters_map.push_back(rgb);
                stage_map.at(i).push_back(rgb.setGreen());
            }
            else if(rgb.isCyan()) //sharpedo
            {
                Sharpedo sharpedo = Sharpedo(i,31-j);
                characters.push_back(sharpedo);

                characters_map.at(i).push_back(rgb);
                stage_map.at(i).push_back(rgb.setBlue());
            }
            else if(rgb.isWhite()) //player
            {
                this->player = Diglett(i,31-j);

                A_RGB green = A_RGB(0,255,0);
                characters_map.at(i).push_back(rgb.setBlue());
                stage_map.at(i).push_back(green);
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

void GameMap::moveEnemies()
{

}
