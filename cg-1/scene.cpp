//
//  scene.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#include "scene.hpp"

mat4 Scene::getVPMatrix() {
    changed = 0;
    updateVPMatrix();
    return VP;
}
void Scene::updateVPMatrix() {
    VP = projection * view;
    invVP = inverse(VP);
}

void Scene::zoomTo(float scale, float centerX, float centerY) {
    currentScale = scale;
    float _w = w / currentScale, _h = h / currentScale;
    projection = ortho(-(_w / 2.0f), _w / 2.0f,
                       -(_h / 2.0f), _h / 2.0f,
                       0.0f, 1000.0f
                       );
    changed = 1;
}

void Scene::moveTo(float posX, float posY) {
    currentPos = vec3(posX, posY, currentPos.z);
    view = lookAt(currentPos, currentPos - vec3(0, 0, 100), vec3(0, 1, 0));
    changed = 1;
}

float Scene::getScale() { return currentScale; }
vec3 Scene::getPos() { return currentPos; }
int Scene::isChanged() { return changed; }

vec3 Scene::rayCast(float posX, float posY) {
    if (changed) updateVPMatrix();
    vec4 screenPos = vec4((posX - x) / (w * 0.5f) - 1.0f,
                          -((posY - y) / (h * 0.5f) - 1.0f),
                          1.0f,
                          1.0f);
    vec4 worldPos = invVP * screenPos;

    return vec3(worldPos);
}
