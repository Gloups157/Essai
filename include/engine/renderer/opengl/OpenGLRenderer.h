#ifndef OPEN_GL_RENDERER_H
#define OPEN_GL_RENDERER_H

#include <iostream>
#include <glm/vec2.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../ARenderer.h"
#include "OpenGLCore.h"
#include "OpenGLTextureLibrary.h"
#include "core/Types.h"
#include "engine/ecs/components/Transform.h"
#include "engine/ecs/components/Renderer2D.h"
#include "engine/renderer/Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 uv;
    unsigned int bufferTextureId;
};

class OpenGLRenderer : public ARenderer {
public:
    constexpr auto initializeIndices() {
        std::array<unsigned int, Core::MAX_INDICES> indicesArray {};
        for (unsigned int i = 0; i < Core::MAX_QUADS; ++i) {
            size_t quadIndices = i * 6;
            indicesArray[quadIndices] = i;
            indicesArray[quadIndices+1] = i + 1;
            indicesArray[quadIndices+2] = i + 2;
            indicesArray[quadIndices+3] = i + 3;
            indicesArray[quadIndices+4] = i;
            indicesArray[quadIndices+5] = i + 2;
        }
        return indicesArray;
    }

    OpenGLRenderer(size_t capacity = Core::DEFAULT_CAPACITY) {
        indices = initializeIndices();

        shader = new Shader("../assets/shaders/vertex/default2D.vert", "../assets/shaders/fragment/default2D.frag");

        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glCreateBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, Core::MAX_VERTICES * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Core::MAX_INDICES * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, uv));
        glEnableVertexAttribArray(1);

        glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(Vertex), (const void*) offsetof(Vertex, bufferTextureId));
        glEnableVertexAttribArray(2);
    }

    void addSprite(const Component::Transform& transform, const Component::Renderer2D& renderer2D) override {
        const glm::vec3 position = transform.position;
        const float halfHeight = renderer2D.height * 0.5f;
        const float halfWidth = renderer2D.width * 0.5f;
        auto textureId = renderer2D.textureId;
        textureLibrary.addTextureToBuffer(textureId);
        unsigned int bufferTextureId = textureLibrary.getBufferTextureId(textureId);
        vertices.push_back({{position + glm::vec3(-halfWidth, halfHeight, 0.0f)}, {0.0f, 0.0f}, bufferTextureId});
        vertices.push_back({{position + glm::vec3(-halfWidth, -halfHeight, 0.0f)}, {0.0f, 1.0f}, bufferTextureId});
        vertices.push_back({{position + glm::vec3(halfWidth, -halfHeight, 0.0f)}, {1.0f, 1.0f}, bufferTextureId});
        vertices.push_back({{position + glm::vec3(halfWidth, halfHeight, 0.0f)}, {1.0f, 0.0f}, bufferTextureId});
    }

    void flush(const glm::mat4& view, const glm::mat4& projection) override {
        glBindVertexArray(vao);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        textureLibrary.bindTextures();
        shader->use();
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        shader->setIntArray("textures[32]", textureLibrary.getBufferTexturesArray());
        glDrawElements(GL_TRIANGLES, vertices.size() / 4 * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        vertices.clear();
        textureLibrary.clearBuffers();
    }

    void registerTexture(Core::AssetPath texturePath) override {
        textureLibrary.registerTexture(texturePath);
    }

    bool shouldFlush() override {
        return textureLibrary.isTextureBufferFull() || vertices.size() >= Core::MAX_VERTICES;
    }

    bool isBufferEmpty() override {
        return vertices.empty();
    }

private:
    GLuint vao, vbo, ebo;
    std::vector<Vertex> vertices;
    std::array<unsigned int, Core::MAX_INDICES> indices;
    OpenGLTextureLibrary textureLibrary;

    Shader* shader;
};

#endif //OPEN_GL_RENDERER_H