#include "render.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "map_parser.h"

#include <stb_image.h>
#include <stb_image_write.h>

int main(void)
{
    Render rd;
    rd.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "fpsgl");

    int width, height, nrChannels;
    unsigned char* data1;
    unsigned char* data2;
    unsigned char* data3;

    data1 = stbi_load("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\metal_001.png", &width, &height, &nrChannels, 0);
    data2 = stbi_load("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\metal_002.png", &width, &height, &nrChannels, 0);
    data3 = stbi_load("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\metal_broken_001.png", &width, &height, &nrChannels, 0);

    unsigned int img_size = width * height * nrChannels * sizeof(unsigned char);

    unsigned char* test;
    test = (unsigned char*)malloc(3*img_size);
    memcpy(test,              data1, img_size);
    memcpy(test + img_size,   data2, img_size);
    memcpy(test + 2*img_size, data3, img_size);

    stbi_write_png("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\textures\\test.png", width, 3*height, nrChannels, test, nrChannels * width);


    std::vector<Mesh> map;
    glm::vec3 playerOrig;
    map = parse_map("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\space01.map", &playerOrig);

    playerOrig = playerOrig * glm::vec3(0.02);

    for (int m = 0; m < map.size(); m++) {
        map[m].model = glm::scale(map[m].model, glm::vec3(0.02, 0.02, 0.02));
    }

    Camera cam = Camera(
        //glm::vec3(0.0f, 1.0f, 3.0f), 
        playerOrig,
        glm::vec3(0.0f, 0.0f, -1.0f), 
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 proj = glm::perspective(glm::radians(cam.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    Shader shader;
    shader.create_shader();

    while (!rd.window_should_close())
    {
        rd.startDraw();
        rd.clear_background(rd.BLACK);
        cam.update(rd.getMouseOffset());

        if (rd.processInput() == UP)
            cam.position += cam.speed * cam.front * rd.deltaTime;
        if (rd.processInput() == DOWN)
            cam.position -= cam.speed * cam.front * rd.deltaTime;
        if (rd.processInput() == LEFT)
            cam.position -= glm::normalize(glm::cross(cam.front, cam.up)) * cam.speed * rd.deltaTime;
        if (rd.processInput() == RIGHT)
            cam.position += glm::normalize(glm::cross(cam.front, cam.up)) * cam.speed * rd.deltaTime;
        
        for (int m = 0; m < map.size(); m++){
            map[m].draw(shader, rd.WHITE, cam.view, proj);
        }
        rd.end_draw();    
    }
    rd.close_window();

    return 0;
}