//
//  shader.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/27.
//

#include "shader.hpp"

Programs programs;

GLuint loadProgram(const char *shaderDir, const char *vert, const char *frag) {
    GLuint program = glCreateProgram();
    loadVertexShader(shaderDir, vert, program);
    loadFragmentShader(shaderDir, frag, program);
    glLinkProgram(program);
    
    char log[1000];
    int logLength;
    glGetProgramInfoLog(program, 1000, &logLength, log);
    if (logLength) {
        log[logLength] = '\0';
        printf("program linking error:\n%s\n", log);
    }
    
    return program;
}

void initPrograms(const char *shaderDir) {
    programs.shapeProgram = loadProgram(shaderDir, "shape.vert", "shape.frag");
    programs.fixedProgram = loadProgram(shaderDir, "shape.vert", "shape.frag");
    programs.pickerProgram = loadProgram(shaderDir, "colorPicker.vert", "colorPicker.frag");
}
