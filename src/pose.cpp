#include "pose.h"
#include <cassert>

Poser::Poser(Psik* target, KF* kfs, int kfc) {
    this->target = target;
    this->kfs = kfs;
    this->kfc = kfc;

    assert(kfc > 0 && "where chicken?");

    frame = 0;
    kf = 0;
};

void Poser::reset() {
    kf = 0;
    frame = 0;
}

void Poser::next_kf() {
    kf++;
    kf %= kfc;
    frame = 0;
}

void Poser::update() {
    apply_pose(kfs[kf].pose);

    int frame_dur = kfs[kf].frame_dur;

    if (frame_dur > 0) {
        frame++;

        if (frame >= frame_dur) next_kf();
    }
}

void Poser::apply_pose(Pose pose) {
    float hip_target_angle = std::max(std::min(pose.hip_angle, HIP_UPPER_ANGLE), HIP_LOWER_ANGLE);
    target->set_joint_angle(target->hipJointId, hip_target_angle, pose.hip_force);

    float knee_target_angle = std::max(std::min(pose.knee_angle, KNEE_UPPER_ANGLE), KNEE_LOWER_ANGLE);
    target->set_joint_angle(target->kneeJointId, knee_target_angle, pose.knee_force);

    float ankle_target_angle = std::max(std::min(pose.ankle_angle, ANKLE_UPPER_ANGLE), ANKLE_LOWER_ANGLE);
    target->set_joint_angle(target->ankleJointId, ankle_target_angle, pose.ankle_force);

    float shoulder_target_angle = std::max(std::min(pose.shoulder_angle, SHOULDER_UPPER_ANGLE), SHOULDER_LOWER_ANGLE);
    target->set_joint_angle(target->shoulderJointId, shoulder_target_angle, pose.shoulder_force);

    float elbow_target_angle = std::max(std::min(pose.elbow_angle, ELBOW_UPPER_ANGLE), ELBOW_LOWER_ANGLE);
    target->set_joint_angle(target->elbowJointId, elbow_target_angle, pose.elbow_force);
}
