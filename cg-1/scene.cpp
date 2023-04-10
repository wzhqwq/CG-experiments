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
    float _w = w / scale, _h = h / scale;
    projection = ortho(-(_w / 2.0f), _w / 2.0f,
                       -(_h / 2.0f), _h / 2.0f,
                       0.0f, 1000.0f
                       );
    currentPos = currentPos + vec3((vec2(centerX, centerY) - vec2(currentPos)) * (scale / currentScale - 1), 0.0);
    view = lookAt(currentPos, currentPos - vec3(0, 0, 100), vec3(0, 1, 0));
    currentScale = scale;
    changed = 1;
    if (selectionRect) {
        selectionRect->updateScale(currentScale);
    }
}

void Scene::moveTo(float posX, float posY) {
    currentPos = vec3(posX, posY, currentPos.z);
    view = lookAt(currentPos, currentPos - vec3(0, 0, 100), vec3(0, 1, 0));
    changed = 1;
}

float Scene::getScale() { return currentScale; }
vec3 Scene::getPos() { return currentPos; }
int Scene::isChanged() { return changed; }

vec3 Scene::toWorldPos(float posX, float posY) {
    if (changed) updateVPMatrix();
    vec4 viewPos = vec4(posX / (w * 0.5f) - 1.0f,
                          -(posY / (h * 0.5f) - 1.0f),
                          1.0f,
                          1.0f);
    vec4 worldPos = invVP * viewPos;

    return vec3(worldPos);
}

void Scene::render(GLenum renderMode) {
    glRenderMode(renderMode);
    if (renderMode == GL_SELECT) {
        glInitNames();
        glPushName(0);
    }
    for (int i = 0; i < shapes.size(); i++) {
        if (renderMode == GL_SELECT) glLoadName(i);
        shapes[i]->paint();
    }
}

Geometry *Scene::rayCast(float x, float y) {
    vec4 viewPos = VP * vec4(x, y, 1.0, 1.0);
    
    GLuint buffer[100];
    glSelectBuffer(100, buffer);
    render(GL_SELECT);
    
    glWindowPos2f(viewPos.x, viewPos.y);

    printf("------test %.2f %.2f---------\n", viewPos.x, viewPos.y);
    for (int i = 0; i < 10; i++) {
        printf("%u\n", buffer[i]);
    }
    int hits = glRenderMode(GL_RENDER);
    printf("-----hits %d-----\n", hits);

    return NULL;
}
