//
//  creator.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#include "creator.hpp"

void RubberBandCreator::dragStop(vec3 end) {
    pushOp(new CreationOp((int) mainScene->shapes.size() - 1));
    result = NULL;
}
void RubberBandCreator::dragMove(vec3 end) {
    result->updateEnd(end);
}

void LineCreator::dragStart(vec3 start, vec3 end) {
    result = new Line(start, end);
    result->currentColor = mainScene->currentColor;
    result->setZIndex((int) mainScene->shapes.size());
    mainScene->shapes.push_back(result);
}

void TriangleCreator::dragStart(vec3 start, vec3 end) {
    result = new Triangle(start, end);
    result->currentColor = mainScene->currentColor;
    result->setMode(mainScene->currentDrawMode);
    result->setZIndex((int) mainScene->shapes.size());
    mainScene->shapes.push_back(result);
}
void RectCreator::dragStart(vec3 start, vec3 end) {
    result = new Rect(start, end);
    result->currentColor = mainScene->currentColor;
    result->setMode(mainScene->currentDrawMode);
    result->setZIndex((int) mainScene->shapes.size());
    mainScene->shapes.push_back(result);
}
void CircleCreator::dragStart(vec3 start, vec3 end) {
    result = new Circle(start, end);
    result->currentColor = mainScene->currentColor;
    result->setMode(mainScene->currentDrawMode);
    result->setZIndex((int) mainScene->shapes.size());
    mainScene->shapes.push_back(result);
}
