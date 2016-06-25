#include "GameMap.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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
        else if(direction == Character::rotateLeft)
        {
            A_RGB rgb = characters_map.at(i).at(j-1);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
        else if(direction == Character::rotateRight)
        {
            A_RGB rgb = characters_map.at(i).at(j+1);
            if(rgb.isMagenta())
                return true;
            else
                return false;
        }
    }

    return false;
}

void GameMap::flood_fill()
{
    // seed = size/2-1 size/2-1 = 15 15
    flood_map = stage_map;
    this->flood_size = 0;

    // primeira seed
    int m = player.getPosition().i;
    int n = player.getPosition().j;
    A_RGB northwest, northeast, southwest, southeast;
    northwest = stage_map.at(m-1).at(n-1);
    northeast = stage_map.at(m-1).at(n+1);
    southwest = stage_map.at(m+1).at(n-1);
    southeast = stage_map.at(m+1).at(n+1);

    if(northwest.isGreen())
        flood_step(m-1, n-1);
    else if(northeast.isGreen())
        flood_step(m-1, n+1);
    else if(southwest.isGreen())
        flood_step(m+1, n-1);
    else if(southeast.isGreen())
        flood_step(m+1, n+1);

    std::cout << flood_size << std::endl;

    //verifica se a área
    if((float)this->flood_size > field_size/2.0f)
    {
        // deleta tudo que ficou verde no flood_map
        for(int i=0; i < flood_map.size(); i++)
        {
            for(int j=0; j < flood_map.at(i).size(); j++)
            {
                A_RGB rgb = flood_map.at(i).at(j);
                if(rgb.isGreen())
                {
                    rgb.setBlue();
                    stage_map.at(i).at(j) = rgb;

                    rgb = characters_map.at(i).at(j);
                    if(rgb.isYellow())
                    {
                        std::vector<Scyther> livingScythers;
                        for(int k=0; k<scythers.size(); k++)
                        {
                            Scyther scyther = scythers.at(k);
                            if(!scyther.getPosition().equals(i,j))
                                livingScythers.push_back(scyther);
                        }
                        scythers = livingScythers;
                    }
                    else if(rgb.isMagenta())
                    {
                        std::vector<Snorlax> livingSnorlaxes;
                        for(int k=0; k<snorlaxs.size(); k++)
                        {
                            Snorlax snorlax = snorlaxs.at(k);
                            if(!snorlax.getPosition().equals(i,j))
                                livingSnorlaxes.push_back(snorlax);
                        }
                        snorlaxs = livingSnorlaxes;
                    }
                    rgb.setBlue();
                    characters_map.at(i).at(j) = rgb;
                }
            }
        }
        field_size = flood_size;
    }
    else
    {
        // deleta tudo que ficou amarelo no flood_map.
        for(int i=0; i < flood_map.size(); i++)
        {
            for(int j=0; j < flood_map.at(i).size(); j++)
            {
                A_RGB rgb = flood_map.at(i).at(j);
                if(rgb.isYellow())
                {
                    rgb.setBlue();
                    stage_map.at(i).at(j) = rgb;

                    rgb = characters_map.at(i).at(j);
                    if(rgb.isYellow())
                    {
                        std::vector<Scyther> livingScythers;
                        for(int k=0; k<scythers.size(); k++)
                        {
                            Scyther scyther = scythers.at(k);
                            if(!scyther.getPosition().equals(i,j))
                                livingScythers.push_back(scyther);
                        }
                        scythers = livingScythers;
                    }
                    else if(rgb.isMagenta())
                    {
                        std::vector<Snorlax> livingSnorlaxes;
                        for(int k=0; k<snorlaxs.size(); k++)
                        {
                            Snorlax snorlax = snorlaxs.at(k);
                            if(!snorlax.getPosition().equals(i,j))
                                livingSnorlaxes.push_back(snorlax);
                        }
                        snorlaxs = livingSnorlaxes;
                    }
                    rgb.setBlue();
                    characters_map.at(i).at(j) = rgb;
                }
            }
        }
        field_size = field_size - flood_size;
    }

}

