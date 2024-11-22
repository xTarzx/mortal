#include <iostream>
#include <algorithm>
#include <cassert>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "box2d/box2d.h"

#include "editor.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "mortal");

    Editor editor = Editor();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        editor.update(dt);

        BeginDrawing();

        editor.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
