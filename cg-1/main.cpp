//
//  main.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/13.
//

#define TEST_BOUNDING

#include "common.h"
#include "shaderReader.hpp"
#include "scene.hpp"
#include "tools.hpp"

using namespace glm;

GLuint shapeProgram;
GLuint toolProgram;
// HSL Picker
GLuint satureLightPickerProgram;
GLuint huePickerProgram;

GLuint shapeMVPLocation;

Scene *mainScene;
DragTool *currentTool = NULL;

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(shapeProgram);
    if (mainScene->isChanged()) {
        glUniformMatrix4fv(shapeMVPLocation, 1, GL_FALSE, &mainScene->getVPMatrix()[0][0]);
    }
    for (auto geo : mainScene->shapes) {
        geo->paint();
    }
}

void loadShaders(char *shaderDir) {
    if (shaderDir[strlen(shaderDir) - 1] == '/') {
        shaderDir[strlen(shaderDir) - 1] = '\0';
    }
    shapeProgram = glCreateProgram();
    
    loadVertexShader(shaderDir, "shape.vert", shapeProgram);
    loadFragmentShader(shaderDir, "shape.frag", shapeProgram);
    
    glLinkProgram(shapeProgram);

    char log[1000];
    int logLength;
    glGetProgramInfoLog(shapeProgram, 1000, &logLength, log);
    if (logLength) {
        log[logLength] = '\0';
        printf("program linking error:\n%s\n", log);
    }
    
    shapeMVPLocation = glGetUniformLocation(shapeProgram, "MVP");
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    currentTool->mouseMove(xpos, ypos, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT), glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT));
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_H:
                currentTool = tools.hand;
                glfwSetCursor(window, cursors.hand);
                break;
            case GLFW_KEY_V:
                currentTool = tools.manipulate;
                glfwSetCursor(window, NULL);
                break;
            case GLFW_KEY_L:
                currentTool = tools.line;
                glfwSetCursor(window, cursors.cross);
                break;
            case GLFW_KEY_T:
                currentTool = tools.triangle;
                glfwSetCursor(window, cursors.cross);
                break;
            case GLFW_KEY_P:
                glfwSetCursor(window, cursors.cross);
                break;
            default:
                break;
        }
        if (!mods) {
            currentTool->setKeyMods(0);
        }
    }
    if (action == GLFW_PRESS) {
        if (mods) {
            currentTool->setKeyMods(mods);
        }
    }
}

void scrollBallback(GLFWwindow *window, double offsetX, double offsetY) {
    mainScene->moveTo(mainScene->getPos().x - offsetX, mainScene->getPos().y + offsetY);
}

int main(int argc, char * argv[]) {
#ifdef TEST_BOUNDING
    printf("Bounding test enabled\n");
#endif
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
        printf("Window Creation Failed.\n");
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        printf("GLEW Initialization Failed.\n");
        return -1;
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    mainScene = new Scene(0, 0, 1000, 800);
    initTools(mainScene);
    currentTool = tools.manipulate;
    loadShaders(argv[1]);

    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scrollBallback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        render();
        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}
