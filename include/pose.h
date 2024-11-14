#pragma once
#include "common.h"
#include "psik.h"
#include <vector>

class Pose {
   public:
    float r_hip_angle;
    float r_hip_force;

    float l_hip_angle;
    float l_hip_force;

    float r_knee_angle;
    float r_knee_force;

    float l_knee_angle;
    float l_knee_force;

    float r_ankle_angle;
    float r_ankle_force;

    float l_ankle_angle;
    float l_ankle_force;

    float r_shoulder_angle;
    float r_shoulder_force;

    float l_shoulder_angle;
    float l_shoulder_force;

    float r_elbow_angle;
    float r_elbow_force;

    float l_elbow_angle;
    float l_elbow_force;
};

struct KF {
    Pose pose;
    int frame_dur;
};

class Poser {
   public:
    std::vector<KF> kfs;
    int kf;

    Psik *target;
    int frame;

    bool play;

    Poser(Psik *target, std::vector<KF> kfs);
    void update();

    void apply_pose(Pose pose);

    void next_kf();

    void reset();
};