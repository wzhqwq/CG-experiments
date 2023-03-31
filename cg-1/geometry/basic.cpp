//
//  triangle.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#include "geometry.hpp"

void Line::updateEnd(vec3 end) {
    vertices[0] = startPoint;
    vertices[1] = vec3(0.0, 0.0, 0.0);
    vertices[2] = end;
    vertices[3] = vec3(1.0, 1.0, 0.0);
    updateBuffer();
}
void Line::setMode(DrawMode mode) {}
int Line::isIn(vec3 point) {
    return length(vertices[0] - point) + length(vertices[1] - point) - length(vertices[0] - vertices[1]) < 3.0f;
}

void Triangle::updateEnd(vec3 end) {
    vertices[0] = vec3((startPoint.x + end.x) / 2, startPoint.y, 0);
    vertices[1] = vec3(0.5, 0.0, 0.0);
    vertices[2] = vec3(startPoint.x, end.y, 0);
    vertices[3] = vec3(0.0, 1.0, 0.0);
    vertices[4] = vec3(end.x, end.y, 0);
    vertices[5] = vec3(1.0, 1.0, 0.0);
    updateBuffer();
}
int Triangle::isIn(vec3 point) {
    return 0;
}

void Rect::updateEnd(vec3 end) {
    vertices[0] = startPoint;
    vertices[1] = vec3(0.0, 0.0, 0.0);
    vertices[2] = vec3(startPoint.x, end.y, 0.0f);
    vertices[3] = vec3(0.0, 1.0, 0.0);
    vertices[4] = end;
    vertices[5] = vec3(1.0, 1.0, 0.0);
    vertices[6] = vec3(end.x, startPoint.y, 0.0f);
    vertices[7] = vec3(1.0, 0.0, 0.0);
    updateBuffer();
}
void Rect::setMode(DrawMode mode) {
    switch (mode) {
        case Filled:
            if (renderType == GL_TRIANGLE_FAN) return;
            renderType = GL_TRIANGLE_FAN;
            break;
        case Outlined:
            if (renderType == GL_LINE_LOOP) return;
            renderType = GL_LINE_LOOP;
            break;
        default:
            break;
    }
    updateBuffer();
}
int Rect::isIn(vec3 point) {
    vec3 v1 = min(vertices[0], vertices[4]), v2 = max(vertices[0], vertices[4]);
    return v1.x < point.x && point.x < v2.x && v1.y < point.y && point.y < v2.y;
}

void Circle::updateEnd(vec3 end) {
    vertices.clear();
    vec3 center = (startPoint + end) * 0.5f;
    width = abs(startPoint.x - end.x) / 2;
    height = abs(startPoint.y - end.y) / 2;
    
    if (renderType == GL_TRIANGLE_FAN) {
        vertices.push_back(center);
        vertices.push_back(vec3(0.5, 0.5, 0.0));
    }
    int split = max(20, width * M_PI / 10);
    for (int i = 0; i <= split; i++) {
        float angle = 2 * M_PI / split * i;
        vertices.push_back(center + vec3(sin(angle) * width, cos(angle) * height, 0.0f));
        vertices.push_back(vec3(0.5 + sin(angle) * 0.5, 0.5 + cos(angle) * 0.5, 0.0f));
    }
    updateBuffer();
}
void Circle::setMode(DrawMode mode) {
    switch (mode) {
        case Filled:
            if (renderType == GL_TRIANGLE_FAN) return;
            renderType = GL_TRIANGLE_FAN;
            vertices.insert(vertices.begin(), vertices[0] - vec3(0.0, height, 0.0));
            vertices.insert(vertices.begin() + 1, vec3(0.5, 0.5, 0.0));
            break;
        case Outlined:
            if (renderType == GL_LINE_STRIP) return;
            renderType = GL_LINE_STRIP;
            vertices.erase(vertices.begin(), vertices.begin() + 2);
            break;
        default:
            break;
    }
    updateBuffer();
}
int Circle::isIn(vec3 point) {
    point -= renderType == GL_TRIANGLE_FAN ? vertices[0] : vertices[0] - vec3(0.0, height, 0.0);
    return length(point * vec3(1.0f / width, 1.0f / height, 1.0f)) < 1.0f;
}
