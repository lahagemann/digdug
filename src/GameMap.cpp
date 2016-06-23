#include "GameMap.h"

GameMap::GameMap()
{
    load_models();
}

GameMap::~GameMap()
{
    //dtor
}

bool GameMap::checkEnemyCollision(int i, int j)
{
    A_RGB rgb = characters_map.at(i).at(j);

    if(rgb.isYellow())
        return true;
    else
        return false;
}

bool GameMap::checkObstacleCollision(Character::Direction direction)
{
    int i = player.getPosition().i;
    int j = player.getPosition().j;

    if(direction == Character::forwards)
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
    else if(direction == Character::backwards)
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

bool GameMap::isEnemyPushable(int i, int j, float playerRotation)
{
    A_RGB movementPosition;

    if(playerRotation == 0.0f) // Virado para a direita do mapa
        movementPosition = characters_map.at(i).at(j+1);
    else if(playerRotation == 90.0f) // Virado para a parte superior do mapa
        movementPosition = characters_map.at(i-1).at(j);
    else if(playerRotation == 180.0f) // Virado para a esquerda do mapa
        movementPosition = characters_map.at(i).at(j-1);
    else if(playerRotation == 270.0f) // Virado para a parte inferior do mapa
        movementPosition = characters_map.at(i+1).at(j);

    if(movementPosition.isBlue())
        return true;
    else
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
    if(checkEnemyCollision(player.getPosition().i, player.getPosition().j))
        return true;
    else if(isPlayerAboveWater())
        return true;

    return false;
}

void GameMap::load_models()
{
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
                rgb.setBlue();
                characters_map.at(i).push_back(rgb);
            }
            else if(rgb.isRed()) //crack
            {
                stage_map.at(i).push_back(rgb);
                rgb.setBlue();
                characters_map.at(i).push_back(rgb);
            }
            else if(rgb.isGreen()) //ground
            {
                stage_map.at(i).push_back(rgb);
                rgb.setBlue();
                characters_map.at(i).push_back(rgb);
            }
            else if(rgb.isBlue()) //sea
            {
                stage_map.at(i).push_back(rgb);
                rgb.setBlue();
                characters_map.at(i).push_back(rgb);
            }
            else if(rgb.isYellow()) //enemy
            {
                Scyther enemy = Scyther(i,31-j);
                scythers.push_back(enemy);

                characters_map.at(i).push_back(rgb);
                rgb.setGreen();
                stage_map.at(i).push_back(rgb);

            }
            else if(rgb.isMagenta()) //snorlax
            {
                Snorlax obstacle = Snorlax(i,31-j);
                snorlaxs.push_back(obstacle);

                characters_map.at(i).push_back(rgb);
                rgb.setGreen();
                stage_map.at(i).push_back(rgb);
            }
            else if(rgb.isCyan()) //sharpedo
            {
                Sharpedo sharpedo = Sharpedo(i,31-j);
                sharpedos.push_back(sharpedo);

                characters_map.at(i).push_back(rgb);
                rgb.setBlue();
                stage_map.at(i).push_back(rgb);
            }
            else if(rgb.isWhite()) //player
            {
                this->player = Diglett(i,31-j);

                A_RGB green = A_RGB(0,255,0);
                rgb.setBlue();
                characters_map.at(i).push_back(rgb);
                stage_map.at(i).push_back(green);
            }
        }
    }
}

void GameMap::makeCrack()
{
    if(isPlayerAboveHole())
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
    }
}

void GameMap::moveAScyther(int i, int j, int enemiesIndex)
{

}

void GameMap::moveASharpedo(int i, int j, int enemiesIndex)
{

}

void GameMap::moveEnemies()
{
    for(int i=0; i<characters_map.size(); i++)
        for(int j=0; j<characters_map.at(i).size(); j++)
        {
            A_RGB currentCharacter = characters_map.at(i).at(j);

            if(currentCharacter.isYellow()) // A wild Scyther appears
            {
                for(int k=0; k<scythers.size(); k++)
                    if(scythers.at(k).getPosition().equals(i,j))
                        moveAScyther(i,j,k);
            }
            else if(currentCharacter.isCyan()) // A wild Sharpedo appears
            {
                for(int k=0; k<sharpedos.size(); k++)
                    if(sharpedos.at(k).getPosition().equals(i,j))
                        moveASharpedo(i,j,k);
            }
        }
}

