#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include "A_RGB.h"
#include "bitmap.h"
#include "Diglett.h"
#include "Scyther.h"
#include "Sharpedo.h"
#include "Snorlax.h"

#define GROUND_HEIGHT 0
#define SEA_HEIGHT -1

class GameMap
{
    public:
        GameMap();
        virtual ~GameMap();

        bool checkEnemyCollision(int i, int j);
        bool checkObstacleCollision(Diglett::Direction direction);
        void flood_fill();
        bool isEnemyPushable(int i, int j, float playerRotation);
        bool isPlayerAboveHole();
        bool isPlayerAboveWater();
        bool isPlayerDead();
        void load_models();
        void makeCrack();
        void moveAScyther(int i, int j, int enemiesIndex);
        void moveASharpedo(int i, int j, int enemiesIndex);
        void moveEnemies();
        void push();

        Diglett player;

    private:
        std::vector< std::vector<A_RGB> > stage_map;
        std::vector< std::vector<A_RGB> > characters_map;
        std::vector<Scyther> scythers;
        std::vector<Sharpedo> sharpedos;
        std::vector<Snorlax> snorlaxs;
};

#endif // GAMEMAP_H
