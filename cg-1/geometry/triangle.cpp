//
//  triangle.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#include "geometry.hpp"

void Triangle::updateEnd(vec3 end) {
    vertices[0] = vec3((startPoint.x + end.x) / 2, startPoint.y, 0);
    vertices[1] = vec3(startPoint.x, end.y, 0);
    vertices[2] = vec3(end.x, end.y, 0);
    updateBuffer();
}
