#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoords;
layout (location = 2) in uint inTextureId;

out vec2 textureCoords;
flat out uint textureId;

uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * vec4(inPosition, 1.0);
    textureCoords = inTextureCoords;
    textureId = inTextureId;
}
