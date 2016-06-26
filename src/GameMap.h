#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
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
        void clean_cracks();
        void flood_fill();
        void flood_step(int i, int j);
        std::vector< std::vector<A_RGB> > getCharactersMap();
        std::vector<Scyther> getScythers();
        std::vector<Sharpedo> getSharpedos();
        std::vector<Snorlax> getSnorlaxs();
        std::vector< std::vector<A_RGB> > getStageMap();
        bool isEnemyPushable(int i, int j, float playerRotation);
        bool isPlayerAboveHole();
        bool isPlayerAboveWater();
        bool isPlayerDead(int time);
        bool isPlayerNearEnemy(int enemiesIndex, int* direction);
        bool isScytherDead(int enemiesIndex);
        void load_models();
        void makeCrack();
        void moveAScyther(int i, int j, int enemiesIndex, int direction);
        void moveASharpedo(int i, int j, int enemiesIndex, int direction);
        void moveEnemies();
        bool playerWon();
        void push(int seconds);

        Diglett player;

    private:
        std::vector< std::vector<A_RGB> > stage_map;
        std::vector< std::vector<A_RGB> > characters_map;
        std::vector< std::vector<A_RGB> > flood_map;
        std::vector<Scyther> scythers;
        std::vector<Sharpedo> sharpedos;
        std::vector<Snorlax> snorlaxs;

        int field_size;
        int flood_size;
        int lastTimeEnemyPushed;
};

#endif // GAMEMAP_H
