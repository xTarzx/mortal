#pragma once
#include "pose.h"

namespace Poses {
const Pose zero = {
    .r_hip_angle = 0.0f,
    .r_hip_force = 0.0f,

    .l_hip_angle = 0.0f,
    .l_hip_force = 0.0f,

    .r_knee_angle = 0.0f,
    .r_knee_force = 0.0f,
    .l_knee_angle = 0.0f,
    .l_knee_force = 0.0f,

    .r_ankle_angle = 0.0f,
    .r_ankle_force = 0.0f,
    .l_ankle_angle = 0.0f,
    .l_ankle_force = 0.0f,

    .r_shoulder_angle = 0.0f,
    .r_shoulder_force = 0.0f,

    .l_shoulder_angle = 0.0f,
    .l_shoulder_force = 0.0f,

    .r_elbow_angle = 0.0f,
    .r_elbow_force = 0.0f,

    .l_elbow_angle = 0.0f,
    .l_elbow_force = 0.0f,
};

const Pose standing = {
    .r_hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .r_hip_force = 10.0f,
    .l_hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .l_hip_force = 10.0f,

    .r_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .r_knee_force = 10.0f,
    .l_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .l_knee_force = 10.0f,

    .r_ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .r_ankle_force = 3.0f,
    .l_ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .l_ankle_force = 3.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .r_shoulder_force = 10.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .l_shoulder_force = 10.0f,

    .r_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .r_elbow_force = 10.0f,

    .l_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .l_elbow_force = 10.0f,

};

const Pose standing_rlx = {
    .r_hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .r_hip_force = 10.0f,
    .l_hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .l_hip_force = 10.0f,

    .r_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .r_knee_force = 10.0f,
    .l_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .l_knee_force = 10.0f,

    .r_ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .r_ankle_force = 0.0f,
    .l_ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .l_ankle_force = 0.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .r_shoulder_force = 10.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .l_shoulder_force = 10.0f,

    .r_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .r_elbow_force = 10.0f,

    .l_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .l_elbow_force = 10.0f,
};
const Pose standing_rlx_arms = {
    .r_hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .r_hip_force = 10.0f,
    .l_hip_angle = HIP_UPPER_ANGLE * 0.55f,
    .l_hip_force = 10.0f,

    .r_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .r_knee_force = 10.0f,
    .l_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .l_knee_force = 10.0f,

    .r_ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .r_ankle_force = 0.0f,
    .l_ankle_angle = ANKLE_UPPER_ANGLE * 0.81f,
    .l_ankle_force = 0.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .r_shoulder_force = 10.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.48f,
    .l_shoulder_force = 10.0f,

    .r_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .r_elbow_force = 10.0f,

    .l_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .l_elbow_force = 10.0f,
};

const Pose jump_prep = {
    .r_hip_angle = HIP_UPPER_ANGLE * 0.73f,
    .r_hip_force = 7.0f,
    .l_hip_angle = HIP_UPPER_ANGLE * 0.73f,
    .l_hip_force = 7.0f,

    .r_knee_angle = KNEE_LOWER_ANGLE * 0.55f,
    .r_knee_force = 8.0f,
    .l_knee_angle = KNEE_LOWER_ANGLE * 0.55f,
    .l_knee_force = 8.0f,

    .r_ankle_angle = ANKLE_UPPER_ANGLE,
    .r_ankle_force = 5.0f,
    .l_ankle_angle = ANKLE_UPPER_ANGLE,
    .l_ankle_force = 5.0f,

    .r_shoulder_angle = SHOULDER_LOWER_ANGLE,
    .r_shoulder_force = 10.0f,

    .l_shoulder_angle = SHOULDER_LOWER_ANGLE,
    .l_shoulder_force = 10.0f,

    .r_elbow_angle = 0.0f,
    .r_elbow_force = 0.0f,

    .l_elbow_angle = 0.0f,
    .l_elbow_force = 0.0f,
};

const Pose prep_swing = {
    .r_hip_angle = HIP_LOWER_ANGLE,
    .r_hip_force = 4.0f,
    .l_hip_angle = HIP_LOWER_ANGLE,
    .l_hip_force = 4.0f,

    .r_knee_angle = 0.0f,
    .r_knee_force = 0.0f,
    .l_knee_angle = 0.0f,
    .l_knee_force = 0.0f,

    .r_ankle_angle = 0.0f,
    .r_ankle_force = 0.0f,
    .l_ankle_angle = 0.0f,
    .l_ankle_force = 0.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE,
    .r_shoulder_force = 8.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE,
    .l_shoulder_force = 8.0f,

    .r_elbow_angle = 0.0f,
    .r_elbow_force = 0.0f,

    .l_elbow_angle = 0.0f,
    .l_elbow_force = 0.0f,
};

const Pose jump0 = {
    .r_hip_angle = HIP_LOWER_ANGLE,
    .r_hip_force = 13.0f,
    .l_hip_angle = HIP_LOWER_ANGLE,
    .l_hip_force = 13.0f,

    .r_knee_angle = KNEE_LOWER_ANGLE * 0.55f,
    .r_knee_force = 5.8f,
    .l_knee_angle = KNEE_LOWER_ANGLE * 0.55f,
    .l_knee_force = 5.8f,

    .r_ankle_angle = 0.0f,
    .r_ankle_force = 0.0f,
    .l_ankle_angle = 0.0f,
    .l_ankle_force = 0.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE,
    .r_shoulder_force = 8.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE,
    .l_shoulder_force = 8.0f,

    .r_elbow_angle = 0.0f,
    .r_elbow_force = 0.0f,

    .l_elbow_angle = 0.0f,
    .l_elbow_force = 0.0f,
};

const Pose jump = {
    .r_hip_angle = HIP_LOWER_ANGLE,
    .r_hip_force = 50.0f,
    .l_hip_angle = HIP_LOWER_ANGLE,
    .l_hip_force = 50.0f,

    .r_knee_angle = KNEE_UPPER_ANGLE,
    .r_knee_force = 20.0f,
    .l_knee_angle = KNEE_UPPER_ANGLE,
    .l_knee_force = 20.0f,

    .r_ankle_angle = ANKLE_LOWER_ANGLE,
    .r_ankle_force = 80.0f,
    .l_ankle_angle = ANKLE_LOWER_ANGLE,
    .l_ankle_force = 80.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE,
    .r_shoulder_force = 12.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE,
    .l_shoulder_force = 12.0f,

    .r_elbow_angle = 0.0f,
    .r_elbow_force = 0.0f,

    .l_elbow_angle = 0.0f,
    .l_elbow_force = 0.0f,
};
const Pose tuck = {
    .r_hip_angle = HIP_UPPER_ANGLE,
    .r_hip_force = 15.0f,
    .l_hip_angle = HIP_UPPER_ANGLE,
    .l_hip_force = 15.0f,

    .r_knee_angle = KNEE_LOWER_ANGLE * 0.85f,
    .r_knee_force = 8.0f,
    .l_knee_angle = KNEE_LOWER_ANGLE * 0.85f,
    .l_knee_force = 8.0f,

    .r_ankle_angle = ANKLE_UPPER_ANGLE,
    .r_ankle_force = 7.0f,
    .l_ankle_angle = ANKLE_UPPER_ANGLE,
    .l_ankle_force = 7.0f,

    .r_shoulder_angle = SHOULDER_LOWER_ANGLE * 0.15f,
    .r_shoulder_force = 12.0f,

    .l_shoulder_angle = SHOULDER_LOWER_ANGLE * 0.15f,
    .l_shoulder_force = 12.0f,

    .r_elbow_angle = ELBOW_UPPER_ANGLE * 0.55f,
    .r_elbow_force = 6.0f,

    .l_elbow_angle = ELBOW_UPPER_ANGLE * 0.55f,
    .l_elbow_force = 6.0f,
};

const Pose pike = {
    .r_hip_angle = HIP_UPPER_ANGLE,
    .r_hip_force = 15.0f,
    .l_hip_angle = HIP_UPPER_ANGLE,
    .l_hip_force = 15.0f,

    .r_knee_angle = KNEE_UPPER_ANGLE * 0.85f,
    .r_knee_force = 8.0f,
    .l_knee_angle = KNEE_UPPER_ANGLE * 0.85f,
    .l_knee_force = 8.0f,

    .r_ankle_angle = ANKLE_UPPER_ANGLE,
    .r_ankle_force = 7.0f,
    .l_ankle_angle = ANKLE_UPPER_ANGLE,
    .l_ankle_force = 7.0f,

    .r_shoulder_angle = SHOULDER_LOWER_ANGLE * 0.15f,
    .r_shoulder_force = 12.0f,

    .l_shoulder_angle = SHOULDER_LOWER_ANGLE * 0.15f,
    .l_shoulder_force = 12.0f,

    .r_elbow_angle = ELBOW_UPPER_ANGLE * 0.55f,
    .r_elbow_force = 6.0f,

    .l_elbow_angle = ELBOW_UPPER_ANGLE * 0.55f,
    .l_elbow_force = 6.0f,
};

const Pose land0 = {
    .r_hip_angle = 0.0f,
    .r_hip_force = 0.0f,
    .l_hip_angle = 0.0f,
    .l_hip_force = 0.0f,

    .r_knee_angle = KNEE_UPPER_ANGLE * 0.45f,
    .r_knee_force = 10.0f,
    .l_knee_angle = KNEE_UPPER_ANGLE * 0.45f,
    .l_knee_force = 10.0f,

    .r_ankle_angle = 0.0f,
    .r_ankle_force = 0.0f,
    .l_ankle_angle = 0.0f,
    .l_ankle_force = 0.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.4f,
    .r_shoulder_force = 8.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.4f,
    .l_shoulder_force = 8.0f,

    .r_elbow_angle = ELBOW_LOWER_ANGLE * 0.98f,
    .r_elbow_force = 4.0f,

    .l_elbow_angle = ELBOW_LOWER_ANGLE * 0.98f,
    .l_elbow_force = 4.0f,
};

const Pose land = {
    .r_hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .r_hip_force = 10.0f,
    .l_hip_angle = HIP_UPPER_ANGLE * 0.05f,
    .l_hip_force = 10.0f,

    .r_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .r_knee_force = 10.0f,
    .l_knee_angle = KNEE_LOWER_ANGLE * 0.09f,
    .l_knee_force = 10.0f,

    .r_ankle_angle = ANKLE_UPPER_ANGLE * 0.05f,
    .r_ankle_force = 5.0f,
    .l_ankle_angle = ANKLE_UPPER_ANGLE * 0.05f,
    .l_ankle_force = 5.0f,

    .r_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.5f,
    .r_shoulder_force = 10.0f,

    .l_shoulder_angle = SHOULDER_UPPER_ANGLE * 0.5f,
    .l_shoulder_force = 10.0f,

    .r_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .r_elbow_force = 10.0f,

    .l_elbow_angle = SHOULDER_UPPER_ANGLE * 0.08f,
    .l_elbow_force = 10.0f,
};

}  // namespace Poses
