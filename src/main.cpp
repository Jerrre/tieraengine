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
    
    while (!window_should_close())
    {
        clear_background(0.2f, 0.3f, 0.3f, 1.0f);
        draw();
    }

    close_window();

    return 0;
}