//
//  geometry.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "geometry.hpp"

void Geometry::paint() {
    glBindVertexArray(VAO);
    
//    glEnableVertexAttribArray(1);
//    glEnableVertexAttribArray(2);
//    glEnableVertexAttribArray(3);
//    glEnableVertexAttribArray(4);
//    glBindBuffer(GL_SHADER_STORAGE_BUFFER, transformBuffer);
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
//    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (4 * sizeof(GL_FLOAT)));
//    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (8 * sizeof(GL_FLOAT)));
//    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (12 * sizeof(GL_FLOAT)));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
    glDrawArrays(renderType, 0, (int) vertices.size());
    glDisableVertexAttribArray(0);
    
    glBindVertexArray(0);
}

void Geometry::setFillColor(vec3 color) {
    glBindVertexArray(VAO);
    glVertexAttrib3fv(1, &color[0]);
    glBindVertexArray(0);
}

void Geometry::updateBuffer() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(GLfloat), &vertices[0], GL_STREAM_DRAW);
    glBindVertexArray(0);
}

void Geometry::updateTransformation() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, transformBuffer);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 16 * sizeof(GLfloat), &transformation[0][0], GL_STREAM_DRAW);
    glBindVertexArray(0);
}

void Geometry::applyTransformation(mat4 matrix) {
    transformation *= matrix;
}

void RubberBandGeometry::updateEnd(vec3 end) {}
