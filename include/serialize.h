#pragma once

#include "pose.h"
#include "json.hpp"

using json = nlohmann::json;

json serialize_pose(Pose pose);
json serialize_keyframe(KF kf);