#ifndef A_RGB_H
#define A_RGB_H


class A_RGB
{
    public:
        A_RGB();
        A_RGB(int red, int green, int blue);
        virtual ~A_RGB();
        bool isRed();
        bool isGreen();
        bool isBlue();
        bool isCyan();
        bool isMagenta();
        bool isYellow();
        bool isWhite();
        bool isBlack();

        int r;
        int g;
        int b;
};

#endif // RGB_H

