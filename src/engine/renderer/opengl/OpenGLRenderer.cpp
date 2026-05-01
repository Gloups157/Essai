#include "../../../../include/engine/renderer/opengl/OpenGLRenderer.h"

// void OpenGLRenderer::createSprite() {
//     glGenVertexArrays(1, &vao);
//     glBindVertexArray(vao);
//
//     glGenBuffers(1, &vbo);
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
//
//     glGenBuffers(1, &ebo);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
//
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//     glEnableVertexAttribArray(1);
// }
//
// void OpenGLRenderer::drawSprite(const glm::mat4& model, Shader& shader, std::vector<Texture>& textures, const glm::mat4& cameraView, const glm::mat4& cameraProjection) {
//     glBindVertexArray(vao);
//     if (!textures.empty()) {
//         textures[0].use(GL_TEXTURE0);
//         textures[1].use(GL_TEXTURE1);
//         shader.setInt("tex1", 0);
//         shader.setInt("tex2", 1);
//         glActiveTexture(GL_TEXTURE0);
//         glBindTexture(GL_TEXTURE_2D, textures[0].id);
//         glActiveTexture(GL_TEXTURE1);
//         glBindTexture(GL_TEXTURE_2D, textures[1].id);
//     }
//     shader.use();
//     shader.setMat4("view", cameraView);
//     shader.setMat4("projection", cameraProjection);
//     shader.setMat4("model", model);
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
// }
