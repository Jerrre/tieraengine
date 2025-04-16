#ifndef GLOBAL_H
#define GLOBAL_H

const unsigned int SCREEN_WIDTH = 640;//1920;
const unsigned int SCREEN_HEIGHT = 480;// 1080;

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
enum ColliderType {
    SPHERE,
    BOX
};
struct Sphere
{
    glm::vec3 pos;
    unsigned int rad;
};
struct Box
{
    glm::vec3 min;
    glm::vec3 max;
};

#endif GLOBAL_H