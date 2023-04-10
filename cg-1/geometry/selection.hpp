//
//  selection.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/4/3.
//

#ifndef selection_hpp
#define selection_hpp

#include "common.h"
#include "geometry.hpp"
#include "texture.hpp"
#include "shader.hpp"

class SelectionRect : public Geometry {
public:
    SelectionRect(vec3 start, vec3 end) {
        renderType = GL_TRIANGLES;
        vertices.resize(108);
        updateBox(start, end);
        texture = textures.selection;
        renderMode = TexPure;
    }
    void updateBox(vec3 bl, vec3 tr);
    void updateScale(float scale);
    void drawSelf();
private:
    void update();
    void updateSection(int offset, vec4 vertRect, vec4 texRect);
    
    float currentScale = 1.0f;
    float top, bottom, left, right;
};

#endif /* selection_hpp */
