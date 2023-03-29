//
//  triangle.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#include "geometry.hpp"

void Line::updateEnd(vec3 end) {
    vertices[1] = end;
    updateBuffer();
}
void Line::setMode(DrawMode mode) {}

void Triangle::updateEnd(vec3 end) {
    vertices[0] = vec3((startPoint.x + end.x) / 2, startPoint.y, 0);
    vertices[1] = vec3(startPoint.x, end.y, 0);
    vertices[2] = vec3(end.x, end.y, 0);
    updateBuffer();
}

void Rect::updateEnd(vec3 end) {
    vertices[0] = startPoint;
    vertices[1] = vec3(startPoint.x, end.y, 0.0f);
    vertices[2] = end;
    vertices[3] = vec3(end.x, startPoint.y, 0.0f);
    updateBuffer();
}
void Rect::setMode(DrawMode mode) {
    switch (mode) {
        case Filled:
            renderType = GL_TRIANGLE_FAN;
            break;
        case Outlined:
            renderType = GL_LINE_LOOP;
            break;
        default:
            break;
    }
}

void Circle::updateEnd(vec3 end) {
    
}
