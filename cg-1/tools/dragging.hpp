//
//  dragging.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/24.
//

#ifndef dragging_hpp
#define dragging_hpp

#include "common.h"
#include "scene.hpp"

enum DragState {
    Standby,
    Starting,
    Dragging
};

class DragTool {
public:
    DragTool() {};
    void mouseMove(double x, double y, int left, int right);
    void cancel();
    virtual void setKeyMods(int mods);
protected:
    virtual void dragStart(vec3 start, vec3 end);
    virtual void dragMove(vec3 end);
    virtual void dragStop(vec3 end);
    virtual void clicked(vec3 p);
    
    int realPos = 0;
    int leftButton = 0, rightButton = 0;
    vec3 lastPoint;
private:
    DragState state = Standby;
};

class HandTool : public DragTool {
public:
    HandTool() {
        realPos = 1;
    };
protected:
    void dragStart(vec3 start, vec3 end);
    void dragMove(vec3 end);
private:
    vec3 startPoint, startPos, realStartPoint;
    float startScale;
};

class ManipulateTool : public DragTool {
protected:
    void clicked(vec3 p);
    void dragStart(vec3 start, vec3 end);
    void dragMove(vec3 end);
    void dragStop(vec3 end);
private:
    int dragging = 0;
};

#endif /* dragging_hpp */
