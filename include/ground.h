#pragma once

#include "box2d/box2d.h"

struct Ground {
    b2BodyId bodyId;
    b2Vec2 extent;

    Ground(b2WorldId worldId);
    Ground() = default;

    void draw();
};