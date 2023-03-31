//
//  texture.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/29.
//

#include "texture.hpp"

Textures textures;

GLuint loadTexture(const char *textureUrl, const char *fileName) {
    char path[255];
    snprintf(path, 255, "%s/%s", textureUrl, fileName);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (!data) return 0;
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    return texture;
}

void initTexture(const char *textureUrl) {
    textures.triangle = loadTexture(textureUrl, "triangle.png");
    textures.rect = loadTexture(textureUrl, "rect.png");
    textures.circle = loadTexture(textureUrl, "circle.png");
    textures.hand = loadTexture(textureUrl, "hand.png");
    textures.line = loadTexture(textureUrl, "line.png");
    textures.pointer = loadTexture(textureUrl, "cursor.png");
    textures.pen = loadTexture(textureUrl, "pen.png");
    textures.colors = loadTexture(textureUrl, "colors.png");
}
