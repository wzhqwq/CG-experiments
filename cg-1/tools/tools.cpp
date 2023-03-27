//
//  tools.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/24.
//

#include "tools.hpp"

Tools tools;
Cursors cursors;

void initTools(Scene *scene) {
    tools.manipulate = new ManipulateTool(scene);
    tools.hand = new HandTool(scene);
    tools.line = new LineCreator(scene);
    tools.triangle = new TriangleCreator(scene);
}

void initCursors() {
    cursors.hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    cursors.cross = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
}
