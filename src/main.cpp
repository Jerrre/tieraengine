#include "render.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"

int main(void)
{
    Render rd;
    rd.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "fpsgl");
    float vertex_arr[] = {
        -0.5f,-0.5f,-0.5f, 
        0.5f,-0.5f,-0.5f, 
        0.5f, 0.5f,-0.5f, 
        0.5f, 0.5f,-0.5f, 
        0.5f, 0.5f,-0.5f, 
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,
        0.5f,-0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f,-0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f, 
        0.5f, 0.5f,-0.5f, 
        0.5f,-0.5f,-0.5f, 
        0.5f,-0.5f,-0.5f, 
        0.5f,-0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f, 
        -0.5f,-0.5f,-0.5f,
        0.5f,-0.5f,-0.5f, 
        0.5f,-0.5f, 0.5f, 
        0.5f,-0.5f, 0.5f, 
        -0.5f,-0.5f, 0.5f,
        -0.5f,-0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,
        0.5f, 0.5f,-0.5f, 
        0.5f, 0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f,-0.5f
 };
    float tex_arr[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        0.0f,1.0f,
        0.0f,0.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        1.0f,1.0f,
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f,
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f,
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f
 };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Mesh mesh;

    for (int i=0; i<sizeof(vertex_arr); i+=3)
    {
        mesh.vertices.push_back(glm::vec3(vertex_arr[i], vertex_arr[i+1], vertex_arr[i+2]));
    }
    for (int i=0; i<sizeof(tex_arr); i+=2)
    {
        mesh.texCoords.push_back(glm::vec2(tex_arr[i], tex_arr[i+1]));
    }

    mesh.create_mesh();

    mesh.shader->create_shader();

    mesh.texture->load_image("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\container.png");
    mesh.texture->create_texture();

    Camera cam = Camera(
        glm::vec3(0.0f, 0.0f, 3.0f), 
        glm::vec3(0.0f, 0.0f, -1.0f), 
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 proj = glm::perspective(glm::radians(cam.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    while (!rd.window_should_close())
    {
        rd.startDraw();

        rd.clear_background(rd.BLACK);

        for (int i = 0; i < 10; i++){
            float angle = (3.0f/10000)*i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.1f, 0.9f));
        }

        cam.update(rd.getMouseOffset());

        if (rd.processInput() == UP)
            cam.position += cam.speed * cam.front * rd.deltaTime;
        if (rd.processInput() == DOWN)
            cam.position -= cam.speed * cam.front * rd.deltaTime;
        if (rd.processInput() == LEFT)
            cam.position -= glm::normalize(glm::cross(cam.front, cam.up)) * cam.speed * rd.deltaTime;
        if (rd.processInput() == RIGHT)
            cam.position += glm::normalize(glm::cross(cam.front, cam.up)) * cam.speed * rd.deltaTime;
        
        mesh.draw(rd.RED, model, cam.view, proj);

        rd.end_draw();    
    }

    rd.close_window();

    return 0;
}