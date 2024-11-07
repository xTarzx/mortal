#include <iostream>
#include <cassert>
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>
#include <box2d/box2d.h>

const float PPM = 100;

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

struct Psik {
    b2BodyId bodyId;

    Psik(b2WorldId worldId) {
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = {0.0f, 3.0f};

        bodyId = b2CreateBody(worldId, &bodyDef);

        float torso_w = 0.25f;
        float torso_h = 0.63f;
        float head_w = 0.08f;
        float head_h = 0.12f;

        b2ShapeDef shapeDef = b2DefaultShapeDef();

        b2Polygon torso = b2MakeOffsetBox(
            torso_w * 0.5f,          // hx
            torso_h * 0.5f,          // hy
            {0.0f, torso_h * 0.5f},  // offset
            0.0f                     // angle
        );
        b2CreatePolygonShape(bodyId, &shapeDef, &torso);

        float thigh_length = 0.06f;
        b2Vec2 torso_base = {torso.centroid.x, torso.centroid.y + torso_h * 0.5f};

        b2Vec2 thigh_points[] = {
            {torso_base.x - torso_w * 0.5f, torso_base.y},
            {torso_base.x + torso_w * 0.5f, torso_base.y},
            {torso_base.x - torso_w * 0.5f, torso_base.y - thigh_length},
            {torso_base.x - torso_w * 0.5f, torso_base.y - thigh_length},
        };

        b2Hull thigh_hull = b2ComputeHull(thigh_points, 4);
        b2Polygon thigh = b2MakePolygon(&thigh_hull, 0);
        b2CreatePolygonShape(bodyId, &shapeDef, &thigh);

        b2Vec2 head_center = {0.0f, torso_h + head_h * 0.5f};
        b2Capsule head = b2Capsule{
            .center1 = {head_center.x, head_center.y + head_h * 0.5f},
            .center2 = {head_center.x, head_center.y - head_h * 0.5f},
            .radius = head_w * 0.5f,
        };
        b2CreateCapsuleShape(bodyId, &shapeDef, &head);
    }

    void draw() {
        b2Vec2 p = b2Body_GetWorldPoint(bodyId, {0, 0});

        int shape_count = b2Body_GetShapeCount(bodyId);
        b2ShapeId *shapeIds = (b2ShapeId *)malloc(sizeof(b2ShapeId) * shape_count);
        assert(shapeIds != nullptr && "malloc failed");
        b2Body_GetShapes(bodyId, shapeIds, shape_count);

        for (int i = 0; i < shape_count; i++) {
            b2ShapeId shape_id = shapeIds[i];
            b2ShapeType shape_type = b2Shape_GetType(shape_id);

            switch (shape_type) {
                case b2_polygonShape: {
                    b2Polygon polygon = b2Shape_GetPolygon(shape_id);
                    for (int j = 0; j < polygon.count; j++) {
                        b2Vec2 vert = polygon.vertices[j];

                        DrawCircleV({(p.x + vert.x) * PPM, (-p.y - vert.y) * PPM}, 0.03 * PPM, RED);
                    }

                    break;
                }

                case b2_circleShape: {
                    b2Circle circle = b2Shape_GetCircle(shape_id);

                    DrawCircleV({(p.x + circle.center.x) * PPM, (-p.y - circle.center.y) * PPM}, circle.radius * PPM, WHITE);
                } break;

                case b2_capsuleShape: {
                    b2Capsule capsule = b2Shape_GetCapsule(shape_id);

                    DrawCircle((p.x + capsule.center1.x) * PPM, (-p.y - capsule.center1.y) * PPM, capsule.radius * PPM, GREEN);
                    DrawCircle((p.x + capsule.center2.x) * PPM, (-p.y - capsule.center2.y) * PPM, capsule.radius * PPM, GREEN);
                    // Rectangle rec = {
                    //     .x = (p.x + capsule.center1.x - capsule.radius) * PPM,
                    //     .y = (-p.y - capsule.center1.y) * PPM,
                    //     .width = capsule.radius * 2 * PPM,
                    //     .height = (capsule.center1.y - capsule.center2.y) * PPM};

                    // DrawRectangleRec(rec, YELLOW);

                } break;

                default:
                    assert(false && "unhandled");
                    break;
            }
        }

        DrawCircle(p.x * PPM, -p.y * PPM, 0.03 * PPM, MAGENTA);

        free(shapeIds);
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

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Vector2 cam_mov = {(float)IsKeyDown(KEY_D) - (float)IsKeyDown(KEY_A), (float)IsKeyDown(KEY_S) - (float)IsKeyDown(KEY_W)};
        int zoom_dir = IsKeyDown(KEY_E) - IsKeyDown(KEY_Q);

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
