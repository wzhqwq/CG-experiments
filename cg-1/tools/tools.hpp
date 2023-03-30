//
//  tools.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/24.
//

#ifndef tools_hpp
#define tools_hpp

#include "common.h"
#include "dragging.hpp"
#include "creator.hpp"

enum ToolName {
    HAND, MANIPULATE, LINE, TRIANGLE, RECT, CIRCLE, PEN
};

struct Tools {
    HandTool *hand;
    ManipulateTool *manipulate;
    // TODO: vertex tool
    LineCreator *line;
    TriangleCreator *triangle;
    RectCreator *rect;
    CircleCreator *circle;
};

void initTools();
void switchTool(ToolName name);

extern DragTool *currentTool;

#endif /* tools_hpp */
