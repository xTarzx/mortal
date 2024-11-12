#pragma once
#include <box2d/box2d.h>

class BodyPart {
   public:
    b2BodyId id;
    b2Vec2 extent;

    BodyPart();
    BodyPart(b2WorldId worldId, b2Vec2 position, b2Vec2 extent, float weight);
};

class Psik {
   public:
    BodyPart torso;
    BodyPart head;
    BodyPart r_thigh;
    BodyPart l_thigh;
    BodyPart r_shin;
    BodyPart l_shin;
    BodyPart r_foot;
    BodyPart l_foot;
    BodyPart r_upper_arm;
    BodyPart r_lower_arm;
    BodyPart l_upper_arm;
    BodyPart l_lower_arm;

    b2JointId r_hipJointId;
    b2JointId l_hipJointId;

    b2JointId r_kneeJointId;
    b2JointId l_kneeJointId;
    b2JointId r_ankleJointId;
    b2JointId l_ankleJointId;

    b2JointId r_shoulderJointId;
    b2JointId r_elbowJointId;

    b2JointId l_shoulderJointId;
    b2JointId l_elbowJointId;

    Psik(b2WorldId b2WorldId);
    void draw();

    void set_joint_angle(b2JointId jointId, float angle, float speed);
};