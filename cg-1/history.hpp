//
//  history.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/4/2.
//

#ifndef history_hpp
#define history_hpp

#include "common.h"
#include "geometry.hpp"
#include "scene.hpp"
#include <stack>

using namespace std;

class Operation {
public:
    virtual void undo();
};

class CreationOp : public Operation {
public:
    void undo();
};

class DeletionOp : public Operation {
public:
    DeletionOp(int _index, Geometry *geo) : index(_index), geometry(geo) {};
    void undo();
private:
    int index;
    Geometry *geometry;
};

class TranslationOp : public Operation {
public:
    TranslationOp(vec2 t, Geometry *geo) : translation(t), geometry(geo) {};
    void undo();
private:
    vec2 translation;
    Geometry *geometry;
};

class ScalingOp : public Operation {
public:
    ScalingOp(vec2 s, vec2 c, Geometry *geo) : scaling(s), center(c), geometry(geo) {};
    void undo();
private:
    vec2 center;
    vec2 scaling;
    Geometry *geometry;
};

class ColoringOp : public Operation {
public:
    ColoringOp(vec3 _lastColor, Geometry *geo) : lastColor(_lastColor), geometry(geo) {};
    void undo();
private:
    vec3 lastColor;
    Geometry *geometry;
};

void pushOp(Operation *op);
void popOp();

#endif /* history_hpp */
