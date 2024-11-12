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
    BodyPart thigh;
    BodyPart shin;
    BodyPart foot;
    BodyPart upper_arm;
    BodyPart lower_arm;

    b2JointId hipJointId;
    b2JointId kneeJointId;
    b2JointId ankleJointId;
    b2JointId shoulderJointId;
    b2JointId elbowJointId;

    Psik(b2WorldId b2WorldId);
    void draw();

    void set_joint_angle(b2JointId jointId, float angle, float speed);
};