#ifndef GLOBAL_H
#define GLOBAL_H

const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

struct Color{
    float r;
    float g;
    float b;
    float a;
};

enum Input{
    NO_INPUT,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

#endif