void GameMap::flood_step(int i, int j)
{
    if(flood_size == field_size)
        return;

    A_RGB north, east, west, south, current;

    // pinta célula atual no flood_map.
    current.setYellow();
    flood_map.at(i).at(j) = current;
    this->flood_size++;


    north = flood_map.at(i-1).at(j);
    east = flood_map.at(i).at(j+1);
    south = flood_map.at(i+1).at(j);
    west = flood_map.at(i).at(j-1);

    if(!north.isGreen() && !east.isGreen() && !south.isGreen() && !west.isGreen())
        return;

    if(north.isGreen())
        flood_step(i-1,j);

    east = flood_map.at(i).at(j+1);
    if(east.isGreen())
        flood_step(i,j+1);

    south = flood_map.at(i+1).at(j);
    if(south.isGreen())
        flood_step(i+1,j);

    west = flood_map.at(i).at(j-1);
    if(west.isGreen())
        flood_step(i,j-1);
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

bool GameMap::isPlayerNearEnemy(int enemiesIndex, int* direction)
{
    Scyther scyther = scythers.at(enemiesIndex);
    int posI = scyther.getPosition().i;
    int posJ = scyther.getPosition().j;

    int playerI = player.getPosition().i;
    int playerJ = player.getPosition().j;

    // case north
    for(int i = 1; i < 5; i++)
    {
        if(playerI == posI - i && playerJ == posJ)
        {
            *direction = 1;
            return true;
        }
    }

    // case east
    for(int j = 1; j < 5; j++)
    {
        if(playerI == posI && playerJ == posJ - j)
        {
            *direction = 2;
            return true;
        }
    }

    // case south
    for(int i = 1; i < 5; i++)
    {
        if(playerI == posI + i && playerJ == posJ)
        {
            *direction = 3;
            return true;
        }
    }

    // case west
    for(int j = 1; j < 5; j++)
    {
        if(playerI == posI && playerJ == posJ + j)
        {
            *direction = 4;
            return true;
        }
    }
    return false;
}

bool GameMap::isScytherDead(int enemiesIndex)
{
    Scyther scyther = scythers.at(enemiesIndex);
    A_RGB rgb = stage_map.at(scyther.getPosition().i).at(scyther.getPosition().j);
    if(rgb.isBlue())
        return true;
    else
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
	field_size = 0;

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
            field_size++;
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
            A_RGB mapPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);
            A_RGB charactersPositionColor = characters_map.at(iterationPosition).at(player.getPosition().j);

            while(mapPositionColor.isGreen() && charactersPositionColor.isBlue())
            {
                iterationPosition--;
                mapPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);
                charactersPositionColor = characters_map.at(iterationPosition).at(player.getPosition().j);
            }

            if(mapPositionColor.isBlack() || mapPositionColor.isRed() || mapPositionColor.isBlue())
            {
                mapPositionColor.setRed();
                for(int k = player.getPosition().i - 1; k > iterationPosition; k--)
                    stage_map.at(k).at(player.getPosition().j) = mapPositionColor;
                flood_fill();
            }
        }
        else if(player.getYRotation() == 90.0f) // Virado para a esquerda do mapa
        {
            int iterationPosition = player.getPosition().j + 1;
            A_RGB mapPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);
            A_RGB charactersPositionColor = characters_map.at(player.getPosition().i).at(iterationPosition);

            while(mapPositionColor.isGreen() && charactersPositionColor.isBlue())
            {
                iterationPosition++;
                mapPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);
                charactersPositionColor = characters_map.at(player.getPosition().i).at(iterationPosition);
            }

            if(mapPositionColor.isBlack() || mapPositionColor.isRed() || mapPositionColor.isBlue())
            {
                mapPositionColor.setRed();
                for(int k = player.getPosition().j + 1; k < iterationPosition; k++)
                    stage_map.at(player.getPosition().i).at(k) = mapPositionColor;
                flood_fill();
            }
        }
        else if(player.getYRotation() == 180.0f) // Virado para a parte inferior do mapa
        {
            int iterationPosition = player.getPosition().i + 1;
            A_RGB mapPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);
            A_RGB charactersPositionColor = characters_map.at(iterationPosition).at(player.getPosition().j);

            while(mapPositionColor.isGreen() && charactersPositionColor.isBlue())
            {
                iterationPosition++;
                mapPositionColor = stage_map.at(iterationPosition).at(player.getPosition().j);
                charactersPositionColor = characters_map.at(iterationPosition).at(player.getPosition().j);
            }

            if(mapPositionColor.isBlack() || mapPositionColor.isRed() || mapPositionColor.isBlue())
            {
                mapPositionColor.setRed();
                for(int k = player.getPosition().i + 1; k < iterationPosition; k++)
                    stage_map.at(k).at(player.getPosition().j) = mapPositionColor;
                flood_fill();
            }
        }
        else if(player.getYRotation() == 270.0f) // Virado para a direita do mapa
        {
            int iterationPosition = player.getPosition().j - 1;
            A_RGB mapPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);
            A_RGB charactersPositionColor = characters_map.at(player.getPosition().i).at(iterationPosition);

            while(mapPositionColor.isGreen() && charactersPositionColor.isBlue())
            {
                iterationPosition--;
                mapPositionColor = stage_map.at(player.getPosition().i).at(iterationPosition);
                charactersPositionColor = characters_map.at(player.getPosition().i).at(iterationPosition);
            }

            if(mapPositionColor.isBlack() || mapPositionColor.isRed() || mapPositionColor.isBlue())
            {
                mapPositionColor.setRed();
                for(int k = player.getPosition().j - 1; k > iterationPosition; k--)
                    stage_map.at(player.getPosition().i).at(k) = mapPositionColor;
                flood_fill();
            }
        }
    }
}

