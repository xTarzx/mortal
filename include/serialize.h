#pragma once

#include "pose.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

json serialize_pose(Pose pose);
json serialize_keyframe(KF kf);

Pose deserialize_pose(json j);
KF deserialize_keyframe(json j);