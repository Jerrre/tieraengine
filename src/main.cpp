#include "render.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "physics.h"

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

    std::ifstream mapfile;
    mapfile.open("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\space01.dat", std::ios::binary | std::ios::in);

    int meshCount = 0;
    mapfile.read(reinterpret_cast<char*>(&meshCount), sizeof(meshCount));

    glm::vec3 vertex;
    glm::vec2 texCoord;

    for (int meshInd = 0; meshInd < meshCount; meshInd++){
        Mesh newMesh;
        map.push_back(newMesh);
        int vertexCount;
        mapfile.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));

        for (int vertInd = 0; vertInd < vertexCount; vertInd++) {
            mapfile.read(reinterpret_cast<char*>(&vertex), sizeof(vertex));
            mapfile.read(reinterpret_cast<char*>(&texCoord), sizeof(texCoord));
            map[meshInd].vertices.push_back(vertex);
            map[meshInd].texCoords.push_back(texCoord);
        }

        int texSize;
        unsigned char* imgData;
        mapfile.read(reinterpret_cast<char*>(&texSize), sizeof(texSize));
        imgData = (unsigned char*)malloc(texSize);
        if (imgData == NULL) {
            std::cout << "Malloc error:\n" << std::endl;
        }
        mapfile.read(reinterpret_cast<char*>(imgData), texSize);

        map[meshInd].texture.load_image_from_memory(imgData, texSize);
        map[meshInd].texture.create_texture();
        map[meshInd].create_mesh();

        free(imgData);

    }
    mapfile.close();

    playerOrig = playerOrig * glm::vec3(0.02);


    Sphere sphere1;
    sphere1.pos = glm::vec3(0, 0, 0);
    sphere1.rad = 2;
    Sphere sphere2;
    sphere2.pos = glm::vec3(0, 5, 0);
    sphere2.rad = 2;

    Box box1;
    box1.min = glm::vec3(0, 0, 0);
    box1.max = glm::vec3(2, 2, 2);
    Box box2;
    box2.min = glm::vec3(3, 3, 3);
    box2.max = glm::vec3(4, 4, 4);

    std::cout << is_aabb_colliding(box1, box2) << std::endl;
    std::cout << is_sphere_colliding(sphere1, sphere2) << std::endl;


    for (int m = 0; m < map.size(); m++) {
        map[m].model = glm::scale(map[m].model, glm::vec3(0.02, 0.02, 0.02));
    }

    Camera cam = Camera(
        glm::vec3(0.0f, 1.0f, 3.0f), 
        //playerOrig,
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