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
    vec3 pos = fixedScene->rayCast(x, -y);
    if (pos.x > BTN_GAP && pos.x < BTN_SIZE + BTN_GAP) {
        return clicked((int) ((pos.y - BTN_GAP) / (BTN_SIZE + BTN_GAP)));
    }
    return 0;
}

void SideBar::create() {
    createBtn()->texture = textures.hand;
    createBtn()->texture = textures.pointer;
    createBtn()->texture = textures.line;
    createBtn()->texture = textures.triangle;
    createBtn()->texture = textures.rect;
    createBtn()->texture = textures.circle;
    createBtn()->texture = textures.pen;
    pickerBtn = createBtn();
    pickerBtn->texture = textures.colors;
    
    switched(0);
}

Rect* SideBar::createBtn() {
    Rect *result = new Rect(vec3(BTN_GAP, BTN_GAP + (BTN_SIZE + BTN_GAP) * buttons.size(), 500),
                            vec3(BTN_GAP + BTN_SIZE, (BTN_GAP + BTN_SIZE) * (buttons.size() + 1), 500));
    result->setMode(Filled);
    result->setColor(vec3(0.6, 0.6, 0.6));
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
            switchTool(RECT);
            break;
        case 5:
            switchTool(CIRCLE);
            break;
        case 6:
            switchTool(PEN);
            break;
        case 7:
            picker->open();
            return 0;
            
        default:
            return 0;
    }
    switched(id);
    return 1;
}

void SideBar::switched(int id) {
    if (id == selected) return;
    if (selected != -1) buttons[selected]->setColor(vec3(0.6, 0.6, 0.6));
    buttons[id]->setColor(vec3(0.4, 0.6, 1.0));
    selected = id;
}
