#pragma once

enum MenuScreen {
    MENU_MAIN = 0,
};

struct Menu {
    MenuScreen screen;

    void draw();
};