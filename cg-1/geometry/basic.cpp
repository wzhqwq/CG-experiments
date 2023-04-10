//
//  triangle.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#include "geometry.hpp"

void Line::updateEnd(vec3 end) {
    vertices[0] = startPoint;
    vertices[1] = vec3(0.0, 0.0, currentZIndex);
    vertices[2] = end;
    vertices[3] = vec3(1.0, 1.0, currentZIndex);
    updateBuffer();
}
void Line::setMode(DrawMode mode) {}
int Line::isIn(vec3 point) {
    float a = (vertices[0].y - vertices[2].y) / (vertices[0].x - vertices[2].x);
    float b = -1, c = vertices[0].y - a * vertices[0].x;
    float d = fabs((a * point.x + b * point.y + c) / length(vec2(a, b)));
    vec3 v1 = getBottomLeft() - vec3(10.0, 10.0, 0.0), v2 = getTopRight() + vec3(10.0, 10.0, 0.0);
    return v1.x < point.x && point.x < v2.x && v1.y < point.y && point.y < v2.y && d < 10.0f;
}
vec3 Line::getCenter() { return (vertices[0] + vertices[2]) * 0.5f; }
vec3 Line::getBottomLeft() { return min(vertices[0], vertices[2]); }
vec3 Line::getTopRight() { return max(vertices[0], vertices[2]); }

void Triangle::updateEnd(vec3 end) {
    vertices[0] = vec3((startPoint.x + end.x) / 2, startPoint.y, currentZIndex);
    vertices[1] = vec3(0.5, 0.0, 0.0);
    vertices[2] = vec3(startPoint.x, end.y, currentZIndex);
    vertices[3] = vec3(0.0, 1.0, 0.0);
    vertices[4] = vec3(end.x, end.y, currentZIndex);
    vertices[5] = vec3(1.0, 1.0, 0.0);
    updateBuffer();
}
int Triangle::isIn(vec3 point) {
    point.z = vertices[0].z;
    int flipX = vertices[2].x > vertices[4].x, flipY = vertices[2].y > vertices[0].y;
    vec3 a = vertices[0];
    vec3 b = flipX ^ flipY ? vertices[4] : vertices[2];
    vec3 c = flipX ^ flipY ? vertices[2] : vertices[4];
    return (cross(b - a, point - a).z > 0 &&
            cross(c - b, point - b).z > 0 &&
            cross(a - c, point - c).z > 0);
}
vec3 Triangle::getCenter() { return (vertices[0] + (vertices[2] + vertices[4]) * 0.5f) * 0.5f; }
vec3 Triangle::getBottomLeft() { return vec3(fmin(vertices[2].x, vertices[4].x), fmin(vertices[0].y, vertices[2].y), vertices[0].z); }
vec3 Triangle::getTopRight() { return vec3(fmax(vertices[2].x, vertices[4].x), fmax(vertices[0].y, vertices[2].y), vertices[0].z); }

void Rect::updateEnd(vec3 end) {
    vertices[0] = vec3(startPoint.x, startPoint.y, currentZIndex);
    vertices[1] = vec3(0.0, 0.0, 0.0);
    vertices[2] = vec3(startPoint.x, end.y, currentZIndex);
    vertices[3] = vec3(0.0, 1.0, 0.0);
    vertices[4] = vec3(end.x, end.y, currentZIndex);
    vertices[5] = vec3(1.0, 1.0, 0.0);
    vertices[6] = vec3(end.x, startPoint.y, currentZIndex);
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
    vec3 v1 = getBottomLeft(), v2 = getTopRight();
    return v1.x < point.x && point.x < v2.x && v1.y < point.y && point.y < v2.y;
}
vec3 Rect::getCenter() { return (vertices[0] + vertices[4]) * 0.5f; }
vec3 Rect::getBottomLeft() { return min(vertices[0], vertices[4]); }
vec3 Rect::getTopRight() { return max(vertices[0], vertices[4]); }

void Circle::updateEnd(vec3 end) {
    vertices.clear();
    vec3 center = (startPoint + end) * 0.5f;
    width = abs(startPoint.x - end.x) / 2;
    height = abs(startPoint.y - end.y) / 2;
    
    if (renderType == GL_TRIANGLE_FAN) {
        vertices.push_back(vec3(center.x, center.y, currentZIndex));
        vertices.push_back(vec3(0.5, 0.5, 0.0));
    }
    int split = max(20, width * M_PI / 10);
    for (int i = 0; i <= split; i++) {
        float angle = 2 * M_PI / split * i;
        vertices.push_back(center + vec3(sin(angle) * width, cos(angle) * height, currentZIndex));
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
    point -= getCenter();
    return length(vec2(point) * vec2(1.0f / width, 1.0f / height)) < 1.0f;
}
void Circle::onScale(float scaleX, float scaleY) {
    width *= scaleX;
    height *= scaleY;
}
vec3 Circle::getCenter() {
    return renderType == GL_TRIANGLE_FAN ? vertices[0] : vertices[0] - vec3(0.0, height, 0.0);
}
vec3 Circle::getBottomLeft() { return getCenter() - vec3(width, height, 0.0); }
vec3 Circle::getTopRight() { return getCenter() + vec3(width, height, 0.0); }
