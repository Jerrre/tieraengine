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

class Body {
public:
    Body();
    glm::vec3 position = { 0,0,0 };
    std::vector<Box> colliders;
    void update(glm::vec3 new_position);
    float collider_size = 0;
private:
};
#endif BODY_H