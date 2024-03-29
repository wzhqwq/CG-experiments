//
//  sideBar.hpp
//  cg-1
//
//  Created by 王子涵 on 2023/3/29.
//

#ifndef sideBar_hpp
#define sideBar_hpp

#include "common.h"
#include "geometry.hpp"
#include "shader.hpp"
#include "tools.hpp"
#include "colorPicker.hpp"
#include "scene.hpp"
#include "texture.hpp"
#include <vector>

using namespace std;

class SideBar {
public:
    SideBar() {
        create();
    }
    void paint();
    int mouseMove(float x, float y, int button);
    void switched(int id);
private:
    void create();
    int clicked(int id);
    Rect* createBtn();
    
    vector<Rect*> buttons;
    Rect *pickerBtn;
    int selected = -1;
};

#endif /* sideBar_hpp */
