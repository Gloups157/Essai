#ifndef OPEN_GL_TEXTURE_LIBRARY_H
#define OPEN_GL_TEXTURE_LIBRARY_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stb_image.h>
#include "core/Types.h"
#include "OpenGLCore.h"

class OpenGLTextureLibrary {
public:
    OpenGLTextureLibrary() :
    maxTextureUnits(0) {
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
        bufferTextures.reserve(maxTextureUnits);
        textureIdsToBufferTextureIds.reserve(maxTextureUnits);
        texturePathsToIds.reserve(Core::MAX_TEXTURES);
    }

    void registerTexture(Core::AssetPath filename) {
        if (texturePathsToIds.find(filename) != texturePathsToIds.end()) {
            texturePathsToIds.emplace(filename, texturePathsToIds.size());
            createTexture(filename);
        }
    }

    void addTextureToBuffer(Core::TextureId textureId) {
        if (textureIdsToBufferTextureIds.find(textureId) == textureIdsToBufferTextureIds.end()) {
            textureIdsToBufferTextureIds.emplace(textureId, bufferTextures.size());
            bufferTextures.push_back(textureId);
        }
    }

    void clearBuffers() {
        bufferTextures.clear();
        textureIdsToBufferTextureIds.clear();
    }

    void bindTextures() {
        for (auto i = 0; i < bufferTextures.size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textureIdsToOpenGLTextureIds.at(bufferTextures[i]));
        }
    }

    bool isTextureBufferFull() const {
        return bufferTextures.size() == maxTextureUnits;
    }

    unsigned int getBufferTextureId(unsigned int textureId) {
        return bufferTextures[textureIdsToBufferTextureIds[textureId]];
    }

    auto getBufferTexturesArray() {
        return bufferTextures.data();
    }

    void createTexture(Core::AssetPath filename) {
        // Create texture id and bind it
        unsigned int openGLTextureId;
        glGenTextures(1, &openGLTextureId);
        glActiveTexture(GL_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, openGLTextureId);
        // set the texture wrapping/filtering options (on currently bound texture)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_set_flip_vertically_on_load(true);
        // load and generate the texture
        int width, height, channels;
        unsigned char *textureData = stbi_load(filename.data(), &width, &height, &channels, 0);
        if (textureData) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(textureData);
        textureIdsToOpenGLTextureIds.emplace(openGLTextureId, textureIdsToOpenGLTextureIds.size());
    }


private:
    int maxTextureUnits;
    std::vector<int> bufferTextures;
    std::unordered_map<unsigned int, unsigned int> textureIdsToOpenGLTextureIds;
    std::unordered_map<unsigned int, unsigned int> textureIdsToBufferTextureIds;
    std::unordered_map<Core::AssetPath, Core::TextureId> texturePathsToIds;
};

#endif //OPEN_GL_TEXTURE_LIBRARY_H