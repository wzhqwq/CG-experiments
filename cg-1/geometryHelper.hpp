//
//  geometryHelper.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/20.
//

#ifndef geometryHelper_hpp
#define geometryHelper_hpp

#include "common.h"

struct Geometry {
    GLuint VAO;
    GLuint VBO;
    GLuint size;
};

Geometry getBufferedGeometry(GLfloat *data, GLuint len, GLfloat *color);
void updateVertexArray(GLfloat *data, GLuint len, Geometry *geo);
void disposeBuffer(Geometry geo);
void paint(Geometry geo);

#endif /* geometryHelper_hpp */
