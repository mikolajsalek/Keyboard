#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 vertex;
in vec2 texCoord;

out vec2 TexCoord;

void main(void) {
    gl_Position = P * V * M * vertex;
    TexCoord = texCoord;
}