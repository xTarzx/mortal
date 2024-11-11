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