void GameMap::moveAScyther(int i, int j, int enemiesIndex, int direction)
{
    A_RGB rgb, stage_rgb;
    Scyther enemy;
    int dir;

    if(isPlayerNearEnemy(enemiesIndex, &dir))
        direction = dir;

    if(direction == 1) //north
    {
        if(i > 0)
        {
            rgb = characters_map.at(i-1).at(j);
            stage_rgb = stage_map.at(i-1).at(j);
            if(rgb.isBlue() && stage_rgb.isGreen())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setYellow();
                characters_map.at(i-1).at(j) = rgb;

                enemy = scythers.at(enemiesIndex);
                enemy.setPosition(i-1, j);
                enemy.setYRotation(0.0f);
                scythers.at(enemiesIndex) = enemy;
            }
        }
    }
    else if(direction == 2) //east
    {
        if(j > 0)
        {
            rgb = characters_map.at(i).at(j-1);
            stage_rgb = stage_map.at(i).at(j-1);
            if(rgb.isBlue() && stage_rgb.isGreen())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setYellow();
                characters_map.at(i).at(j-1) = rgb;

                enemy = scythers.at(enemiesIndex);
                enemy.setPosition(i, j-1);
                enemy.setYRotation(270.0f);
                scythers.at(enemiesIndex) = enemy;
            }
        }
    }
    else if(direction == 3) //south
    {
        if(i < 31)
        {
            rgb = characters_map.at(i+1).at(j);
            stage_rgb = stage_map.at(i+1).at(j);
            if(rgb.isBlue() && stage_rgb.isGreen())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setYellow();
                characters_map.at(i+1).at(j) = rgb;

                enemy = scythers.at(enemiesIndex);
                enemy.setPosition(i+1, j);
                enemy.setYRotation(180.0f);
                scythers.at(enemiesIndex) = enemy;
            }
        }
    }
    else if(direction == 4)
    {
        if(j < 31)
        {
            rgb = characters_map.at(i).at(j+1);
            stage_rgb = stage_map.at(i).at(j+1);
            if(rgb.isBlue() && stage_rgb.isGreen())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setYellow();
                characters_map.at(i).at(j+1) = rgb;

                enemy = scythers.at(enemiesIndex);
                enemy.setPosition(i, j+1);
                enemy.setYRotation(90.0f);
                scythers.at(enemiesIndex) = enemy;
            }
        }
    }
}

