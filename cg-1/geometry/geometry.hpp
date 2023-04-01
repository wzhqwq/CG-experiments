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
        glGenBuffers(1, &texCoordBuffer);
    }
    ~Geometry() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &texCoordBuffer);
    }
    
    void paint();
    void setColor(vec3 color);
    virtual void setMode(DrawMode mode);
    virtual int isIn(vec3 point);
    virtual void onScale(float scaleX, float scaleY);

    void applyTransformation(mat4 matrix);
    void translate(float x, float y);
    void scale(float scaleX, float scaleY, float x, float y);
    void setZIndex(int index);
    int getZIndex();

    GLuint getVAO();
    
    GLuint texture = 0;
protected:
    void updateBuffer();
    
    GLuint VAO;
    GLuint vertexBuffer, texCoordBuffer;
    mat4 transformation = mat4(1.0f);
    vector<vec3> vertices;
    GLenum renderType = GL_TRIANGLES;
    vec3 currentColor;
    int currentZIndex = 0;
};

class RubberBandGeometry : public Geometry {
public:
    RubberBandGeometry(vec3 start) : startPoint(start) {};
    virtual void updateEnd(vec3 end);
protected:
    vec3 startPoint;
};

class Line : public RubberBandGeometry {
public:
    Line(vec3 start, vec3 end) : RubberBandGeometry(start) {
        renderType = GL_LINE_STRIP;
        vertices.resize(4);
        updateEnd(end);
    }
    
    void setMode(DrawMode mode);
    void updateEnd(vec3 end);
    int isIn(vec3 point);
};

class Triangle : public RubberBandGeometry {
public:
    Triangle(vec3 start, vec3 end) : RubberBandGeometry(start) {
        renderType = GL_LINE_LOOP;
        vertices.resize(6);
        updateEnd(end);
    }
    
    void updateEnd(vec3 end);
    int isIn(vec3 point);
};

class Rect : public RubberBandGeometry {
public:
    Rect() : Rect(vec3(-0.5f, -0.5f, 0.0f), vec3(0.5f, 0.5f, 0.0f)) {}
    Rect(float width, float height) : Rect(vec3(-0.5f * width, -0.5f * height, 0.0f), vec3(0.5f * width, 0.5f * height, 0.0f)) {}
    Rect(vec3 start, vec3 end) : RubberBandGeometry(start) {
        renderType = GL_LINE_LOOP;
        vertices.resize(8);
        updateEnd(end);
    }
    
    void setMode(DrawMode mode);
    void updateEnd(vec3 end);
    int isIn(vec3 point);
};

class Circle : public RubberBandGeometry {
public:
    Circle() : Circle(vec3(-0.5f, -0.5f, 0.0f), vec3(0.5f, 0.5f, 0.0f)) {}
    Circle(vec3 start, vec3 end) : RubberBandGeometry(start) {
        renderType = GL_LINE_STRIP;
        updateEnd(end);
    }
    
    void setMode(DrawMode mode);
    void updateEnd(vec3 end);
    int isIn(vec3 point);
    void onScale(float scaleX, float scaleY);
private:
    float width, height;
};

#endif /* geometry_hpp */
