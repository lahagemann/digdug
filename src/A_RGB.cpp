#include "A_RGB.h"

A_RGB::A_RGB(int red, int green, int blue)
{
    r = red;
    g = green;
    b = blue;
}

A_RGB::~A_RGB()
{
    //dtor
}

bool A_RGB::isRed()
{
    if(r == 255 && g == 0 && b == 0)
        return true;
    else
        return false;
}

bool A_RGB::isGreen()
{
    if(r == 0 && g == 255 && b == 0)
        return true;
    else
        return false;
}

bool A_RGB::isBlue()
{
    if(r == 0 && g == 0 && b == 255)
        return true;
    else
        return false;
}

bool A_RGB::isCyan()
{
    if(r == 0 && g == 255 && b == 255)
        return true;
    else
        return false;
}

bool A_RGB::isMagenta()
{
    if(r == 255 && g == 0 && b == 255)
        return true;
    else
        return false;
}

bool A_RGB::isYellow()
{
    if(r == 255 && g == 255 && b == 0)
        return true;
    else
        return false;
}

bool A_RGB::isBlack()
{
    if(r == 0 && g == 0 && b == 0)
        return true;
    else
        return false;
}

bool A_RGB::isWhite()
{
    if(r == 255 && g == 255 && b == 255)
        return true;
    else
        return false;
}

