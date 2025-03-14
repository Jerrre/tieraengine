#include "render.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "map_parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <stb_image.h>
#include <stb_image_write.h>

int main(void)
{
    Render rd;
    rd.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "fpsgl");

    std::vector<Mesh> map;
    glm::vec3 playerOrig;
    map = parse_map("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\space01.map", &playerOrig);

    float test;
    std::ifstream datafile;
    datafile.open("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\test.dat", std::ios::binary | std::ios::in);
    datafile.read(reinterpret_cast<char*>(&test), sizeof(float));
    datafile.close();
    std::cout << test << std::endl;


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