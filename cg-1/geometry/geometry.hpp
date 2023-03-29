//
//  geometry.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#ifndef geometry_hpp
#define geometry_hpp

#include "common.h"
#include <vector>
#include <cmath>

using namespace std;

enum DrawMode {
    Filled, Outlined
};

class Geometry {
public:
    Geometry() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &transformBuffer);
    }
    ~Geometry() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &vertexBuffer);
    }
    
    void paint();
    void setColor(vec3 color);
    virtual void setMode(DrawMode mode);
    
    void applyTransformation(mat4 matrix);
    void translate(float x, float y);
    void setZIndex(float index);
    
    GLuint getVAO();
protected:
    void updateBuffer();
    
    GLuint VAO;
    GLuint vertexBuffer, transformBuffer;
    mat4 transformation = mat4(1.0f);
    vector<vec3> vertices;
    GLenum renderType = GL_TRIANGLES;
    vec3 currentColor;
    float currentZIndex = 0.0f;
};

class RubberBandGeometry : public Geometry {
public:
    virtual void updateEnd(vec3 end);
};

class Line : public RubberBandGeometry {
public:
    Line(vec3 start, vec3 end) : RubberBandGeometry() {
        vertices.push_back(start);
        vertices.push_back(end);
        updateBuffer();
        renderType = GL_LINE_STRIP;
    }
    
    void setMode(DrawMode mode);
    void updateEnd(vec3 end);
};

class Triangle : public RubberBandGeometry {
public:
    Triangle(vec3 start, vec3 end) : RubberBandGeometry(), startPoint(start) {
        vertices.push_back(vec3((start.x + end.x) / 2, start.y, 0));
        vertices.push_back(vec3(start.x, end.y, 0));
        vertices.push_back(vec3(end.x, end.y, 0));
        updateBuffer();
        renderType = GL_LINE_LOOP;
    }
    
    void updateEnd(vec3 end);
private:
    vec3 startPoint;
};

class Rect : public RubberBandGeometry {
public:
    Rect() : Rect(vec3(-0.5f, -0.5f, 0.0f), vec3(0.5f, 0.5f, 0.0f)) {}
    Rect(float width, float height) : Rect(vec3(-0.5f * width, -0.5f * height, 0.0f), vec3(0.5f * width, 0.5f * height, 0.0f)) {}
    Rect(vec3 start, vec3 end) : RubberBandGeometry(), startPoint(start) {
        vertices.push_back(start);
        vertices.push_back(vec3(start.x, end.y, 0.0f));
        vertices.push_back(end);
        vertices.push_back(vec3(end.x, start.y, 0.0f));
        vertices.push_back(start);
        updateBuffer();
        renderType = GL_LINE_LOOP;
    }
    
    void setMode(DrawMode mode);
    void updateEnd(vec3 end);
private:
    vec3 startPoint;
};

class Circle : public RubberBandGeometry {
public:
    Circle() : Circle(vec3(-0.5f, -0.5f, 0.0f), vec3(0.5f, 0.5f, 0.0f)) {}
    Circle(vec3 start, vec3 end) : RubberBandGeometry(), startPoint(start) {
        vec3 center = (start + end) * 0.5f;
        float width = abs(start.x - end.x);
        float height = abs(start.y - end.y);
        vertices.push_back(center);
        int split = width * M_PI / 4;
        for (int i = 0; i < split; i++) {
            float angle = 2 * M_PI / split * i;
            vertices.push_back(vec3(sin(angle) * width / 2, cos(angle) * height / 2, 0.0f));
        }
        updateBuffer();
        renderType = GL_LINE_LOOP;
    }
    
    void setMode(DrawMode mode);
    void updateEnd(vec3 end);
private:
    vec3 startPoint;
};

#endif /* geometry_hpp */
