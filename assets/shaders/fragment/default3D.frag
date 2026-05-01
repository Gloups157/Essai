#version 460 core

in vec2 textureCoords;

out vec4 FragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
    FragColor = mix(texture(tex1, textureCoords), texture(tex2, textureCoords), 0.5);
}