void GameMap::moveASharpedo(int i, int j, int enemiesIndex, int direction)
{
    A_RGB rgb, stage_rgb;
    Sharpedo sharpedo;
    int dir;

    if(direction == 1) //north
    {
        if(i > 0)
        {
            rgb = characters_map.at(i-1).at(j);
            stage_rgb = stage_map.at(i-1).at(j);
            if(rgb.isBlue() && stage_rgb.isBlue())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setCyan();
                characters_map.at(i-1).at(j) = rgb;

                sharpedo = sharpedos.at(enemiesIndex);
                sharpedo.setPosition(i-1, j);
                sharpedo.setYRotation(0.0f);
                sharpedos.at(enemiesIndex) = sharpedo;
            }
        }
    }
    else if(direction == 2) //east
    {
        if(j > 0)
        {
            rgb = characters_map.at(i).at(j-1);
            stage_rgb = stage_map.at(i).at(j-1);
            if(rgb.isBlue() && stage_rgb.isBlue())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setCyan();
                characters_map.at(i).at(j-1) = rgb;

                sharpedo = sharpedos.at(enemiesIndex);
                sharpedo.setPosition(i, j-1);
                sharpedo.setYRotation(270.0f);
                sharpedos.at(enemiesIndex) = sharpedo;
            }
        }
    }
    else if(direction == 3) //south
    {
        if(i < 31)
        {
            rgb = characters_map.at(i+1).at(j);
            stage_rgb = stage_map.at(i+1).at(j);
            if(rgb.isBlue() && stage_rgb.isBlue())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setCyan();
                characters_map.at(i+1).at(j) = rgb;

                sharpedo = sharpedos.at(enemiesIndex);
                sharpedo.setPosition(i+1, j);
                sharpedo.setYRotation(180.0f);
                sharpedos.at(enemiesIndex) = sharpedo;
            }
        }
    }
    else if(direction == 4) // west
    {
        if(j < 31)
        {
            rgb = characters_map.at(i).at(j+1);
            stage_rgb = stage_map.at(i).at(j+1);
            if(rgb.isBlue() && stage_rgb.isBlue())
            {
                rgb.setBlue();
                characters_map.at(i).at(j) = rgb;
                rgb.setCyan();
                characters_map.at(i).at(j+1) = rgb;

                sharpedo = sharpedos.at(enemiesIndex);
                sharpedo.setPosition(i, j+1);
                sharpedo.setYRotation(90.0f);
                sharpedos.at(enemiesIndex) = sharpedo;
            }
        }
    }
}

void GameMap::moveEnemies()
{
    srand (time(NULL));

    for(int k=0; k<scythers.size(); k++)
    {
        int direction = rand() % 4 + 1;
        Scyther scyther = scythers.at(k);
        moveAScyther(scyther.getPosition().i,scyther.getPosition().j,k,direction);
    }

    for(int k=0; k<sharpedos.size(); k++)
    {
        int direction = rand() % 5 + 1;
        Sharpedo sharpie = sharpedos.at(k);
        moveASharpedo(sharpie.getPosition().i,sharpie.getPosition().j,k,direction);
    }

    std::vector<Scyther> livingScythers;

    for(int k=0; k<scythers.size(); k++)
    {
        Scyther s = scythers.at(k);
        if(!isScytherDead(k))
            livingScythers.push_back(s);
    }
    scythers = livingScythers;
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
