//
//  sideBar.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/29.
//

#include "sideBar.hpp"

void SideBar::paint() {
    glUseProgram(programs.fixedProgram);
    pickerBtn->setColor(mainScene->currentColor);
    for (auto btn : buttons) {
        btn->paint();
    }
}

int SideBar::mouseMove(float x, float y, int button) {
    if (button != GLFW_PRESS) return 0;
    vec3 pos = fixedScene->rayCast(x, y);
    if (x > BTN_GAP && x < BTN_SIZE + BTN_GAP) {
        return clicked((int) (y / (BTN_SIZE + BTN_GAP)));
    }
    return 0;
}

void SideBar::create() {
    createBtn();
    createBtn();
    createBtn();
    createBtn();
    createBtn();
    pickerBtn = createBtn();
}

Rect* SideBar::createBtn() {
    Rect *result = new Rect(vec3(BTN_GAP, BTN_GAP + (BTN_SIZE + BTN_GAP) * buttons.size(), 500),
                            vec3(BTN_GAP + BTN_SIZE, (BTN_GAP + BTN_SIZE) * (buttons.size() + 1), 500));
    result->setMode(Filled);
    buttons.push_back(result);
    return result;
}

int SideBar::clicked(int id) {
    switch (id) {
        case 0:
            switchTool(HAND);
            break;
        case 1:
            switchTool(MANIPULATE);
            break;
        case 2:
            switchTool(LINE);
            break;
        case 3:
            switchTool(TRIANGLE);
            break;
        case 4:
            switchTool(PEN);
            break;
        case 5:
            picker->open();
            break;
            
        default:
            return 0;
    }
    return 1;
}
