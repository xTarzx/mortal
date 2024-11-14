#include "serialize.h"

json serialize_pose(Pose pose) {
    json j;

    j["r_hip_angle"] = pose.r_hip_angle;
    j["r_hip_force"] = pose.r_hip_force;
    j["l_hip_angle"] = pose.l_hip_angle;
    j["l_hip_force"] = pose.l_hip_force;
    j["r_knee_angle"] = pose.r_knee_angle;
    j["r_knee_force"] = pose.r_knee_force;
    j["l_knee_angle"] = pose.l_knee_angle;
    j["l_knee_force"] = pose.l_knee_force;
    j["r_ankle_angle"] = pose.r_ankle_angle;
    j["r_ankle_force"] = pose.r_ankle_force;
    j["l_ankle_angle"] = pose.l_ankle_angle;
    j["l_ankle_force"] = pose.l_ankle_force;
    j["r_shoulder_angle"] = pose.r_shoulder_angle;
    j["r_shoulder_force"] = pose.r_shoulder_force;
    j["l_shoulder_angle"] = pose.l_shoulder_angle;
    j["l_shoulder_force"] = pose.l_shoulder_force;
    j["r_elbow_angle"] = pose.r_elbow_angle;
    j["r_elbow_force"] = pose.r_elbow_force;
    j["l_elbow_angle"] = pose.l_elbow_angle;
    j["l_elbow_force"] = pose.l_elbow_force;

    return j;
};

json serialize_keyframe(KF kf) {
    json j;

    j["frame_dur"] = kf.frame_dur;
    j["pose"] = serialize_pose(kf.pose);

    return j;
};
