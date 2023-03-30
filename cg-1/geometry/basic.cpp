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
int Line::isIn(vec3 point) {
    return length(vertices[0] - point) + length(vertices[1] - point) - length(vertices[0] - vertices[1]) < 3.0f;
}


void Triangle::updateEnd(vec3 end) {
    vertices[0] = vec3((startPoint.x + end.x) / 2, startPoint.y, 0);
    vertices[1] = vec3(startPoint.x, end.y, 0);
    vertices[2] = vec3(end.x, end.y, 0);
    updateBuffer();
}
int Triangle::isIn(vec3 point) {
    return 0;
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
int Rect::isIn(vec3 point) {
    vec3 v1 = min(vertices[0], vertices[2]), v2 = max(vertices[0], vertices[2]);
    return v1.x < point.x && point.x < v2.x && v1.y < point.y && point.y < v2.y;
}


void Circle::updateEnd(vec3 end) {
    vertices.clear();
    vec3 center = (startPoint + end) * 0.5f;
    width = abs(startPoint.x - end.x) / 2;
    height = abs(startPoint.y - end.y) / 2;
    vertices.push_back(center);
    int split = width * M_PI / 4;
    for (int i = 0; i < split; i++) {
        float angle = 2 * M_PI / split * i;
        vertices.push_back(center + vec3(sin(angle) * width, cos(angle) * height, 0.0f));
    }
    vertices.push_back(center + vec3(0.0f, height, 0.0f));
    updateBuffer();
}
void Circle::setMode(DrawMode mode) {
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
int Circle::isIn(vec3 point) {
    point -= vertices[0];
    return length(point * vec3(1.0f / width, 1.0f / height, 1.0f)) < 1.0f;
}
