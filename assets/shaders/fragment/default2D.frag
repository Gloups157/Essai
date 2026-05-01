#version 460 core

in vec2 textureCoords;
flat in uint textureId;

out vec4 FragColor;

uniform sampler2D textures[32];

void main() {
    FragColor = texture(textures[textureId], textureCoords);
}
