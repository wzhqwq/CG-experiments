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
    void mouseMove(double x, double y, int mouseState);
    void cancel();
protected:
    virtual void start(vec3 start, vec3 end);
    virtual void updateEnd(vec3 end);
    virtual void ended(vec3 end);
    
    Scene *scene;
private:
    DragState state;
    vec3 lastPoint;
};

#endif /* dragging_hpp */
