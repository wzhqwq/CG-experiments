#version 330 core

in vec3 ourColor; //output color from vertexshader
in vec2 TexCoord;
flat in int mode;

out vec4 color;

uniform sampler2D ourTexture;

void main() {
    vec4 textureColor = texture(ourTexture, TexCoord);
    if (mode == 0) {
        color = vec4(ourColor, 1.0);
    }
    else if (mode == 1) {
        color = vec4(textureColor.a * ourColor + (1 - textureColor.a) * vec3(1.0, 1.0, 1.0), 1.0);
    }
    else if (mode == 2) {
        color = textureColor;
    }
    else {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
