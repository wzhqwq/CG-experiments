//
//  creator.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#include "creator.hpp"

void RubberBandCreator::ended(vec3 end) {
    result = NULL;
}
void RubberBandCreator::updateEnd(vec3 end) {
    result->updateEnd(end);
}

void LineCreator::start(vec3 start, vec3 end) {
    result = new Line(start, end);
    result->setColor(mainScene->currentColor);
    mainScene->shapes.push_back(result);
}

void TriangleCreator::start(vec3 start, vec3 end) {
    result = new Triangle(start, end);
    result->setColor(mainScene->currentColor);
    result->setMode(mainScene->currentDrawMode);
    mainScene->shapes.push_back(result);
}
