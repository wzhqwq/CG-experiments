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

    glBindVertexArray(pickerBox->getVAO());
    glVertexAttrib1f(2, PICKER_SIZE);
    glVertexAttrib2f(3, -(PICKER_SIZE / 2 + BTN_SIZE + BTN_GAP * 2), -(PICKER_SIZE / 2 + BTN_GAP));
    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    pickerBox->paint();
    glDisable(GL_BLEND);
}

int ColorPicker::mouseMove(float x, float y, int button) {
    if (!opened) return 0;
    if (button == GLFW_RELEASE) {
        if (status != Idle) status = Idle;
        return 1;
    }
    
    vec2 inPos = vec2(fixedScene->rayCast(x, -y));
    inPos.x = (inPos.x - (PICKER_SIZE / 2 + BTN_SIZE + BTN_GAP * 2)) / PICKER_SIZE;
    inPos.y = -(inPos.y - (PICKER_SIZE / 2 + BTN_GAP)) / PICKER_SIZE;
        
    if (status == Idle) {
        float d = length(inPos);        
        if (abs(inPos.x) < 0.3 && abs(inPos.y) < 0.3) {
            status = InRect;
        }
        else if (d > 0.44 && d < 0.5) {
            status = InRing;
        }
        else {
            close();
            return 1;
        }
    }
    if (status == InRing) {
        hue = atan2(inPos.x, inPos.y) / M_PI / 2;
        if (hue < 0) hue += 1.0;
        mainScene->currentColor = hsv_to_rgb(hue, saturate, brightness);
    }
    if (status == InRect) {
        saturate = fmax(0.0f, fmin(1.0f, inPos.x / 0.6 + 0.5));
        brightness = fmax(0.0f, fmin(1.0f, inPos.y / 0.6 + 0.5));
        mainScene->currentColor = hsv_to_rgb(hue, saturate, brightness);
    }
    return 1;
}

void ColorPicker::open() {
    opened = 1;
}

void ColorPicker::close() {
    opened = 0;
}
