//
//  selection.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/4/3.
//

#include "selection.hpp"

void SelectionRect::updateBox(vec3 bl, vec3 tr) {
    top = tr.y;
    bottom = bl.y;
    left = bl.x;
    right = tr.x;
    update();
}

void SelectionRect::updateScale(float scale) {
    currentScale = scale;
    update();
}

void SelectionRect::update() {
    // bottom
    updateSection(0,
                  vec4(left - DOT_SIZE / currentScale, left, bottom - DOT_SIZE / currentScale, bottom),
                  vec4(0.0, 0.3, 0.0, 0.3));
    updateSection(12,
                  vec4(left, right, bottom - DOT_SIZE / currentScale, bottom),
                  vec4(0.3, 0.7, 0.0, 0.3));
    updateSection(24,
                  vec4(right, right + DOT_SIZE / currentScale, bottom - DOT_SIZE / currentScale, bottom),
                  vec4(0.7, 1.0, 0.0, 0.3));
    
    // center
    updateSection(36,
                  vec4(left - DOT_SIZE / currentScale, left, bottom, top),
                  vec4(0.0, 0.3, 0.3, 0.7));
    updateSection(48,
                  vec4(left, right, bottom, top),
                  vec4(0.3, 0.7, 0.3, 0.7));
    updateSection(60,
                  vec4(right, right + DOT_SIZE / currentScale, bottom, top),
                  vec4(0.7, 1.0, 0.3, 0.7));
    
    // top
    updateSection(72,
                  vec4(left - DOT_SIZE / currentScale, left, top, top + DOT_SIZE / currentScale),
                  vec4(0.0, 0.3, 0.7, 1.0));
    updateSection(84,
                  vec4(left, right, top, top + DOT_SIZE / currentScale),
                  vec4(0.3, 0.7, 0.7, 1.0));
    updateSection(96,
                  vec4(right, right + DOT_SIZE / currentScale, top, top + DOT_SIZE / currentScale),
                  vec4(0.7, 1.0, 0.7, 1.0));
    
    updateBuffer();
}

// rect: left right bottom top
void SelectionRect::updateSection(int offset, vec4 vertRect, vec4 texRect) {
    vertices[offset] = vec3(vertRect[0], vertRect[2], 900.0);
    vertices[offset + 1] = vec3(texRect[0], texRect[2], 900.0);
    vertices[offset + 2] = vec3(vertRect[0], vertRect[3], 900.0);
    vertices[offset + 3] = vec3(texRect[0], texRect[3], 900.0);
    vertices[offset + 4] = vec3(vertRect[1], vertRect[3], 900.0);
    vertices[offset + 5] = vec3(texRect[1], texRect[3], 900.0);
    
    vertices[offset + 6] = vec3(vertRect[1], vertRect[3], 900.0);
    vertices[offset + 7] = vec3(texRect[1], texRect[3], 900.0);
    vertices[offset + 8] = vec3(vertRect[1], vertRect[2], 900.0);
    vertices[offset + 9] = vec3(texRect[1], texRect[2], 900.0);
    vertices[offset + 10] = vec3(vertRect[0], vertRect[2], 900.0);
    vertices[offset + 11] = vec3(texRect[0], texRect[2], 900.0);
}

void SelectionRect::drawSelf() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    paint();
    glDisable(GL_BLEND);
}
