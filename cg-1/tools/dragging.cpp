//
//  dragging.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/24.
//

#include "dragging.hpp"

void DragTool::mouseMove(double x, double y, int left, int right) {
    vec3 p = realPos ? vec3(x, -y, 0) : mainScene->rayCast(x, y);
    leftButton = left;
    rightButton = right;
    switch (left | right) {
        case GLFW_PRESS:
            switch (state) {
                case Standby:
                    state = Starting;
                    break;
                case Starting:
                    dragStart(lastPoint, p);
                    state = Dragging;
                    break;
                case Dragging:
                    dragMove(p);
                    break;
                default:
                    break;
            }
            break;
        
        case GLFW_RELEASE:
            switch (state) {
                case Dragging:
                    dragMove(p);
                    dragStop(p);
                    state = Standby;
                    break;
                case Starting:
                    clicked(p);
                    state = Standby;
                    break;
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
    lastPoint = p;
}

void DragTool::cancel() {
    dragStop(lastPoint);
    state = Standby;
}

void DragTool::dragStart(vec3 start, vec3 end) {
#ifdef TEST_BOUNDING
    printf("start not bound\n");
#endif
}
void DragTool::dragMove(vec3 end) {
#ifdef TEST_BOUNDING
    printf("start not bound\n");
#endif
}
void DragTool::dragStop(vec3 end) {
#ifdef TEST_BOUNDING
    printf("updateEnd not bound\n");
#endif
}
void DragTool::clicked(vec3 p) {
#ifdef TEST_BOUNDING
    printf("clicked not bound\n");
#endif
}
void DragTool::setKeyMods(int mods) {
#ifdef TEST_BOUNDING
    printf("setKeyMods not bound\n");
#endif
}

void HandTool::dragStart(vec3 start, vec3 end) {
    realStartPoint = start;
    startPoint = mainScene->rayCast(start.x, -start.y);
    startPos = mainScene->getPos();
    startScale = mainScene->getScale();
    dragMove(end);
}
void HandTool::dragMove(vec3 end) {
    vec3 delta = end - realStartPoint;
    if (leftButton) {
        vec3 newPos = startPos - delta;
        mainScene->moveTo(newPos.x, newPos.y);
    }
    else if (rightButton) {
        mainScene->zoomTo(fmax(1.0f, startScale * (1.0f + delta.x / 100.0f)), startPoint.x, startPoint.y);
    }
}

void ManipulateTool::clicked(vec3 p) {
    int maxZIndex = -1;
    for (auto geo : mainScene->shapes) {
        if (geo->getZIndex() > maxZIndex && geo->isIn(p)) {
            mainScene->selectedItem = geo;
            maxZIndex = geo->getZIndex();
        }
    }
    if (maxZIndex == -1) mainScene->selectedItem = NULL;
}
void ManipulateTool::dragStart(vec3 start, vec3 end) {
    clicked(start);
    if (mainScene->selectedItem) {
        startPoint = start;
        startCenter = mainScene->selectedItem->getCenter();
        currentTranslation = vec2(0.0);
        currentScaling = vec2(1.0);
        type = leftButton ? 1 : 2;
        dragging = 1;
        dragMove(end);
    }
}
void ManipulateTool::dragMove(vec3 end) {
    if (dragging) doTransformation(end - startPoint);
}
void ManipulateTool::setKeyMods(int mods) {
    fitAxis = mods & GLFW_MOD_SHIFT;
    centerFixed = mods & GLFW_MOD_ALT;
    if (dragging) doTransformation(lastPoint - startPoint);
}
void ManipulateTool::doTransformation(vec2 delta) {
    if (leftButton) {
        if (fitAxis) {
            if (fabs(delta.x) > fabs(delta.y)) {
                delta.y = 0;
            }
            else {
                delta.x = 0;
            }
        }
        vec2 t = delta - currentTranslation;
        mainScene->selectedItem->translate(t.x, t.y);
        currentTranslation = delta;
    }
    else if (rightButton) {
        vec2 center = vec2(centerFixed ? startCenter : startPoint);
        vec2 s;
        if (fitAxis) {
            s = vec2(1.0);
            if (fabs(delta.x) > fabs(delta.y)) {
                s.x = 1.0f + delta.x / 100;
            }
            else {
                s.y = 1.0f + delta.y / 100;
            }
        }
        else {
            s = vec2(1.0f + delta.x / 100);
        }
        vec2 s2 = s / currentScaling;
        mainScene->selectedItem->scale(s2.x, s2.y, center.x, center.y);
        currentScaling = s;
    }
}
void ManipulateTool::dragStop(vec3 end) {
    if (!dragging) return;
    dragging = 0;
    switch (type) {
        case 1:
            pushOp(new TranslationOp(currentTranslation, mainScene->selectedItem));
            break;
        case 2:
            pushOp(new ScalingOp(currentScaling, vec2(centerFixed ? startCenter : startPoint), mainScene->selectedItem));
            break;
    }
}
