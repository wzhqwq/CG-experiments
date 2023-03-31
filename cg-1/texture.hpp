//
//  texture.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/29.
//

#ifndef texture_hpp
#define texture_hpp

#include "stb_image.h"
#include "common.h"

struct Textures {
    GLuint triangle, rect, circle, hand, line, pointer, pen, colors;
};

GLuint loadTexture(const char *textureUrl, const char *fileName);
void initTexture(const char *textureUrl);

extern Textures textures;

#endif /* texture_hpp */
