#include "engine/renderer/Texture.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(char const* filename) {
    id = create(filename);
}

void Texture::use(GLenum layer) {
    glActiveTexture(layer);
    glBindTexture(GL_TEXTURE_2D, id);
}

GLuint Texture::create(char const *filename) {
    // Create texture id and bind it
    GLuint textureId;
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    // load and generate the texture
    int width, height, channels;
    unsigned char *textureData = stbi_load(filename, &width, &height, &channels, 0);
    if (textureData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(textureData);
    return textureId;
}
