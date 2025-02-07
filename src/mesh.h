#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <vector>

class Mesh {
    public:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texCoords;
        //std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        Mesh(){
        };
        void create_mesh();
        void draw(unsigned int shader, unsigned int texture);
    private:
        unsigned int VBO, VAO, EBO;
};