#include "raylib.h"

#include "editor.h"
#include "mmenu.h"

namespace Screen {
enum e_Screen {
    MENU,
    EDITOR
};
}
using Screen::e_Screen;

e_Screen screen = Screen::MENU;

void open_editor() {
    screen = Screen::EDITOR;
}

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "mortal");
    SetExitKey(KEY_Z);

    Editor editor = Editor();
    Menu menu = Menu();

    menu.onclick_editor = open_editor;

    bool quit = false;
    while (!quit && !WindowShouldClose()) {
        float dt = GetFrameTime();

        switch (screen) {
            case Screen::MENU:

                if (IsKeyPressed(KEY_ESCAPE)) {
                    // screen = Screen::EDITOR;
                    quit = true;
                }
                menu.update(dt);
                break;
            case Screen::EDITOR:
                if (IsKeyPressed(KEY_ESCAPE)) {
                    screen = Screen::MENU;
                }
                editor.update(dt);
                break;

            default:
                break;
        }

        BeginDrawing();

        switch (screen) {
            case Screen::MENU:
                menu.draw();
                break;
            case Screen::EDITOR:
                editor.draw();
                break;

            default:
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
