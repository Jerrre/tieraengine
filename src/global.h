#ifndef GLOBAL_H
#define GLOBAL_H

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

const std::string globTexPath = "C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\";
const std::string globMapPath = "C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\";

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

#endif GLOBAL_H