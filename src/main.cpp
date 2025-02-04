#include "render.h"

int main(void)
{
    Render rd;
    rd.init_window(640, 480, "fpsgl");
    
    float vertices[] = {
        // positions          // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

    rd.create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    Image img = rd.load_image("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\container.png");
    rd.create_texture(img);
    
    while (!rd.window_should_close())
    {
        rd.clear_background(rd.BLACK);
        rd.draw(rd.WHITE);
        rd.set_default_shader_transform(trans);
    }

    rd.close_window();

    return 0;
}