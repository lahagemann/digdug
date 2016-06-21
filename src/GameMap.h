#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Diglett.h"
#include "Scyther.h"
#include "Sharpedo.h"
#include "Snorlax.h"
#include "bitmap.h"
#include "A_RGB.h"

#define GROUND_HEIGHT 0
#define SEA_HEIGHT -1


class GameMap
{
    public:
        GameMap();
        virtual ~GameMap();
        void load_models();
        void flood_fill();
        bool allow_movement(Character *character);

        bool checkEnemyCollision(Diglett::Direction direction);
        bool checkObstacleCollision(Diglett::Direction direction);

        Diglett player;

    private:
        std::vector< std::vector<A_RGB> > original_map;
        std::vector< std::vector<A_RGB> > stage_map;
        std::vector< std::vector<A_RGB> > characters_map;

        std::vector<Scyther> enemies;
        std::vector<Sharpedo> sharpedos;
        std::vector<Snorlax> rocks;

        // three levels of object control matrixes:
        std::vector< std::vector<Character> > characters;
        std::vector< std::vector<Ground> > ground;
        //std::vector< std::vector<Sea> > sea;
};

#endif // GAMEMAP_H
