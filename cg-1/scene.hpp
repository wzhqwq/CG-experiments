//
//  scene.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/22.
//

#ifndef scene_hpp
#define scene_hpp

#include "common.h"
#include "geometry.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Scene {
public:
    Scene(int _x, int _y, int _w, int _h): x(_x), y(_y), w(_w), h(_h) {
        glViewport(_x, _y, _w, _h);
        projection = ortho(-(_w / 2.0f), _w / 2.0f,
                           -(_h / 2.0f), _h / 2.0f,
                           0.0f, 1000.0f
                           );
        currentPos = vec3(0, 0, 1000.0f);
        view = lookAt(currentPos, vec3(0, 0, 0), vec3(0, 1, 0));
    }
    
    mat4 getVPMatrix();
    void zoomTo(float scale, float centerX, float centerY);
    void moveTo(float posX, float posY);
    
    float getScale();
    vec3 getPos();
    int isChanged();
    
    vec3 rayCast(float x, float y);
    
    vector<Geometry*> shapes;
    vec3 currentColor = vec3(1.0f, 0.0f, 0.0f);
    
private:
    void updateVPMatrix();
    
    mat4 projection;
    mat4 view;
    mat4 VP;
    mat4 invVP;
    
    float currentScale = 1.0f;
    vec3 currentPos;
    
    int changed = 1;
    int x, y, w, h;
};

#endif /* scene_hpp */
