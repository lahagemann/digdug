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

        bool checkEnemyCollision();
        bool checkObstacleCollision(Diglett::Direction direction);
        bool isEnemyPushable(int i, int j, float playerRotation);
        bool isPlayerAboveHole();
        bool isPlayerAboveWater();
        bool isPlayerDead();
        void makeCrack();
        void moveAScyther(int i, int j, int enemiesIndex);
        void moveASharpedo(int i, int j, int enemiesIndex);
        void moveEnemies();
        void push();

        Diglett player;

    private:
        std::vector< std::vector<A_RGB> > original_map;
        std::vector< std::vector<A_RGB> > stage_map;
        std::vector< std::vector<A_RGB> > characters_map;

        // object control matrixes:
        std::vector<Character> characters;
};

#endif // GAMEMAP_H
