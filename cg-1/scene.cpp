//
//  scene.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "scene.hpp"

mat4 Scene::getVPMatrix() {
    changed = 0;
    updateMVPMatrix();
    return VP;
}
void Scene::updateMVPMatrix() {
    VP = projection * view;
    invVP = inverse(VP);
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

vec3 Scene::rayCast(double posX, double posY) {
    if (changed) updateMVPMatrix();
    glm::vec4 screenPos = glm::vec4((posX - x) / (w * 0.5f) - 1.0f,
                                    -((posY - y) / (h * 0.5f) - 1.0f),
                                    1.0f,
                                    1.0f);
    glm::vec4 worldPos = invVP * screenPos;

    return glm::vec3(worldPos);
}
