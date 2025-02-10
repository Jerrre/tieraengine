#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "global.h"

class Camera {
    public:
        Camera(glm::vec3 _position);
        glm::vec3 position;
        glm::mat4 view;
        
    private:
        
};