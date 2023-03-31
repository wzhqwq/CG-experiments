#version 330 core

in vec3 ourColor; //output color from vertexshader
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main() {
    vec4 textureColor = texture(ourTexture, TexCoord);
    color = vec4(textureColor.a * ourColor + (1 - textureColor.a) * vec3(1.0, 1.0, 1.0), 1.0);
//    color = vec4(TexCoord.x, TexCoord.y, 0.0, 1.0);
}
