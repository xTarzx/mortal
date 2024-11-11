#pragma once
#include "common.h"
#include "psik.h"

class Pose {
   public:
    float hip_angle;
    float hip_force;

    float knee_angle;
    float knee_force;

    float ankle_angle;
    float ankle_force;

    float shoulder_angle;
    float shoulder_force;

    float elbow_angle;
    float elbow_force;
};

namespace Poses {
const Pose standing = {
    .hip_angle = HIP_UPPER_ANGLE * 0.11f,
    .hip_force = 10.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .knee_force = 10.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE * 0.0005f,
    .ankle_force = 6.0f,

    .shoulder_angle = SHOULDER_LOWER_ANGLE * 0.2f,
    .shoulder_force = 10.0f,

    .elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .elbow_force = 10.0f,
};

const Pose jump_prep = {
    .hip_angle = HIP_UPPER_ANGLE * 0.8f,
    .hip_force = 7.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.6f,
    .knee_force = 10.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE,
    .ankle_force = 10.0f,

    .shoulder_angle = 0.0f,
    .shoulder_force = 0.0f,
    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};

const Pose jump = {
    .hip_angle = HIP_LOWER_ANGLE * 0.2f,
    .hip_force = 100.0f,

    .knee_angle = KNEE_UPPER_ANGLE,
    .knee_force = 30.0f,

    .ankle_angle = ANKLE_LOWER_ANGLE,
    .ankle_force = 100.0f,

    .shoulder_angle = 0.0f,
    .shoulder_force = 0.0f,
    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};
const Pose tuck = {
    .hip_angle = HIP_UPPER_ANGLE,
    .hip_force = 50.0f,

    .knee_angle = KNEE_LOWER_ANGLE * 0.9f,
    .knee_force = 30.0f,

    .ankle_angle = ANKLE_UPPER_ANGLE * 0.001f,
    .ankle_force = 30.0f,

    .shoulder_angle = 0.0f,
    .shoulder_force = 0.0f,
    .elbow_angle = 0.0f,
    .elbow_force = 0.0f,
};

}  // namespace Poses

struct KF {
    Pose pose;
    int frame_dur;
};

class Poser {
   public:
    KF *kfs;
    int kfc;
    int kf;

    Psik *target;
    int frame;

    Poser(Psik *target, KF *kfs, int kfc);
    void update();

    void apply_pose(Pose pose);

    void next_kf();

    void reset();
};