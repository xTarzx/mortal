#include <iostream>
#include <cassert>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <box2d/box2d.h>

#include "common.h"
#include "psik.h"

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

struct Box {
    b2BodyId bodyId;
    b2Vec2 extent;

    Box(b2WorldId worldId) {
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = {0.0f, 20.0f};
        bodyId = b2CreateBody(worldId, &bodyDef);
        extent = {2.5f, 2.5f};
        b2Polygon polygon = b2MakeBox(extent.x, extent.y);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
    }

    void draw() {
        b2Vec2 p = b2Body_GetWorldPoint(bodyId, {-extent.x, extent.y});
        b2Rot rotation = b2Body_GetRotation(bodyId);
        float angle = b2Rot_GetAngle(rotation);

        Rectangle rec = {p.x * PPM, -p.y * PPM, extent.x * 2 * PPM, extent.y * 2 * PPM};
        DrawRectanglePro(rec, {0.0f, 0.0f}, -angle * RAD2DEG, DARKBLUE);
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "mortal");

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);

    Ground ground = Ground(worldId);
    // Box box = Box(worldId);
    // b2Body_ApplyAngularImpulse(box.bodyId, 110.0f, false);

    Psik psik = Psik(worldId);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    Camera2D camera{
        .offset = {GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f + 6.8f * PPM},
        // .offset = {GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f},
        .target = {0.0f, 0.0f},
        .rotation = 0.0f,
        .zoom = 2.62f,

    };

    float camera_speed = 150.0f;
    float zoom_speed = 1.0f;

    Pose poses[] = {
        Poses::standing,
        Poses::jump_prep,
        Poses::jump,
        Poses::tuck,
    };

    int pose_idx = 0;
    int pose_count = sizeof(poses) / sizeof(poses[0]);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Vector2 cam_mov = {(float)IsKeyDown(KEY_D) - (float)IsKeyDown(KEY_A), (float)IsKeyDown(KEY_S) - (float)IsKeyDown(KEY_W)};
        int zoom_dir = IsKeyDown(KEY_E) - IsKeyDown(KEY_Q);

        if (IsKeyPressed(KEY_R)) {
            b2DestroyWorld(worldId);
            worldId = b2CreateWorld(&worldDef);
            pose_idx = 0;
            ground = Ground(worldId);
            psik = Psik(worldId);
        }

        if (IsKeyPressed(KEY_SPACE)) {
            pose_idx = (pose_idx + 1) % pose_count;
        }

        psik.set_pose(poses[pose_idx]);

        camera.zoom += zoom_dir * zoom_speed * dt;
        camera.target = Vector2Add(camera.target, Vector2Scale(cam_mov, dt * camera_speed));

        b2World_Step(worldId, timeStep, subStepCount);

        BeginDrawing();
        ClearBackground(GetColor(0x1f1f1fff));

        BeginMode2D(camera);

        ground.draw();
        // box.draw();

        psik.draw();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    b2DestroyWorld(worldId);
    return 0;
}
