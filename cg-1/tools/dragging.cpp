//
//  dragging.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/24.
//

#include "dragging.hpp"

void DragTool::mouseMove(double x, double y, int mouseState) {
    vec3 p = scene->rayCast(x, y);
    switch (mouseState) {
        case GLFW_PRESS:
            switch (state) {
                case Standby:
                    state = Starting;
                    break;
                case Starting:
                    start(lastPoint, p);
                    state = Dragging;
                    break;
                case Dragging:
                    updateEnd(p);
                    break;
                default:
                    break;
            }
            break;
        
        case GLFW_RELEASE:
            if (state == Dragging) {
                updateEnd(p);
                ended(p);
                state = Standby;
            }
            break;
            
        default:
            break;
    }
    lastPoint = p;
}

void DragTool::cancel() {
    ended(lastPoint);
    state = Standby;
}

void DragTool::start(vec3 start, vec3 end) {}
void DragTool::updateEnd(vec3 end) {}
void DragTool::ended(vec3 end) {}

