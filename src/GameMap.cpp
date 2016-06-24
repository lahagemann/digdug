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
    if(i < characters_map.size() && j < characters_map.at(i).size())
    {
        A_RGB rgb = characters_map.at(i).at(j);

        if(rgb.isYellow())
            return true;
    }
    return false;
}

bool GameMap::checkObstacleCollision(Character::Direction direction)
{
    int i = player.getPosition().i;
    int j = player.getPosition().j;

    if(i < characters_map.size()-1 && j < characters_map.at(i).size()-1 && i > 0 && j > 0)
    {
        if(direction == Character::forwards)
        {
            if(player.getYRotation() == 0.0f)
            {
                A_RGB rgb = characters_map.at(i-1).at(j);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
            else if(player.getYRotation() == 90.0f)
            {
                A_RGB rgb = characters_map.at(i).at(j+1);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
            else if(player.getYRotation() == 180.0f)
            {
                A_RGB rgb = characters_map.at(i+1).at(j);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
            else if(player.getYRotation() == 270.0f)
            {
                A_RGB rgb = characters_map.at(i).at(j-1);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
        }
        else if(direction == Character::backwards)
        {
            if(player.getYRotation() == 0.0f)
            {
                A_RGB rgb = characters_map.at(i+1).at(j);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
            else if(player.getYRotation() == 90.0f)
            {
                A_RGB rgb = characters_map.at(i).at(j-1);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
            else if(player.getYRotation() == 180.0f)
            {
                A_RGB rgb = characters_map.at(i-1).at(j);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
            else if(player.getYRotation() == 270.0f)
            {
                A_RGB rgb = characters_map.at(i).at(j+1);
                if(rgb.isMagenta())
                    return true;
                else
                    return false;
            }
        }
    }

    return false;
}

std::vector< std::vector<A_RGB> > GameMap::getCharactersMap()
{
    return characters_map;
}

std::vector<Scyther> GameMap::getScythers()
{
    return scythers;
}

std::vector<Sharpedo> GameMap::getSharpedos()
{
    return sharpedos;
}

std::vector<Snorlax> GameMap::getSnorlaxs()
{
    return snorlaxs;
}

std::vector< std::vector<A_RGB> > GameMap::getStageMap()
{
    return stage_map;
}

bool GameMap::isEnemyPushable(int i, int j, float playerRotation)
{
    if(i < characters_map.size()-1 && j < characters_map.at(i).size()-1 && i > 0 && j > 0)
    {
        A_RGB movementPosition;

        if(playerRotation == 0.0f) // Virado para a direita do mapa
            movementPosition = characters_map.at(i-1).at(j);
        else if(playerRotation == 90.0f) // Virado para a parte superior do mapa
            movementPosition = characters_map.at(i).at(j+1);
        else if(playerRotation == 180.0f) // Virado para a esquerda do mapa
            movementPosition = characters_map.at(i+1).at(j);
        else if(playerRotation == 270.0f) // Virado para a parte inferior do mapa
            movementPosition = characters_map.at(i).at(j-1);

        if(movementPosition.isBlue())
            return true;
    }

    return false;
}

bool GameMap::isPlayerAboveHole()
{
    if(player.getPosition().i < stage_map.size() &&
       player.getPosition().j < stage_map.at(player.getPosition().i).size())
    {
        A_RGB rgb = stage_map.at(player.getPosition().i).at(player.getPosition().j);

        if(rgb.isBlack())
            return true;
    }

    return false;
}

bool GameMap::isPlayerAboveWater()
{
    if(player.getPosition().i < stage_map.size() &&
       player.getPosition().j < stage_map.at(player.getPosition().i).size())
    {
        A_RGB rgb = stage_map.at(player.getPosition().i).at(player.getPosition().j);

        if(rgb.isBlue())
            return true;
    }

    return false;
}

bool GameMap::isPlayerDead()
{
    if(checkEnemyCollision(player.getPosition().i, player.getPosition().j) || isPlayerAboveWater())
        return true;

    return false;
}

bool GameMap::isPlayerNearEnemy(int enemiesIndex, int directionOptions[4], int *direction)
{
    Scyther scyther = scythers.at(enemiesIndex);

    // case north
    if(directionOptions[0] != 0)
    {
        for(int i = 1; i < 5; i++)
        {
            A_RGB rgb = stage_map.at(scyther.getPosition().i - i).at(scyther.getPosition().j);
            if(rgb.isWhite())
            {
                *direction = 1;
                return true;
            }
        }
    }

    if(directionOptions[1] != 0) // case east
    {
        for(int j = 1; j < 5; j++)
        {
            A_RGB rgb = stage_map.at(scyther.getPosition().i).at(scyther.getPosition().j - j);
            if(rgb.isWhite())
            {
                *direction = 2;
                return true;
            }
        }
    }

    // case south
    if(directionOptions[2] != 0)
    {
        for(int i = 1; i < 5; i++)
        {
            A_RGB rgb = stage_map.at(scyther.getPosition().i + i).at(scyther.getPosition().j);
            if(rgb.isWhite())
            {
                *direction = 3;
                return true;
            }
        }
    }

    // case west
    if(directionOptions[1] != 0)
    {
        for(int j = 1; j < 5; j++)
        {
            A_RGB rgb = stage_map.at(scyther.getPosition().i).at(scyther.getPosition().j + j);
            if(rgb.isWhite())
            {
                *direction = 4;
                return true;
            }
        }
    }

    *direction = 5;
    return false;
}

void GameMap::load_models()
{
    BITMAPINFO	*info;           /* Bitmap information */
    GLubyte	    *bits;           /* Bitmap RGB pixels */
    GLubyte     *ptr;            /* Pointer into bit buffer */
    GLubyte	    *rgba;           /* RGBA pixel buffer */

    bits = LoadDIBitmap("Stage2.bmp", &info);
    if(bits == (GLubyte *)0)
    {
		std::cout << "Error loading!" << std::endl << std::endl;
		return;
	}

    for(int j = 0; j < 32; j++)
	{
	    std::vector<A_RGB> charRGBLine;
        characters_map.push_back(charRGBLine);

        std::vector<A_RGB> stageRGBLine;
        stage_map.push_back(stageRGBLine);
	}

	rgba = (GLubyte *)malloc(info->bmiHeader.biWidth * info->bmiHeader.biHeight * 4);

    int i = info->bmiHeader.biWidth * info->bmiHeader.biHeight-1;
    for(ptr = bits;  i >= 0; i--, ptr += 3)
    {
        int r = ptr[2];
        int g = ptr[1];
        int b = ptr[0];

        //std::cout << i << " " << r << " " << g << " " << b << std::endl;

        A_RGB rgb = A_RGB(r,g,b);
        if(rgb.isBlack()) //hole
        {
            stage_map.at(31-i/32).push_back(rgb);
            rgb.setBlue();
            characters_map.at(31-i/32).push_back(rgb);
        }
        else if(rgb.isRed()) //crack
        {
            stage_map.at(31-i/32).push_back(rgb);
            rgb.setBlue();
            characters_map.at(31-i/32).push_back(rgb);
        }
        else if(rgb.isGreen()) //ground
        {
            stage_map.at(31-i/32).push_back(rgb);
            rgb.setBlue();
            characters_map.at(31-i/32).push_back(rgb);
        }
        else if(rgb.isBlue()) //sea
        {
            stage_map.at(31-i/32).push_back(rgb);
            rgb.setBlue();
            characters_map.at(31-i/32).push_back(rgb);
        }
        else if(rgb.isYellow()) //enemy
        {
            Scyther enemy = Scyther(31-i/32,31 - i%32);
            scythers.push_back(enemy);

            characters_map.at(31-i/32).push_back(rgb);
            rgb.setGreen();
            stage_map.at(31-i/32).push_back(rgb);
        }
        else if(rgb.isMagenta()) //snorlax
        {
            Snorlax obstacle = Snorlax(31-i/32,31 - i%32);
            snorlaxs.push_back(obstacle);

            characters_map.at(31-i/32).push_back(rgb);
            rgb.setGreen();
            stage_map.at(31-i/32).push_back(rgb);
        }
        else if(rgb.isCyan()) //sharpedo
        {
            Sharpedo sharpedo = Sharpedo(31-i/32,31 - i%32);
            sharpedos.push_back(sharpedo);

            characters_map.at(31-i/32).push_back(rgb);
            rgb.setBlue();
            stage_map.at(31-i/32).push_back(rgb);
        }
        else if(rgb.isWhite()) //player
        {
            this->player = Diglett(31-i/32,31 - i%32);

            A_RGB green = A_RGB(0,255,0);
            rgb.setBlue();
            characters_map.at(31-i/32).push_back(rgb);
            stage_map.at(31-i/32).push_back(green);
        }
    }
}

void GameMap::makeCrack()
{
    if(isPlayerAboveHole())
    {
        if(player.getYRotation() == 0.0f) // Virado para a parte superior do mapa
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
        else if(player.getYRotation() == 90.0f) // Virado para a esquerda do mapa
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
        else if(player.getYRotation() == 180.0f) // Virado para a parte inferior do mapa
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
        else if(player.getYRotation() == 270.0f) // Virado para a direita do mapa
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
    }
}

void GameMap::moveAScyther(int i, int j, int enemiesIndex)
{
    int direction;
    int directionOptions[4] = {1,2,3,4};
    bool moved = false;
    Scyther scyther = scythers.at(enemiesIndex);

    while(!moved)
    {
        if(isPlayerNearEnemy(enemiesIndex, directionOptions, &direction))
        {
            if(directionOptions[0] == 0 && directionOptions[1] == 0
               && directionOptions[1] == 0 && directionOptions[1] == 0)
                direction = 5;
        }
        else
        {
            srand (time(NULL));
            direction = rand() % 5 + 1;
            moved = false;
        }

        A_RGB rgb;

        switch(direction)
        {
            case 1: //north
                rgb = stage_map.at(i-1).at(j);
                if(rgb.isGreen())
                {
                    CharacterPosition pos = CharacterPosition(i-1,j);
                    scyther.setPosition(pos);
                    scyther.setYRotation(90.0f);
                    scythers.at(enemiesIndex) = scyther;
                    directionOptions[0] = 0;
                    moved = true;
                }
                break;
            case 2: //east
                rgb = stage_map.at(i).at(j+1);
                if(rgb.isGreen())
                {
                    CharacterPosition pos = CharacterPosition(i,j+1);
                    scyther.setPosition(pos);
                    scyther.setYRotation(0.0f);
                    scythers.at(enemiesIndex) = scyther;
                    directionOptions[1] = 0;
                    moved = true;
                }
                break;
            case 3: //south
                rgb = stage_map.at(i+1).at(j);
                if(rgb.isGreen())
                {
                    CharacterPosition pos = CharacterPosition(i+1,j);
                    scyther.setPosition(pos);
                    scyther.setYRotation(270.0f);
                    scythers.at(enemiesIndex) = scyther;
                    directionOptions[3] = 0;
                    moved = true;
                }
                break;
            case 4: //west
                rgb = stage_map.at(i).at(j-1);
                if(rgb.isGreen())
                {
                    CharacterPosition pos = CharacterPosition(i+1,j);
                    scyther.setPosition(pos);
                    scyther.setYRotation(180.0f);
                    scythers.at(enemiesIndex) = scyther;
                    directionOptions[4] = 0;
                    moved = true;
                }
                break;
            case 5: //don't move
                moved = true;
                break;
            default:
                break;
        }
    }


    // detectar se o player está a 4 células de distância deste scyther.

    //scythers.at(enemiesIndex);

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

    if(player.getYRotation() == 0.0f)
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
    else if(player.getYRotation() == 90.0f)
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
    else if(player.getYRotation() == 180.0f)
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
    else if(player.getYRotation() == 270.0f)
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
}
