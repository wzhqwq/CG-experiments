//
//  colorPicker.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/27.
//

#ifndef colorPicker_hpp
#define colorPicker_hpp

#include "common.h"
#include "scene.hpp"
#include "geometry.hpp"
#include "shader.hpp"
#include "history.hpp"
#include <cmath>

enum PickStatus {
    Idle, InRing, InRect
};

class ColorPicker {
public:
    ColorPicker() {
        pickerBox = new Rect(PICKER_SIZE, PICKER_SIZE);
        pickerBox->translate(PICKER_SIZE / 2 + BTN_SIZE + BTN_GAP * 2, PICKER_SIZE / 2 + BTN_GAP);
        pickerBox->setMode(Filled);
    };
    
    void open();
    void close();
    void paint();
    int mouseMove(float x, float y, int button);
private:
    float hue = 0.0f, saturate = 1.0f, brightness = 1.0f;
    Rect *pickerBox;
    int opened = 0;
    PickStatus status = Idle;
    vec3 lastColor;
};

extern ColorPicker *picker;

#endif /* colorPicker_hpp */
