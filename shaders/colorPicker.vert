#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;

out vec2 uv;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    uv = vec2(aTexCoord.x - 0.5, 0.5 - aTexCoord.y);
}
