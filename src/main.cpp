#include "render.h"

int main(void)
{
    Render rd;
    rd.init_window(640, 480, "fpsgl");
    
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

    rd.create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));

    while (!rd.window_should_close())
    {
        rd.clear_background(rd.BLACK);
        rd.draw(rd.WHITE);
    }

    rd.close_window();

    return 0;
}