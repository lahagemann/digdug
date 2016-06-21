#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

class GameSettings
{
public:
    const unsigned char walk_forward = 119;     //w
    const unsigned char walk_back = 115;        //s
    const unsigned char rotate_right = 100;     //d
    const unsigned char rotate_left = 97;       //a
    const unsigned char push_enemy = 102;       //f
    const unsigned char change_camera = 118;    //v
    const unsigned char make_crack = 32;        //spacebar

    const unsigned char pause = 112;            //p
    const unsigned char quit = 27;              //esc
};

#endif // GAMESETTINGS_H
