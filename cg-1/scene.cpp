//
//  scene.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "scene.hpp"

mat4 Scene::getMVPMatrix() {
    changed = 0;
    return projection * view * model;
}

void Scene::zoomTo(float scale, float mouseX, float mouseY) {
    mouseX -= x;
    mouseY -= y;
    // MVP * p = (mX, mY, 0, 1)
    // P * V' * M' * p = (mX, mY, 0, 1)
    changed = 1;
}

void Scene::move(float offsetX, float offsetY) {
    projection = translate(projection, vec3(offsetX, -offsetY, 0));
    changed = 1;
}

float Scene::getScale() {
    return currentScale;
}

int Scene::isChanged() {
    return changed;
}
