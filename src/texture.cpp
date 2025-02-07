#include "texture.h"

void Texture::load_image(const char *path)
{
    stbi_set_flip_vertically_on_load(true);
    img.data = stbi_load(path, &img.width, &img.height, &img.nrChannels, 0);
    if (!img.data){
        std::cout << "Failed to load texture" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Texture::create_texture()
{
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0); // active texture unit 0, only needed if shader has multiple textures
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(img.data);
}