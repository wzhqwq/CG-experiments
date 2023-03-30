//
//  geometry.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "geometry.hpp"

void Geometry::paint() {
    glBindVertexArray(VAO);
    
    glVertexAttrib3fv(1, &currentColor[0]);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
    glDrawArrays(renderType, 0, (int) vertices.size());
    glDisableVertexAttribArray(0);
    
    glBindVertexArray(0);
}

void Geometry::setColor(vec3 color) {
    currentColor = color;
}

void Geometry::setMode(DrawMode mode) {
    switch (mode) {
        case Filled:
            renderType = GL_TRIANGLE_STRIP;
            break;
        case Outlined:
            renderType = GL_LINE_LOOP;
            break;
        default:
            break;
    }
}

void Geometry::updateBuffer() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
    glBindVertexArray(0);
}

void Geometry::applyTransformation(mat4 matrix) {
    for (int i = 0; i < vertices.size(); i++) {
        vertices[i] = vec3(matrix * vec4(vertices[i], 1.0f));
    }
    updateBuffer();
}

void Geometry::translate(float x, float y) {
    applyTransformation(glm::translate(mat4(1.0f), vec3(x, y, 0)));
}
void Geometry::setZIndex(int index) {
    applyTransformation(glm::translate(mat4(1.0f), vec3(0, 0, index - currentZIndex)));
    currentZIndex = index;
}
int Geometry::getZIndex() {
    return currentZIndex;
}
int Geometry::isIn(vec3 point) {
    return 0;
}

GLuint Geometry::getVAO() {
    return VAO;
}

void RubberBandGeometry::updateEnd(vec3 end) {}
