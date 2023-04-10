//
//  colorPicker.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/27.
//

#include "colorPicker.hpp"

vec3 hsv_to_rgb(float h, float s, float v) {
    float c = v * s;
    h *= 6;
    float x = c * (1.0f - abs(mod(h, 2.0f) - 1.0f));
    vec3 result;
    if (0.0f <= h && h < 1.0f) {
        result = vec3(c, x, 0.0f);
    } else if (1.0f <= h && h < 2.0f) {
        result = vec3(x, c, 0.0f);
    } else if (2.0f <= h && h < 3.0f) {
        result = vec3(0.0f, c, x);
    } else if (3.0f <= h && h < 4.0f) {
        result = vec3(0.0f, x, c);
    } else if (4.0f <= h && h < 5.0f) {
        result = vec3(x, 0.0f, c);
    } else if (5.0f <= h && h < 6.0f) {
        result = vec3(c, 0.0f, x);
    } else {
        result = vec3(0.0f, 0.0f, 0.0f);
    }
    result += vec3(v - c);
    return result;
}


void ColorPicker::paint() {
    if (!opened) return;
    glUseProgram(programs.pickerProgram);

    GLuint hsbLocation = glGetUniformLocation(programs.pickerProgram, "hsv");
    glUniform3f(hsbLocation, hue, saturate, brightness);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    pickerBox->paint();
    glDisable(GL_BLEND);
    
    glUseProgram(programs.fixedProgram);
    for (auto btn : colorBlocks) btn->paint();
}

int ColorPicker::mouseMove(float x, float y, int left, int right) {
    if (!opened) return 0;
    if ((left | right) == GLFW_RELEASE) {
        if (status != Idle) status = Idle;
        return 1;
    }
    
    vec3 castPos = fixedScene->toWorldPos(x, -y) - vec3(selfX, selfY, 0.0);
    vec2 inPos = vec2(castPos) * (1.0f / PICKER_SIZE) - vec2(0.5);
    inPos.y = -inPos.y;
        
    if (status == Idle) {
        float d = length(inPos);
        if (abs(inPos.x) < 0.3 && abs(inPos.y) < 0.3) {
            status = InRect;
        }
        else if (d > 0.44 && d < 0.5) {
            status = InRing;
        }
        else if (0 < castPos.x &&
                 castPos.x < PICKER_SIZE &&
                 PICKER_SIZE < castPos.y &&
                 castPos.y < PICKER_SIZE + PICKER_COLOR_BLOCK_SIZE * 10) {
            int row = (castPos.y - PICKER_SIZE) / PICKER_COLOR_BLOCK_SIZE;
            int col = castPos.x / PICKER_COLOR_BLOCK_SIZE;
            int index = row * LINE_COUNT + col;
            if (index >= colorBlocks.size()) {
                close();
                return 1;
            }
            if (left) {
                if (index == colorBlocks.size() - 1) return 1;
                pickColor(index);
            }
            if (right) {
                if (index == colorBlocks.size() - 1) addColorBlock();
                registerColor(index);
            }
        }
        else {
            close();
            return 1;
        }
    }
    
    if (status == InRing) {
        hue = atan2(inPos.x, inPos.y) / M_PI / 2;
        if (hue < 0) hue += 1.0;
    }
    if (status == InRect) {
        saturate = fmax(0.0f, fmin(1.0f, inPos.x / 0.6 + 0.5));
        brightness = fmax(0.0f, fmin(1.0f, inPos.y / 0.6 + 0.5));
    }
    setColor();
    
    return 1;
}

void ColorPicker::open() {
    opened = 1;
    if (mainScene->selectedItem) {
        lastColor = mainScene->selectedItem->currentColor;
    }
}

void ColorPicker::close() {
    opened = 0;
    if (mainScene->selectedItem) pushOp(new ColoringOp(lastColor, mainScene->selectedItem));
}

void ColorPicker::addColorBlock() {
    int row = (int) colorBlocks.size() / LINE_COUNT;
    int col = (int) colorBlocks.size() % LINE_COUNT;
    Rect *block = new Rect(vec3(selfX + col * PICKER_COLOR_BLOCK_SIZE, selfY + PICKER_SIZE + row * PICKER_COLOR_BLOCK_SIZE, 990.0),
                           vec3(selfX + (col + 1) * PICKER_COLOR_BLOCK_SIZE, selfY + PICKER_SIZE + (row + 1) * PICKER_COLOR_BLOCK_SIZE, 990.0));
    block->currentColor = vec3(0.0, 0.0, 0.0);
    block->setMode(Outlined);
    colorBlocks.push_back(block);
    savedColors.push_back(vec3(0.0, 0.0, 0.0));
}

void ColorPicker::registerColor(int index) {
    Rect *block = colorBlocks[index];
    block->setMode(Filled);
    block->currentColor = hsv_to_rgb(hue, saturate, brightness);
    savedColors[index] = vec3(hue, saturate, brightness);
}

void ColorPicker::pickColor(int index) {
    vec3 hsv = savedColors[index];
    hue = hsv.x;
    saturate = hsv.y;
    brightness = hsv.z;
    setColor();
}
void ColorPicker::setColor() {
    vec3 color = hsv_to_rgb(hue, saturate, brightness);
    if (mainScene->selectedItem) {
        mainScene->selectedItem->currentColor = color;
    }
    else {
        mainScene->currentColor = color;
    }
}
