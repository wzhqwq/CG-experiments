#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 color;
layout (location = 3) in int renderMode;

uniform mat4 MVP;

out vec3 ourColor;
out vec2 TexCoord;
flat out int mode;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    ourColor = color;
    TexCoord = aTexCoord;
    mode = renderMode;
}
