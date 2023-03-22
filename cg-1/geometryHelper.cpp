//
//  geometryHelper.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/20.
//

#include "geometryHelper.hpp"

Geometry getBufferedGeometry(GLfloat *data, GLuint len, GLfloat *color) {
    GLuint VAO, VBO;
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, len * sizeof(GLfloat), data, GL_STATIC_DRAW);
    
    glVertexAttrib3fv(1, color);
    
    glBindVertexArray(0);

    return { VAO, VBO, len / 3 };
}

void updateVertexArray(GLfloat *data, GLuint len, Geometry *geo) {
    glBindVertexArray(geo->VAO);
    
    GLuint oldVBO = geo->VBO;
    glGenBuffers(1, &geo->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, geo->VBO);
    glBufferData(GL_ARRAY_BUFFER, len * sizeof(GLfloat), data, GL_STATIC_DRAW);
    
    glBindVertexArray(0);
    geo->size = len / 3;

    glDeleteBuffers(1, &oldVBO);
}

void disposeBuffer(Geometry geo) {
    glDeleteVertexArrays(1, &geo.VAO);
    glDeleteBuffers(1, &geo.VBO);
}

void paint(Geometry geo) {
    glBindVertexArray(geo.VAO);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, geo.VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *) 0);
    glDrawArrays(GL_TRIANGLES, 0, geo.size);
    glDisableVertexAttribArray(0);
    
    glBindVertexArray(0);
}
