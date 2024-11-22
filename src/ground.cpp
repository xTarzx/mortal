#include "ground.h"

#include "common.h"
#include "raylib.h"

Ground::Ground(b2WorldId worldId) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.position = {0.0f, 0.0f};
    bodyId = b2CreateBody(worldId, &bodyDef);
    extent = {5.8f, 1.5f};
    b2Polygon polygon = b2MakeBox(extent.x, extent.y);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.friction = 1.0f;
    b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
}

void Ground::draw() {
    b2Vec2 p = b2Body_GetWorldPoint(bodyId, {-extent.x, extent.y});

    DrawRectangle(p.x * PPM, -p.y * PPM, extent.x * 2 * PPM, extent.y * 2 * PPM, GetColor(0x8095b9));
}