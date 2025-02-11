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

#include "global.h"

class Texture;
class Shader;

class Mesh {
    public:
        Mesh();
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> texCoords;
        //std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;
        Texture* texture;
        Shader* shader;
        void create_mesh();
        void draw(Color color, glm::mat4 model, glm::mat4 view, glm::mat4 projection);
    private:
        unsigned int VBO, VAO, EBO;
};