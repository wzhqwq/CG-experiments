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
#include <vector>

#define LINE_COUNT (PICKER_SIZE / PICKER_COLOR_BLOCK_SIZE)

using namespace std;

enum PickStatus {
    Idle, InRing, InRect
};

class ColorPicker {
public:
    ColorPicker() : ColorPicker(BTN_SIZE + BTN_GAP * 2, BTN_GAP) {};
    ColorPicker(float x, float y) : selfX(x), selfY(y) {
        pickerBox = new Rect(PICKER_SIZE, PICKER_SIZE);
        pickerBox->translate(PICKER_SIZE / 2 + x, PICKER_SIZE / 2 + y);
        pickerBox->setMode(Filled);
        
        addColorBlock();
    }
    
    void open();
    void close();
    void paint();
    int mouseMove(float x, float y, int left, int right);
private:
    void addColorBlock();
    void registerColor(int index);
    void pickColor(int index);
    void setColor();
    
    float selfX, selfY;
    float hue = 0.0f, saturate = 1.0f, brightness = 1.0f;
    Rect *pickerBox;
    int opened = 0;
    PickStatus status = Idle;
    vec3 lastColor;
    vector<vec3> savedColors;
    vector<Rect *> colorBlocks;
};

extern ColorPicker *picker;

#endif /* colorPicker_hpp */
