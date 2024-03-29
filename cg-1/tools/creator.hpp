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
protected:
    RubberBandGeometry *result;
    void dragMove(vec3 end);
    void dragStop(vec3 end);
};

class LineCreator : public RubberBandCreator {
protected:
    void dragStart(vec3 start, vec3 end);
};

class TriangleCreator : public RubberBandCreator {
protected:
    void dragStart(vec3 start, vec3 end);
};

class RectCreator : public RubberBandCreator {
protected:
    void dragStart(vec3 start, vec3 end);
};

class CircleCreator : public RubberBandCreator {
protected:
    void dragStart(vec3 start, vec3 end);
};

#endif /* creator_hpp */
