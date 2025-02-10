#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

struct Color;

class Shader {
    public:
        Shader(){};

        void create_shader();
        void set_matrices(glm::mat4 transform, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
        void set_color(Color color);
        void set_texture(unsigned int texUnit);
        void use();
        unsigned int shaderProgram;
    private:

};