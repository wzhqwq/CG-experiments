//
//  main.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/13.
//

#include "common.h"
#include "shaderReader.hpp"
#include "geometryHelper.hpp"

GLuint defaultProgram;
Geometry testTriagle;

GLfloat vertices[] = {
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
};
GLfloat color[] = {
    1.0f, 1.0f, 0.0f,
};

void render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(defaultProgram);
    paint(testTriagle);
//    printf("paint\n");

    glutSwapBuffers();
}

void loadShaders(char *shaderDir) {
    if (shaderDir[strlen(shaderDir) - 1] == '/') {
        shaderDir[strlen(shaderDir) - 1] = '\0';
    }
    defaultProgram = glCreateProgram();
    
    loadVertexShader(shaderDir, "test.vert", defaultProgram);
    loadFragmentShader(shaderDir, "test.frag", defaultProgram);
    
    glLinkProgram(defaultProgram);
    
    char log[1000];
    int logLength;
    glGetProgramInfoLog(defaultProgram, 1000, &logLength, log);
    if (logLength) {
        log[logLength] = '\0';
        printf("program linking error:\n%s\n", log);
    }
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_3_2_CORE_PROFILE);
    
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(40, 80);
    glutCreateWindow("test");

    glewInit();
    loadShaders(argv[1]);
    testTriagle = getBufferedGeometry(vertices, 9, color);
    
    glutDisplayFunc(render);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutMainLoop();

    return 0;
}
