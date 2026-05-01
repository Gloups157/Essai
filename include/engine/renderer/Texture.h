#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

class Texture {
public:
    Texture(char const* filename);
    void use(GLenum layer);
    GLuint id;

private:
    GLuint create(char const* filename);
};

#endif //TEXTURE_H