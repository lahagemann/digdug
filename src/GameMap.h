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
        void load_stage();
        void flood_fill();
        bool allow_movement(Character *character);

        Diglett player;

    private:
        std::vector< std::vector<A_RGB> > original_map;
        std::vector< std::vector<A_RGB> > stage_map;
        std::vector< std::vector<A_RGB> > characters_map;

        std::vector<Scyther> enemies;
        std::vector<Sharpedo> sharpedos;
        std::vector<Snorlax> rocks;
        //std::vector<Floor> floor;
        //std::vector<Crack> cracks;
};

#endif // GAMEMAP_H
