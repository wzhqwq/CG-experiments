//
//  line.cpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/23.
//

#include "geometry.hpp"

void Line::updateEnd(vec3 end) {
    vertices[1] = end;
    updateBuffer();
}
