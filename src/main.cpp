#include "render.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "physics.h"
#include "body.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <stb_image.h>
#include <stb_image_write.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

int main(void)
{
    Render rd;
    rd.init_window(SCREEN_WIDTH, SCREEN_HEIGHT, "fpsgl");

    Body map;
    glm::vec3 playerOrig;

    std::ifstream mapfile;
    mapfile.open("C:\\Users\\jp-om\\Documents\\repos\\fpsgl\\resources\\space01.dat", std::ios::binary | std::ios::in);

    int meshCount = 0;
    mapfile.read(reinterpret_cast<char*>(&meshCount), sizeof(meshCount));

    glm::vec3 vertex;
    glm::vec2 texCoord;

    for (int meshInd = 0; meshInd < meshCount; meshInd++){
        Mesh newMesh;
        int vertexCount;
        mapfile.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));

        for (int vertInd = 0; vertInd < vertexCount; vertInd++) {
            mapfile.read(reinterpret_cast<char*>(&vertex), sizeof(vertex));
            mapfile.read(reinterpret_cast<char*>(&texCoord), sizeof(texCoord));
            newMesh.vertices.push_back(vertex);
            newMesh.texCoords.push_back(texCoord);
        }

        int texSize;
        unsigned char* imgData;
        mapfile.read(reinterpret_cast<char*>(&texSize), sizeof(texSize));
        imgData = (unsigned char*)malloc(texSize);
        if (imgData == NULL) {
            std::cout << "Malloc error:\n" << std::endl;
        }
        mapfile.read(reinterpret_cast<char*>(imgData), texSize);

        newMesh.texture.load_image_from_memory(imgData, texSize);
        newMesh.texture.create_texture();
        newMesh.create_mesh();
        map.meshes.push_back(newMesh);

        free(imgData);
    }
    int colliderCount;
    mapfile.read(reinterpret_cast<char*>(&colliderCount), sizeof(colliderCount));
    for (int box = 0; box < colliderCount; box++) {
        Box newCollider;
        mapfile.read(reinterpret_cast<char*>(&newCollider), sizeof(Box));
        map.colliders.push_back(newCollider);
    }

    mapfile.close();

    playerOrig = playerOrig * glm::vec3(0.02);

    map.set_scale(0.02);

    Camera cam = Camera(
        glm::vec3(-8.0f, 0.5f, 0.0f), 
        //playerOrig,
        glm::vec3(0.0f, 0.0f, -1.0f), 
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 proj = glm::perspective(glm::radians(cam.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    Shader shader;
    shader.create_shader();

    Box playerCollider;
    float colliderSize = 0.6;
    playerCollider.min = cam.position;
    playerCollider.max = playerCollider.min + glm::vec3(colliderSize);

    bool colliding = false;
    while (!rd.window_should_close())
    {
        rd.startDraw();
        rd.clear_background(rd.BLACK);
        cam.update(rd.getMouseOffset());
        

        if (colliding) {
            cam.position -= cam.front*glm::vec3(0.03);
        }
        else {
            if (rd.processInput() == UP)
                cam.position += cam.speed * cam.front * rd.deltaTime;
            if (rd.processInput() == DOWN)
                cam.position -= cam.speed * cam.front * rd.deltaTime;
            if (rd.processInput() == LEFT)
                cam.position -= glm::normalize(glm::cross(cam.front, cam.up)) * cam.speed * rd.deltaTime;
            if (rd.processInput() == RIGHT)
                cam.position += glm::normalize(glm::cross(cam.front, cam.up)) * cam.speed * rd.deltaTime;
        }
        //
        //playerCollider.min = cam.position;
        //playerCollider.max = playerCollider.min + glm::vec3(colliderSize);
        //for (int obj = 0; obj < colliders.size(); obj++) {
        //    if (is_aabb_colliding(playerCollider, colliders[obj])) {
        //        colliding = true;
        //        break;
        //    }
        //    else {
        //        colliding = false;
        //    }
        //}
        //
        map.draw(shader, rd.WHITE, cam.view, proj);

        rd.end_draw();    
    }
    rd.close_window();

    return 0;
}