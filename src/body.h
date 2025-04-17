#ifndef BODY_H
#define BODY_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "global.h"

class Mesh;
class Shader;

class Body {
public:
    Body();
    glm::vec3 position;
    std::vector<Mesh> meshes;
    std::vector<Box> colliders;
    void set_scale(float newScale);
    void draw(Shader& shader, Color color, glm::mat4 view, glm::mat4 projection);
private:
    float scale = 1.0;
};
#endif BODY_H