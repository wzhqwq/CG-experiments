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

using namespace std;

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
    void setFillColor(vec3 color);
    void applyTransformation(mat4 matrix);
    void translate(float x, float y);
    void setZIndex(float index);
protected:
    void updateBuffer();
    void updateTransformation();
    
    GLuint VAO;
    GLuint vertexBuffer, transformBuffer;
    mat4 transformation = mat4(1.0f);
    vector<vec3> vertices;
    GLenum renderType = GL_TRIANGLES;
};

class RubberBandGeometry : public Geometry {
public:
    virtual void updateEnd(vec3 end);
};

class Line : public RubberBandGeometry {
public:
    Line(vec3 color, vec3 start, vec3 end) : RubberBandGeometry() {
        vertices.push_back(start);
        vertices.push_back(end);
        setFillColor(color);
        updateBuffer();
        renderType = GL_LINE_STRIP;
    }
    
    void updateEnd(vec3 end);
};

class Triangle : public RubberBandGeometry {
public:
    Triangle(vec3 color, vec3 start, vec3 end) : RubberBandGeometry(), startPoint(start) {
        vertices.push_back(vec3((start.x + end.x) / 2, start.y, 0));
        vertices.push_back(vec3(start.x, end.y, 0));
        vertices.push_back(vec3(end.x, end.y, 0));
        setFillColor(color);
        updateBuffer();
        renderType = GL_LINE_LOOP;
    }
    
    void updateEnd(vec3 end);
private:
    vec3 startPoint;
};

#endif /* geometry_hpp */
