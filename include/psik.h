#pragma once
#include <box2d/box2d.h>
#include "pose.h"

#define HIP_LOWER_ANGLE (-b2_pi * 0.25f)
#define HIP_UPPER_ANGLE (b2_pi * 0.72f)

#define KNEE_LOWER_ANGLE (-b2_pi * 0.6f)
#define KNEE_UPPER_ANGLE 0.0f

#define ANKLE_LOWER_ANGLE (-b2_pi * 0.15f)
#define ANKLE_UPPER_ANGLE (b2_pi * 0.05f)

class Psik {
   public:
    b2BodyId torsoId;
    b2Vec2 torsoExtent;

    b2BodyId headId;
    b2Vec2 headExtent;

    b2BodyId thighId;
    b2Vec2 thighExtent;

    b2BodyId shinId;
    b2Vec2 shinExtent;

    b2BodyId footId;
    b2Vec2 footExtent;

    b2JointId hipJointId;
    b2JointId kneeJointId;
    b2JointId ankleJointId;

    Psik(b2WorldId b2WorldId);
    void draw();

    void set_joint_angle(b2JointId jointId, float angle, float speed);

    void set_pose(Pose pose);
};