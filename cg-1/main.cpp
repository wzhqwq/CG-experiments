//
//  main.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/13.
//

#include "common.h"
#include "shaderReader.hpp"
#include "geometryHelper.hpp"
#include "scene.hpp"

using namespace glm;

GLuint defaultProgram;
GLuint defaultProgramMVPLocation;
Geometry testTriagle;
Scene *mainScene;

GLfloat vertices[] = {
    50.0f, -50.0f, 0.0f,
    -50.0f, -50.0f, 0.0f,
    0.0f, 50.0f, 0.0f,
};
GLfloat color[] = {
    1.0f, 1.0f, 0.0f,
};

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(defaultProgram);
    if (mainScene->isChanged()) {
        glUniformMatrix4fv(defaultProgramMVPLocation, 1, GL_FALSE, &mainScene->getMVPMatrix()[0][0]);
    }

    paint(testTriagle);
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
    
    defaultProgramMVPLocation = glGetUniformLocation(defaultProgram, "MVP");
}

void mouseCallBack(GLFWwindow *window, double xpos, double ypos) {
    static double lastX, lastY;
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        mainScene->move(xpos - lastX, ypos - lastY);
    }
    
    lastX = xpos;
    lastY = ypos;
}

int main(int argc, char * argv[]) {
    if (!glfwInit()) {
        printf("GLFW Initialization Failed.\n");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(1000, 800, "experiment 1", NULL, NULL);
    if (!window) {
        printf("Window Initialization Failed.\n");
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        printf("GLEW Initialization Failed.\n");
        return -1;
    }
    //    glEnable(GL_DEBUG_OUTPUT);
    //    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    mainScene = new Scene(0, 0, 1000, 800);
    loadShaders(argv[1]);
    testTriagle = getBufferedGeometry(vertices, 9, color);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetCursorPosCallback(window, mouseCallBack);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        render();
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}
