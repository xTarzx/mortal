#pragma once

#include "raylib.h"

enum MenuScreen {
    MENU_MAIN = 0,
};

class Menu {
    MenuScreen screen;
    Font neon_font;
    Font bitroad_font;
    Font hokjesgeest_font;
    Font pointless_font;

   public:
    void (*onclick_editor)() = nullptr;
    Menu();
    void update(float dt);
    void draw();
};