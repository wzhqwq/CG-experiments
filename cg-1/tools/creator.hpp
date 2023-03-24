//
//  creator.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#ifndef creator_hpp
#define creator_hpp

#include "common.h"
#include "scene.hpp"
#include "dragging.hpp"
#include "geometry.hpp"

class RubberBandCreator : public DragTool {
public:
    RubberBandCreator(Scene *s) : DragTool(s) {};
protected:
    RubberBandGeometry *result;
    void updateEnd(vec3 end);
    void ended(vec3 end);
};

class LineCreator : public RubberBandCreator {
public:
    LineCreator(Scene *s) : RubberBandCreator(s) {};
protected:
    void start(vec3 start, vec3 end);
};

class TriangleCreator : public RubberBandCreator {
public:
    TriangleCreator(Scene *s) : RubberBandCreator(s) {};
protected:
    void start(vec3 start, vec3 end);
};

#endif /* creator_hpp */
