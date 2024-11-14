#include <iostream>
#include <cassert>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <box2d/box2d.h>

#include "common.h"
#include "psik.h"
#include "pose.h"
#include "poses.h"

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

struct Ground {
    b2BodyId bodyId;
    b2Vec2 extent;

    Ground(b2WorldId worldId) {
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.position = {0.0f, 0.0f};
        bodyId = b2CreateBody(worldId, &bodyDef);
        extent = {5.8f, 1.5f};
        b2Polygon polygon = b2MakeBox(extent.x, extent.y);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.friction = 1.0f;
        b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
    }

    void draw() {
        b2Vec2 p = b2Body_GetWorldPoint(bodyId, {-extent.x, extent.y});

        DrawRectangle(p.x * PPM, -p.y * PPM, extent.x * 2 * PPM, extent.y * 2 * PPM, GetColor(0x8095b9));
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "mortal");

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);

    Ground ground = Ground(worldId);
    Psik psik = Psik(worldId);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    Camera2D camera{
        .offset = {GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f},
        .target = {0.0f, -2.3f * PPM},
        .rotation = 0.0f,
        .zoom = 1.84f,

    };

    float camera_speed = 150.0f;
    float zoom_speed = 1.0f;

    // std::vector<KF> kfs1 = {
    //     {.pose = Poses::standing, .frame_dur = 8},
    //     {.pose = Poses::standing_rlx, .frame_dur = 0},
    //     {.pose = Poses::jump_prep, .frame_dur = 0},
    //     {.pose = Poses::prep_swing, .frame_dur = 3},
    //     {.pose = Poses::jump0, .frame_dur = 6},
    //     {.pose = Poses::jump, .frame_dur = 0},
    //     {.pose = Poses::tuck, .frame_dur = 0},
    //     {.pose = Poses::land0, .frame_dur = 6},
    //     {.pose = Poses::land, .frame_dur = 4},
    // };
    // std::vector<KF> kfs2 = {
    //     {.pose = Poses::standing, .frame_dur = 15},
    //     {.pose = Poses::standing_rlx, .frame_dur = 0},
    //     {.pose = Poses::jump_prep, .frame_dur = 0},
    //     {.pose = Poses::prep_swing, .frame_dur = 3},
    //     {.pose = Poses::jump0, .frame_dur = 6},
    //     {.pose = Poses::jump, .frame_dur = 0},
    //     {.pose = Poses::pike, .frame_dur = 0},
    //     {.pose = Poses::land0, .frame_dur = 6},
    //     {.pose = Poses::land, .frame_dur = 0},
    // };

    // std::vector<KF> vk = {
    //     {.pose = Poses::standing, .frame_dur = 15},
    //     {.pose = Poses::standing_rlx, .frame_dur = 0},
    //     {.pose = Poses::jump_prep, .frame_dur = 0},
    //     {.pose = Poses::prep_swing, .frame_dur = 3},
    //     {.pose = Poses::jump0, .frame_dur = 6},
    //     {.pose = Poses::jump, .frame_dur = 0},
    //     {.pose = Poses::split, .frame_dur = 0},

    // };

    std::vector<KF> edit_kfs = {
        {.pose = Poses::zero, .frame_dur = 0},
        {.pose = Poses::standing, .frame_dur = 0},
    };

    edit_kfs[0].pose.r_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.8f;
    edit_kfs[0].pose.r_shoulder_force = 10.0f;
    edit_kfs[1].pose.r_ankle_force = 3.0f;
    edit_kfs[1].pose.r_ankle_angle = ANKLE_UPPER_ANGLE * 0.5f;
    edit_kfs[1].pose.l_ankle_force = 3.0f;
    edit_kfs[1].pose.l_ankle_angle = ANKLE_UPPER_ANGLE * 0.5f;

    // int k = 0;
    // std::vector<KF> kfs[] = {
    //     kfs1, kfs2, vk};
    Poser poser = Poser(&psik, edit_kfs);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        int screen_width = GetRenderWidth();
        int screen_height = GetRenderHeight();
        Vector2 mouse_pos = GetMousePosition();

        Vector2 cam_mov = {(float)IsKeyDown(KEY_D) - (float)IsKeyDown(KEY_A), (float)IsKeyDown(KEY_S) - (float)IsKeyDown(KEY_W)};
        int zoom_dir = IsKeyDown(KEY_E) - IsKeyDown(KEY_Q);

        if (IsKeyPressed(KEY_R)) {
            b2DestroyWorld(worldId);
            worldId = b2CreateWorld(&worldDef);
            poser.reset();
            ground = Ground(worldId);
            psik = Psik(worldId);
        }

        // if (IsKeyPressed(KEY_V)) {
        //     k = (k + 1) % (sizeof(kfs) / sizeof(kfs[0]));
        //     poser.kfs = kfs[k];
        // }

        if (IsKeyPressed(KEY_SPACE)) {
            poser.next_kf();
        }

        poser.update();

        camera.zoom += zoom_dir * zoom_speed * dt;
        camera.offset = {screen_width / 2.0f, screen_height / 2.0f};
        camera.target = Vector2Add(camera.target, Vector2Scale(cam_mov, dt * camera_speed));

        b2World_Step(worldId, timeStep, subStepCount);

        BeginDrawing();
        ClearBackground(GetColor(0x1f1f1fff));

        BeginMode2D(camera);

        ground.draw();
        // box.draw();

        psik.draw();

        EndMode2D();

        // timeline

        float timeline_height = screen_height * 0.20f;
        Rectangle timeline_rec = {0.0f, screen_height - timeline_height, (float)screen_width, timeline_height};
        DrawRectangleRec(timeline_rec, GetColor(0x333333ff));

        float sz = timeline_height * 0.65f;
        float padding = sz * 0.1f;
        float x = padding;
        float y = screen_height - timeline_height / 2 - sz / 2;
        for (int i = 0; i < poser.kfs.size(); i++) {
            Rectangle box = {x, y, sz, sz};
            DrawRectangleRec(box, GetColor(0x555555ff));

            const char* i_str = TextFormat("%d", i);
            float font_sz = sz * 0.8f;
            Vector2 msr = MeasureTextEx(GetFontDefault(), i_str, font_sz, 0.0f);
            DrawText(i_str, box.x + box.width / 2 - msr.x / 2, box.y + box.height / 2 - msr.y / 2, font_sz, i == poser.kf ? BLUE : WHITE);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, box)) {
                poser.kf = i;
                poser.frame = 0;
            }

            // TODO: border

            x += sz + padding;
        }

        // Rectangle r_shoulder_slider = {50.0f, 0.0f, 100.0f, 25.0f};
        // GuiSlider(r_shoulder_slider, TextFormat("%.2f", SHOULDER_LOWER_ANGLE * RAD2DEG), TextFormat("%.2f", SHOULDER_UPPER_ANGLE * RAD2DEG), &poser.kfs[poser.kf].pose.r_shoulder_angle, SHOULDER_LOWER_ANGLE, SHOULDER_UPPER_ANGLE);
        // Rectangle r_elbow_slider = {50.0f, 50.0f, 100.0f, 25.0f};
        // GuiSlider(r_elbow_slider, TextFormat("%.2f", ELBOW_LOWER_ANGLE * RAD2DEG), TextFormat("%.2f", ELBOW_UPPER_ANGLE * RAD2DEG), &poser.kfs[poser.kf].pose.r_elbow_angle, ELBOW_LOWER_ANGLE, ELBOW_UPPER_ANGLE);

        EndDrawing();
    }

    b2DestroyWorld(worldId);
    CloseWindow();
    return 0;
}
