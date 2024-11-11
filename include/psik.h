#pragma once
#include <box2d/box2d.h>

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

    b2BodyId upperArmId;
    b2Vec2 upperArmExtent;

    b2BodyId lowerArmId;
    b2Vec2 lowerArmExtent;

    b2JointId hipJointId;
    b2JointId kneeJointId;
    b2JointId ankleJointId;
    b2JointId shoulderJointId;
    b2JointId elbowJointId;

    Psik(b2WorldId b2WorldId);
    void draw();

    void set_joint_angle(b2JointId jointId, float angle, float speed);
};