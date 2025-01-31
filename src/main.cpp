#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.h"

int main(void)
{
    init_window(640, 480, "fpsgl");
    
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    
    Color white;
    white.r = 1.0;
    white.g = 1.0;
    white.b = 1.0;
    white.a = 1.0;

    Color test;
    test.r = 0.2;
    test.g = 0.5;
    test.b = 1.0;
    test.a = 1.0;

    while (!window_should_close())
    {
        clear_background(test);
        draw(white);
    }

    close_window();

    return 0;
}