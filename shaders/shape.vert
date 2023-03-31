#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 color;

uniform mat4 MVP;

out vec3 ourColor;
out vec2 TexCoord;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    ourColor = color;
    TexCoord = aTexCoord;
}
