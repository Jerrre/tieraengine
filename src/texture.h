#ifndef TEXTURE_H
#define TEXTURE_H

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

struct Image{
    int width, height, nrChannels;
    unsigned char* data;
};

class Texture {
    public:
        void load_image(const char *path);
        void create_texture();

        Texture(){
        };
        unsigned int texture;
        unsigned int get_texture(){return texture;};
        Image img = {0};
    private:
};

#endif // !TEXTURE_H