void GameMap::push()
{
    int i = player.getPosition().i;
    int j = player.getPosition().j;

    if(player.getXRotation() == 0.0f)
    {
        A_RGB rgb_near = characters_map.at(i).at(j+1);
        A_RGB rgb_far = characters_map.at(i).at(j+2);
        if(rgb_near.isYellow())
        {
            if(isEnemyPushable(i,j+1,0.0f))
            {
                rgb_near.setBlue();
                characters_map.at(i).at(j+1) = rgb_near;

                rgb_near.setYellow();
                characters_map.at(i).at(j+3) = rgb_near;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i, j+1))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i, j+3);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
        else if(rgb_far.isYellow() && rgb_near.isBlue())
        {
            if(isEnemyPushable(i,j+2,0.0f))
            {
                rgb_far.setBlue();
                characters_map.at(i).at(j+2) = rgb_far;

                rgb_far.setYellow();
                characters_map.at(i).at(j+4) = rgb_far;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i, j+2))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i, j+4);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
    }
    else if(player.getXRotation() == 90.0f)
    {
        A_RGB rgb_near = characters_map.at(i-1).at(j);
        A_RGB rgb_far = characters_map.at(i-2).at(j);
        if(rgb_near.isYellow())
        {
            if(isEnemyPushable(i-1,j,90.0f))
            {
                rgb_near.setBlue();
                characters_map.at(i-1).at(j) = rgb_near;

                rgb_near.setYellow();
                characters_map.at(i-3).at(j) = rgb_near;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i-1, j))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i-3, j);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
        else if(rgb_far.isYellow() && rgb_near.isBlue())
        {
            if(isEnemyPushable(i-2,j,90.0f))
            {
                rgb_far.setBlue();
                characters_map.at(i-2).at(j) = rgb_far;

                rgb_far.setYellow();
                characters_map.at(i-4).at(j) = rgb_far;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i-2, j))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i-4, j);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
    }
    else if(player.getXRotation() == 180.0f)
    {
        A_RGB rgb_near = characters_map.at(i).at(j-1);
        A_RGB rgb_far = characters_map.at(i).at(j-2);
        if(rgb_near.isYellow())
        {
            if(isEnemyPushable(i,j-1,180.0f))
            {
                rgb_near.setBlue();
                characters_map.at(i).at(j-1) = rgb_near;

                rgb_near.setYellow();
                characters_map.at(i).at(j-3) = rgb_near;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i, j-1))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i, j-3);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
        else if(rgb_far.isYellow() && rgb_near.isBlue())
        {
            if(isEnemyPushable(i,j-2,180.0f))
            {
                rgb_far.setBlue();
                characters_map.at(i).at(j-2) = rgb_far;

                rgb_far.setYellow();
                characters_map.at(i).at(j-4) = rgb_far;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i, j-2))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i, j-4);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
    }
    else if(player.getXRotation() == 270.0f)
    {
        A_RGB rgb_near = characters_map.at(i+1).at(j);
        A_RGB rgb_far = characters_map.at(i+2).at(j);
        if(rgb_near.isYellow())
        {
            if(isEnemyPushable(i+1,j,270.0f))
            {
                rgb_near.setBlue();
                characters_map.at(i+1).at(j) = rgb_near;

                rgb_near.setYellow();
                characters_map.at(i+3).at(j) = rgb_near;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i+1, j))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i+3, j);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
        else if(rgb_far.isYellow() && rgb_near.isBlue())
        {
            if(isEnemyPushable(i+2,j,270.0f))
            {
                rgb_far.setBlue();
                characters_map.at(i+2).at(j) = rgb_far;

                rgb_far.setYellow();
                characters_map.at(i+4).at(j) = rgb_far;

                for(int k = 0; k < scythers.size(); k++)
                {
                    if(scythers.at(k).getPosition().equals(i+2, j))
                    {
                        Scyther enemy = scythers.at(k);
                        enemy.setPosition(i+4, j);
                        scythers.at(k) = enemy;
                    }
                }
            }
        }
    }
}
