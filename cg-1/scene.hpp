//
//  scene.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#ifndef scene_hpp
#define scene_hpp

#include "common.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Scene {
public:
    Scene(int _x, int _y, int _w, int _h): x(_x), y(_y), w(_w), h(_h) {
        glViewport(_x, _y, _w, _h);
        projection = ortho(-(_w / 2.0f), _w / 2.0f,
                           -(_h / 2.0f), _h / 2.0f,
                           -1000.0f, 1000.0f
                           );
        view = lookAt(vec3(0, 0, 100), vec3(0, 0, 0), vec3(0, 1, 0));
        model = mat4(1.0f);
    }
    mat4 getMVPMatrix();
    void zoomTo(float scale, float mouseX, float mouseY);
    void move(float offsetX, float offsetY);
    float getScale();
    int isChanged();
private:
    mat4 projection;
    mat4 view;
    mat4 model;
    mat4 mvp;
    float currentScale = 1.0f;
    int changed = 1;
    int x, y, w, h;
};

#endif /* scene_hpp */
