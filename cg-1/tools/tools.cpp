//
//  tools.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/24.
//

#include "tools.hpp"

Tools tools;

void initTools() {
    tools.manipulate = new ManipulateTool();
    tools.hand = new HandTool();
    tools.line = new LineCreator();
    tools.triangle = new TriangleCreator();
    tools.rect = new RectCreator();
    tools.circle = new CircleCreator();
    
    currentTool = tools.manipulate;
}

void switchTool(ToolName name) {
    switch (name) {
        case HAND:
            currentTool = tools.hand;
            break;
        case MANIPULATE:
            currentTool = tools.manipulate;
            break;
        case LINE:
            currentTool = tools.line;
            break;
        case TRIANGLE:
            currentTool = tools.triangle;
            break;
        case RECT:
            currentTool = tools.rect;
            break;
        case CIRCLE:
            currentTool = tools.circle;
            break;
        case PEN:
            break;
        default:
            break;

    }
}
