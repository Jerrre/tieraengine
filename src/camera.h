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
        Camera(glm::vec3 _position, glm::vec3 _front, glm::vec3 _up);
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::mat4 view;
        float speed = 5.0f;   
        void update(glm::vec2 mouseOffset);
    private:
        float yaw = -90.0f;
        float pitch = 0.0f;
    
};