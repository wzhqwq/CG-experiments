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
    DragTool(Scene *s): scene(s) {};
    void mouseMove(double x, double y, int left, int right);
    void cancel();
    virtual void setKeyMods(int mods);
protected:
    virtual void start(vec3 start, vec3 end);
    virtual void updateEnd(vec3 end);
    virtual void ended(vec3 end);
    virtual void clicked(vec3 p);
    
    Scene *scene;
    int realPos = 0;
    int leftButton = 0, rightButton = 0;
private:
    DragState state = Standby;
    vec3 lastPoint;
};

class HandTool : public DragTool {
public:
    HandTool(Scene *s) : DragTool(s) {
        realPos = 1;
    };
protected:
    void start(vec3 start, vec3 end);
    void updateEnd(vec3 end);
private:
    vec3 startPoint, startPos, realStartPoint;
    float startScale;
};

class ManipulateTool : public DragTool {
public:
    ManipulateTool(Scene *s) : DragTool(s) {};
};

#endif /* dragging_hpp */
