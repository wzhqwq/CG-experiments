//
//  common.h
//  cg-1
//
//  Created by 王子涵 on 2023/3/21.
//

#ifndef common_h
#define common_h

#include <cstdio>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WIDTH 1000
#define HEIGHT 800
#define PICKER_SIZE 300
#define BTN_SIZE 32
#define BTN_GAP 8

inline int max(const int& a, const int& b) {
    return a > b ? a : b;
}
inline int min(const int& a, const int& b) {
    return a < b ? a : b;
}

using namespace glm;

#endif /* common_h */
