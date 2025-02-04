#include "render.h"

int main(void)
{
    Render rd;
    unsigned int width, height;
    width = 640;
    height = 480;
    rd.init_window(width, height, "fpsgl");
    float vertices[] = {
    -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
 0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
 0.5f, 0.5f,-0.5f, 1.0f, 1.0f,
 0.5f, 0.5f,-0.5f, 1.0f, 1.0f,
0.5f, 0.5f,-0.5f, 0.0f,1.0f,
-0.5f,-0.5f,-0.5f, 0.0f,0.0f,
-0.5f,-0.5f, 0.5f, 0.0f,0.0f,
 0.5f,-0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,1.0f,
 0.5f, 0.5f, 0.5f, 1.0f,1.0f,
 -0.5f, 0.5f, 0.5f, 0.0f,1.0f,
 -0.5f,-0.5f, 0.5f, 0.0f,0.0f,
 -0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 -0.5f, 0.5f,-0.5f, 1.0f,1.0f,
 -0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 -0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 -0.5f,-0.5f, 0.5f, 0.0f,0.0f,
 -0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f,-0.5f, 1.0f,1.0f,
 0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 0.5f,-0.5f, 0.5f, 0.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 -0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 0.5f,-0.5f,-0.5f, 1.0f,1.0f,
 0.5f,-0.5f, 0.5f, 1.0f,0.0f,
 0.5f,-0.5f, 0.5f, 1.0f,0.0f,
 -0.5f,-0.5f, 0.5f, 0.0f,0.0f,
 -0.5f,-0.5f,-0.5f, 0.0f,1.0f,
 -0.5f, 0.5f,-0.5f, 0.0f,1.0f,
 0.5f, 0.5f,-0.5f, 1.0f,1.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 0.5f, 0.5f, 0.5f, 1.0f,0.0f,
 -0.5f, 0.5f, 0.5f, 0.0f,0.0f,
 -0.5f, 0.5f,-0.5f, 0.0f,1.0f
 };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };


    glm::mat4 trans = glm::mat4(1.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    rd.create_mesh(vertices, sizeof(vertices), indices, sizeof(indices));
    Image img = rd.load_image("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\container.png");
    rd.create_texture(img);

    model = glm::translate(model, glm::vec3(1.0f, 2.0f, -1.0f));
    
    while (!rd.window_should_close())
    {
        rd.clear_background(rd.BLACK);
        rd.draw(rd.WHITE);

        for (int i = 0; i < 10; i++){
            float angle = (3.0f/10000)*i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.1f, 0.9f));
        }

        rd.set_default_shader_matrices(trans, model, view, proj);
    }

    rd.close_window();

    return 0;
}