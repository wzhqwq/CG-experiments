//
//  main.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/13.
//

//#define TEST_BOUNDING

#include "common.h"
#include "shader.hpp"
#include "scene.hpp"
#include "tools.hpp"
#include "colorPicker.hpp"
#include "sideBar.hpp"
#include "texture.hpp"

using namespace glm;

GLuint shapeMVPLocation, colorPickerMVPLocation;

Scene *mainScene, *fixedScene;
DragTool *currentTool = NULL;
ColorPicker *picker;
SideBar *sideBar;

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (mainScene->isChanged()) {
        glUseProgram(programs.shapeProgram);
        glUniformMatrix4fv(shapeMVPLocation, 1, GL_FALSE, &mainScene->getVPMatrix()[0][0]);
    }
    glUseProgram(programs.shapeProgram);
    mainScene->render(GL_RENDER);
    if (mainScene->selectionRect && mainScene->selectedItem) {
        mainScene->selectionRect->drawSelf();
    }
    
    picker->paint();
    sideBar->paint();
}

void loadShaders(char *shaderDir) {
    if (shaderDir[strlen(shaderDir) - 1] == '/') {
        shaderDir[strlen(shaderDir) - 1] = '\0';
    }
    initPrograms(shaderDir);
    
    shapeMVPLocation = glGetUniformLocation(programs.shapeProgram, "MVP");
    colorPickerMVPLocation = glGetUniformLocation(programs.pickerProgram, "MVP");
    
    glUseProgram(programs.fixedProgram);
    mat4 flippedMVP = scale(fixedScene->getVPMatrix(), vec3(1.0f, -1.0f, 1.0f));
    glUniformMatrix4fv(shapeMVPLocation, 1, GL_FALSE, &flippedMVP[0][0]);
    glUseProgram(programs.pickerProgram);
    glUniformMatrix4fv(colorPickerMVPLocation, 1, GL_FALSE, &flippedMVP[0][0]);
}

void mouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {
    int left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (picker->mouseMove(xpos, ypos, left, right)) return;
    currentTool->mouseMove(xpos, ypos, left, right);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    currentTool->setKeyMods(mods);
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    if (picker->mouseMove(x, y, button == GLFW_MOUSE_BUTTON_LEFT ? action : GLFW_RELEASE, button == GLFW_MOUSE_BUTTON_RIGHT ? action : GLFW_RELEASE)) return;
    if (sideBar->mouseMove(x, y, action)) return;
    currentTool->mouseMove(x, y, button == GLFW_MOUSE_BUTTON_LEFT ? action : GLFW_RELEASE, button == GLFW_MOUSE_BUTTON_RIGHT ? action : GLFW_RELEASE);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_H:
                switchTool(HAND);
                sideBar->switched(0);
                break;
            case GLFW_KEY_V:
                switchTool(MANIPULATE);
                sideBar->switched(1);
                break;
            case GLFW_KEY_L:
                switchTool(LINE);
                sideBar->switched(2);
                break;
            case GLFW_KEY_T:
                switchTool(TRIANGLE);
                sideBar->switched(3);
                break;
            case GLFW_KEY_R:
                switchTool(RECT);
                sideBar->switched(4);
                break;
            case GLFW_KEY_C:
                switchTool(CIRCLE);
                sideBar->switched(5);
                break;
            case GLFW_KEY_P:
                switchTool(PEN);
                sideBar->switched(6);
                break;
            case GLFW_KEY_SLASH:
                if (mainScene->selectedItem) {
                    mainScene->selectedItem->setMode(Outlined);
                }
                else {
                    mainScene->currentDrawMode = Outlined;
                }
                break;
            case GLFW_KEY_PERIOD:
                if (mainScene->selectedItem) {
                    mainScene->selectedItem->setMode(Filled);
                }
                else {
                    mainScene->currentDrawMode = Filled;
                }
                break;
            case GLFW_KEY_Z:
                if (mods & GLFW_MOD_SUPER) {
                    popOp();
                }
                break;
            case GLFW_KEY_BACKSPACE:
                if (mainScene->selectedItem) {
                    for (auto i = mainScene->shapes.begin(); i < mainScene->shapes.end(); i++) {
                        if (*i == mainScene->selectedItem) {
                            pushOp(new DeletionOp((int) (i - mainScene->shapes.begin()), *i));
                            mainScene->shapes.erase(i);
                            mainScene->selectedItem = NULL;
                            break;
                        }
                    }
                }
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
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "experiment 1", NULL, NULL);
    if (!window) {
        printf("Window Creation Failed.\n");
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (glewInit() != GLEW_OK) {
        printf("GLEW Initialization Failed.\n");
        return -1;
    }
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_MULTISAMPLE);

    mainScene = new Scene(WIDTH, HEIGHT);
    fixedScene = new Scene(WIDTH, HEIGHT);
    fixedScene->moveTo(WIDTH / 2, -HEIGHT / 2);
    loadShaders(argv[1]);
    initTexture(argv[2]);
    
    initTools();
    picker = new ColorPicker();
    sideBar = new SideBar();

    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
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
