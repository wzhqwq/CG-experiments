#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in float size;
layout (location = 3) in vec2 translate;
out vec2 uv;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    uv = (position.xy + translate) / size;
    uv.y = -uv.y;
}
