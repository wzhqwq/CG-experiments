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
    result = (RubberBandGeometry *) new Line(scene->currentColor, start, end);
    scene->shapes.push_back(result);
}

void TriangleCreator::start(vec3 start, vec3 end) {
    printf("triagle\n");
    result = (RubberBandGeometry *) new Triangle(scene->currentColor, start, end);
    scene->shapes.push_back(result);
}
