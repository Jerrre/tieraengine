#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "global.h"
#include "body.h"

class Mesh;
class Shader;

class GameObject {
public:
    GameObject();
    glm::vec3 position = { 0,0,0 };
    std::vector<Mesh> meshes;
    Body body;
    void set_scale(float newScale);
    void draw(Shader& shader, Color color, glm::mat4 view, glm::mat4 projection);
    void update();
private:
    float scale = 1.0;
};
#endif GAME_OBJECT_H