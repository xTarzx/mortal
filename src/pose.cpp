#include "pose.h"
#include <cassert>

Poser::Poser(Psik* target, std::vector<KF> kfs) {
    this->target = target;
    this->kfs = kfs;

    frame = 0;
    kf = 0;

    play = true;
};

void Poser::reset() {
    kf = 0;
    frame = 0;
}

void Poser::next_kf() {
    if (kfs.size() == 0) return;
    kf++;
    kf %= kfs.size();
    frame = 0;
}

void Poser::prev_kf() {
    if (kfs.size() == 0) return;
    kf--;
    if (kf < 0) {
        kf = kfs.size() - 1;
    }
    frame = 0;
}

void Poser::update() {
    if (kfs.size() == 0) return;
    apply_pose(kfs[kf].pose);

    if (!play) return;

    int frame_dur = kfs[kf].frame_dur;

    if (frame_dur > 0) {
        frame++;

        if (frame >= frame_dur) next_kf();
    }
}

void Poser::apply_pose(Pose pose) {
    float r_hip_target_angle = std::max(std::min(pose.r_hip_angle, HIP_UPPER_ANGLE), HIP_LOWER_ANGLE);
    target->set_joint_angle(target->r_hipJointId, r_hip_target_angle, pose.r_hip_force);

    float l_hip_target_angle = std::max(std::min(pose.l_hip_angle, HIP_UPPER_ANGLE), HIP_LOWER_ANGLE);
    target->set_joint_angle(target->l_hipJointId, l_hip_target_angle, pose.l_hip_force);

    float r_knee_target_angle = std::max(std::min(pose.r_knee_angle, KNEE_UPPER_ANGLE), KNEE_LOWER_ANGLE);
    target->set_joint_angle(target->r_kneeJointId, r_knee_target_angle, pose.r_knee_force);

    float l_knee_target_angle = std::max(std::min(pose.l_knee_angle, KNEE_UPPER_ANGLE), KNEE_LOWER_ANGLE);
    target->set_joint_angle(target->l_kneeJointId, l_knee_target_angle, pose.l_knee_force);

    float r_ankle_target_angle = std::max(std::min(pose.r_ankle_angle, ANKLE_UPPER_ANGLE), ANKLE_LOWER_ANGLE);
    target->set_joint_angle(target->r_ankleJointId, r_ankle_target_angle, pose.r_ankle_force);

    float l_ankle_target_angle = std::max(std::min(pose.l_ankle_angle, ANKLE_UPPER_ANGLE), ANKLE_LOWER_ANGLE);
    target->set_joint_angle(target->l_ankleJointId, l_ankle_target_angle, pose.l_ankle_force);

    float r_shoulder_target_angle = std::max(std::min(pose.r_shoulder_angle, SHOULDER_UPPER_ANGLE), SHOULDER_LOWER_ANGLE);
    target->set_joint_angle(target->r_shoulderJointId, r_shoulder_target_angle, pose.r_shoulder_force);

    float l_shoulder_target_angle = std::max(std::min(pose.l_shoulder_angle, SHOULDER_UPPER_ANGLE), SHOULDER_LOWER_ANGLE);
    target->set_joint_angle(target->l_shoulderJointId, l_shoulder_target_angle, pose.l_shoulder_force);

    float r_elbow_target_angle = std::max(std::min(pose.r_elbow_angle, ELBOW_UPPER_ANGLE), ELBOW_LOWER_ANGLE);
    target->set_joint_angle(target->r_elbowJointId, r_elbow_target_angle, pose.r_elbow_force);

    float l_elbow_target_angle = std::max(std::min(pose.l_elbow_angle, ELBOW_UPPER_ANGLE), ELBOW_LOWER_ANGLE);
    target->set_joint_angle(target->l_elbowJointId, l_elbow_target_angle, pose.l_elbow_force);
}
