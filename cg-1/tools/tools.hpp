//
//  tools.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/24.
//

#ifndef tools_hpp
#define tools_hpp

#include "dragging.hpp"
#include "creator.hpp"

struct Tools {
    HandTool *hand;
    ManipulateTool *manipulate;
    // TODO: vertex tool
    LineCreator *line;
    TriangleCreator *triangle;
    
};
struct Cursors {
    GLFWcursor *hand;
    GLFWcursor *cross;
};

void initTools(Scene *scene);
void initCursors();

extern Tools tools;
extern Cursors cursors;

#endif /* tools_hpp */
