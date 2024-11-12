#pragma once
#include "pose.h"

namespace Poses {
const Pose zero = {
    .hip_angle = 0.0f,
    .hip_force = 0.0f,

    .knee_angle = 0.0f,
    .knee_force = 0.0f,

    .ankle_angle = 0.0f,
    .ankle_force = 0.0f,

    .shoulder_angle = 0.0f,
    .shoulder_force = 0.0f,

    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};

const Pose standing = {
    .hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .hip_force = 10.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .knee_force = 10.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .ankle_force = 3.0f,

    .shoulder_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .shoulder_force = 10.0f,

    .elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .elbow_force = 10.0f,
};
const Pose standing_rlx = {
    .hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .hip_force = 10.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .knee_force = 10.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .ankle_force = 0.0f,

    .shoulder_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .shoulder_force = 10.0f,

    .elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .elbow_force = 10.0f,
};

const Pose jump_prep = {
    .hip_angle = HIP_UPPER_ANGLE * 0.73f,
    .hip_force = 7.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.55f,
    .knee_force = 8.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE,
    .ankle_force = 5.0f,

    .shoulder_angle = SHOULDER_LOWER_ANGLE,
    .shoulder_force = 10.0f,

    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};

const Pose prep_swing = {
    .hip_angle = HIP_LOWER_ANGLE,
    .hip_force = 4.0f,

    .knee_angle = 0.0f,
    .knee_force = 0.0f,

    .ankle_angle = 0.0f,
    .ankle_force = 0.0f,

    .shoulder_angle = SHOULDER_UPPER_ANGLE,
    .shoulder_force = 8.0f,

    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};

const Pose jump0 = {
    .hip_angle = HIP_LOWER_ANGLE,
    .hip_force = 13.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.55f,
    .knee_force = 5.8f,

    .ankle_angle = 0.0f,
    .ankle_force = 0.0f,

    .shoulder_angle = SHOULDER_UPPER_ANGLE,
    .shoulder_force = 8.0f,

    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};

const Pose jump = {
    .hip_angle = HIP_LOWER_ANGLE,
    .hip_force = 50.0f,

    .knee_angle = KNEE_UPPER_ANGLE,
    .knee_force = 20.0f,

    .ankle_angle = ANKLE_LOWER_ANGLE,
    .ankle_force = 80.0f,

    .shoulder_angle = SHOULDER_UPPER_ANGLE,
    .shoulder_force = 12.0f,

    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};
const Pose tuck = {
    .hip_angle = HIP_UPPER_ANGLE,
    .hip_force = 15.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.85f,
    .knee_force = 8.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE,
    .ankle_force = 7.0f,

    .shoulder_angle = SHOULDER_LOWER_ANGLE * 0.15f,
    .shoulder_force = 12.0f,

    .elbow_angle = ELBOW_UPPER_ANGLE * 0.55f,
    .elbow_force = 6.0f,
};

const Pose pike = {
    .hip_angle = HIP_UPPER_ANGLE,
    .hip_force = 15.0f,

    .knee_angle = KNEE_UPPER_ANGLE * 0.85f,
    .knee_force = 8.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE,
    .ankle_force = 7.0f,

    .shoulder_angle = SHOULDER_LOWER_ANGLE * 0.15f,
    .shoulder_force = 12.0f,

    .elbow_angle = ELBOW_UPPER_ANGLE * 0.55f,
    .elbow_force = 6.0f,
};

const Pose land0 = {
    .hip_angle = 0.0f,
    .hip_force = 0.0f,

    .knee_angle = KNEE_UPPER_ANGLE * 0.45f,
    .knee_force = 10.0f,

    .ankle_angle = 0.0f,
    .ankle_force = 0.0f,

    .shoulder_angle = SHOULDER_UPPER_ANGLE * 0.4f,
    .shoulder_force = 8.0f,

    .elbow_angle = ELBOW_LOWER_ANGLE * 0.98f,
    .elbow_force = 4.0f,
};

const Pose land = {
    .hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .hip_force = 10.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .knee_force = 10.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE * 0.05f,
    .ankle_force = 5.0f,

    .shoulder_angle = SHOULDER_UPPER_ANGLE * 0.5f,
    .shoulder_force = 10.0f,

    .elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .elbow_force = 10.0f,
};

}  // namespace Poses
