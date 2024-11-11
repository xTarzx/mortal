#include <raylib.h>
#include "common.h"
#include "psik.h"

Psik::Psik(b2WorldId worldId) {
    float weight = 64.0f;

    // torso
    float torso_w = 0.19f;
    float torso_h = 0.53f;
    torsoExtent = {torso_w * 0.5f, torso_h * 0.5f};

    b2BodyDef torsoBodyDef = b2DefaultBodyDef();
    torsoBodyDef.type = b2_dynamicBody;
    torsoBodyDef.position = {0.0f, 2.78f};

    torsoId = b2CreateBody(worldId, &torsoBodyDef);

    b2Polygon torso = b2MakeBox(
        torsoExtent.x,  // hx
        torsoExtent.y   // hy
    );

    b2ShapeDef torsoShapeDef = b2DefaultShapeDef();
    torsoShapeDef.density = (weight * 0.48f) / (torso_w * torso_h);
    torsoShapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(torsoId, &torsoShapeDef, &torso);

    // head
    float head_w = 0.13f;
    float head_h = 0.20f;
    headExtent = {head_w * 0.5f, head_h * 0.5f};

    b2BodyDef headBodyDef = b2DefaultBodyDef();
    headBodyDef.type = b2_dynamicBody;
    headBodyDef.position.x = 0.1f;
    headBodyDef.position.y = torsoBodyDef.position.y + head_h;

    headId = b2CreateBody(worldId, &headBodyDef);

    b2Polygon head = b2MakeBox(headExtent.x, headExtent.y);

    b2ShapeDef headShapeDef = b2DefaultShapeDef();
    headShapeDef.density = (weight * 0.08f) / (head_w * head_h);
    headShapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(headId, &headShapeDef, &head);

    // thigh

    float thigh_w = torso_w * 0.8f;
    float thigh_h = 0.37f;
    thighExtent = {thigh_w * 0.5f, thigh_h * 0.5f};

    b2BodyDef thighBodyDef = b2DefaultBodyDef();
    thighBodyDef.type = b2_dynamicBody;
    thighBodyDef.position.y = torsoBodyDef.position.y - torso_h - thigh_h;

    thighId = b2CreateBody(worldId, &thighBodyDef);

    b2Polygon thigh = b2MakeBox(thighExtent.x, thighExtent.y);

    b2ShapeDef thighShapeDef = b2DefaultShapeDef();
    thighShapeDef.density = (weight * 0.22f) / (thigh_w * thigh_h);
    thighShapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(thighId, &thighShapeDef, &thigh);

    // shin

    float shin_w = thigh_w * 0.8f;
    float shin_h = 0.36f;
    shinExtent = {shin_w * 0.5f, shin_h * 0.5f};

    b2BodyDef shinBodyDef = b2DefaultBodyDef();
    shinBodyDef.type = b2_dynamicBody;
    shinBodyDef.position.y = thighBodyDef.position.y - shinExtent.y;

    shinId = b2CreateBody(worldId, &shinBodyDef);

    b2Polygon shin = b2MakeBox(shinExtent.x, shinExtent.y);

    b2ShapeDef shinShapeDef = b2DefaultShapeDef();
    shinShapeDef.density = (weight * 0.10f) / (shin_w * shin_h);
    shinShapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(shinId, &shinShapeDef, &shin);

    // foot

    float foot_w = 0.26f;
    float foot_h = 0.06f;
    footExtent = {foot_w * 0.5f, foot_h * 0.5f};

    b2BodyDef footBodyDef = b2DefaultBodyDef();
    footBodyDef.type = b2_dynamicBody;
    footBodyDef.position.y = shinBodyDef.position.y - shinExtent.y - footExtent.y;

    footId = b2CreateBody(worldId, &footBodyDef);

    b2Polygon foot = b2MakeBox(footExtent.x, footExtent.y);

    b2ShapeDef footShapeDef = b2DefaultShapeDef();
    footShapeDef.density = (weight * 0.035f) / (foot_w * foot_h);
    footShapeDef.friction = 1.0f;
    footShapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(footId, &footShapeDef, &foot);

    // upper arm

    float upperArm_w = 0.05f;
    float upperArm_h = 0.35f;
    upperArmExtent = {upperArm_w * 0.5f, upperArm_h * 0.5f};

    b2BodyDef upperArmBodyDef = b2DefaultBodyDef();
    upperArmBodyDef.type = b2_dynamicBody;
    upperArmBodyDef.position.y = torsoBodyDef.position.y;

    upperArmId = b2CreateBody(worldId, &upperArmBodyDef);

    b2Polygon upperArm = b2MakeBox(upperArmExtent.x, upperArmExtent.y);

    b2ShapeDef upperArmShapeDef = b2DefaultShapeDef();
    upperArmShapeDef.density = (weight * 0.047f) / (upperArm_w * upperArm_h);
    upperArmShapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(upperArmId, &upperArmShapeDef, &upperArm);

    // lower arm

    float lowerArm_w = 0.043f;
    float lowerArm_h = 0.29f;
    lowerArmExtent = {lowerArm_w * 0.5f, lowerArm_h * 0.5f};

    b2BodyDef lowerArmBodyDef = b2DefaultBodyDef();
    lowerArmBodyDef.type = b2_dynamicBody;
    lowerArmBodyDef.position.y = torsoBodyDef.position.y;

    lowerArmId = b2CreateBody(worldId, &lowerArmBodyDef);

    b2Polygon lowerArm = b2MakeBox(lowerArmExtent.x, lowerArmExtent.y);

    b2ShapeDef lowerArmShapeDef = b2DefaultShapeDef();
    lowerArmShapeDef.density = (weight * 0.022f) / (lowerArm_w * lowerArm_h);
    lowerArmShapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(lowerArmId, &lowerArmShapeDef, &lowerArm);

    // neck joint
    b2RevoluteJointDef neck_joint_def = b2DefaultRevoluteJointDef();
    neck_joint_def.bodyIdA = torsoId;
    neck_joint_def.bodyIdB = headId;
    neck_joint_def.localAnchorA = {0.0f, torsoExtent.y};
    neck_joint_def.localAnchorB = {0.0f, -headExtent.y};
    neck_joint_def.lowerAngle = 0.0f;
    neck_joint_def.upperAngle = 0.0f;
    neck_joint_def.enableLimit = true;
    b2CreateRevoluteJoint(worldId, &neck_joint_def);

    // hip joint
    b2RevoluteJointDef hip_joint_def = b2DefaultRevoluteJointDef();
    hip_joint_def.bodyIdA = torsoId;
    hip_joint_def.bodyIdB = thighId;
    hip_joint_def.localAnchorA = {0.0f, -torsoExtent.y};
    hip_joint_def.localAnchorB = {0.0f, thighExtent.y};
    hip_joint_def.lowerAngle = HIP_LOWER_ANGLE;
    hip_joint_def.upperAngle = HIP_UPPER_ANGLE;
    hip_joint_def.enableLimit = true;
    hip_joint_def.maxMotorTorque = 250.0f;
    hip_joint_def.motorSpeed = 0.0f;
    hip_joint_def.enableMotor = true;

    hipJointId = b2CreateRevoluteJoint(worldId, &hip_joint_def);

    // knee joint
    b2RevoluteJointDef knee_joint_def = b2DefaultRevoluteJointDef();
    knee_joint_def.bodyIdA = thighId;
    knee_joint_def.bodyIdB = shinId;
    knee_joint_def.localAnchorA = {0.0f, -thighExtent.y};
    knee_joint_def.localAnchorB = {0.0f, shinExtent.y};
    knee_joint_def.lowerAngle = KNEE_LOWER_ANGLE;
    knee_joint_def.upperAngle = KNEE_UPPER_ANGLE;
    knee_joint_def.enableLimit = true;
    knee_joint_def.maxMotorTorque = 250.0f;
    knee_joint_def.motorSpeed = 0.0f;
    knee_joint_def.enableMotor = true;

    kneeJointId = b2CreateRevoluteJoint(worldId, &knee_joint_def);

    // ankle joint
    b2RevoluteJointDef ankle_joint_def = b2DefaultRevoluteJointDef();
    ankle_joint_def.bodyIdA = shinId;
    ankle_joint_def.bodyIdB = footId;
    ankle_joint_def.localAnchorA = {-shinExtent.x, -shinExtent.y};
    ankle_joint_def.localAnchorB = {-shinExtent.x * 1.6f, footExtent.y};
    ankle_joint_def.lowerAngle = ANKLE_LOWER_ANGLE;
    ankle_joint_def.upperAngle = ANKLE_UPPER_ANGLE;
    ankle_joint_def.enableLimit = true;
    ankle_joint_def.dampingRatio = 1.0f;
    ankle_joint_def.maxMotorTorque = 200.0f;
    ankle_joint_def.motorSpeed = 0.0f;
    ankle_joint_def.enableMotor = true;

    ankleJointId = b2CreateRevoluteJoint(worldId, &ankle_joint_def);

    // shoulder joint
    b2RevoluteJointDef shoulder_joint_def = b2DefaultRevoluteJointDef();
    shoulder_joint_def.bodyIdA = torsoId;
    shoulder_joint_def.bodyIdB = upperArmId;
    shoulder_joint_def.localAnchorA = {0.0f, torsoExtent.y * 0.8f};
    shoulder_joint_def.localAnchorB = {0.0f, upperArmExtent.y * 0.9f};
    shoulder_joint_def.lowerAngle = SHOULDER_LOWER_ANGLE;
    shoulder_joint_def.upperAngle = SHOULDER_UPPER_ANGLE;
    shoulder_joint_def.enableLimit = true;
    shoulder_joint_def.maxMotorTorque = 200.0f;
    shoulder_joint_def.motorSpeed = 0.0f;
    shoulder_joint_def.enableMotor = true;

    shoulderJointId = b2CreateRevoluteJoint(worldId, &shoulder_joint_def);

    // elbow joint
    b2RevoluteJointDef elbow_joint_def = b2DefaultRevoluteJointDef();
    elbow_joint_def.bodyIdA = upperArmId;
    elbow_joint_def.bodyIdB = lowerArmId;
    elbow_joint_def.localAnchorA = {0.0f, -upperArmExtent.y * 0.9f};
    elbow_joint_def.localAnchorB = {0.0f, lowerArmExtent.y * 0.9f};
    elbow_joint_def.lowerAngle = ELBOW_LOWER_ANGLE;
    elbow_joint_def.upperAngle = ELBOW_UPPER_ANGLE;
    elbow_joint_def.enableLimit = true;
    elbow_joint_def.maxMotorTorque = 200.0f;
    elbow_joint_def.motorSpeed = 0.0f;
    elbow_joint_def.enableMotor = true;

    elbowJointId = b2CreateRevoluteJoint(worldId, &elbow_joint_def);
}

void Psik::draw() {
    // torso
    b2Vec2 torso_p = b2Body_GetWorldPoint(torsoId, {-torsoExtent.x, torsoExtent.y});
    b2Rot torso_rotation = b2Body_GetRotation(torsoId);
    float torso_angle = b2Rot_GetAngle(torso_rotation);

    Rectangle torso_rec = {torso_p.x * PPM, -torso_p.y * PPM, torsoExtent.x * 2 * PPM, torsoExtent.y * 2 * PPM};
    DrawRectanglePro(torso_rec, {0.0f, 0.0f}, -torso_angle * RAD2DEG, DARKBLUE);

    // head
    b2Vec2 head_p = b2Body_GetWorldPoint(headId, {-headExtent.x, headExtent.y});
    b2Rot head_rotation = b2Body_GetRotation(headId);
    float head_angle = b2Rot_GetAngle(head_rotation);

    Rectangle head_rec = {head_p.x * PPM, -head_p.y * PPM, headExtent.x * 2 * PPM, headExtent.y * 2 * PPM};
    DrawRectanglePro(head_rec, {0.0f, 0.0f}, -head_angle * RAD2DEG, BLUE);

    // thigh
    b2Vec2 thigh_p = b2Body_GetWorldPoint(thighId, {-thighExtent.x, thighExtent.y});
    b2Rot thigh_rotation = b2Body_GetRotation(thighId);
    float thigh_angle = b2Rot_GetAngle(thigh_rotation);

    Rectangle thigh_rec = {thigh_p.x * PPM, -thigh_p.y * PPM, thighExtent.x * 2 * PPM, thighExtent.y * 2 * PPM};
    DrawRectanglePro(thigh_rec, {0.0f, 0.0f}, -thigh_angle * RAD2DEG, BLUE);

    // shin
    b2Vec2 shin_p = b2Body_GetWorldPoint(shinId, {-shinExtent.x, shinExtent.y});
    b2Rot shin_rotation = b2Body_GetRotation(shinId);
    float shin_angle = b2Rot_GetAngle(shin_rotation);

    Rectangle shin_rec = {shin_p.x * PPM, -shin_p.y * PPM, shinExtent.x * 2 * PPM, shinExtent.y * 2 * PPM};
    DrawRectanglePro(shin_rec, {0.0f, 0.0f}, -shin_angle * RAD2DEG, DARKBLUE);

    // foot

    b2Vec2 foot_p = b2Body_GetWorldPoint(footId, {-footExtent.x, footExtent.y});
    b2Rot foot_rotation = b2Body_GetRotation(footId);
    float foot_angle = b2Rot_GetAngle(foot_rotation);

    Rectangle foot_rec = {foot_p.x * PPM, -foot_p.y * PPM, footExtent.x * 2 * PPM, footExtent.y * 2 * PPM};
    DrawRectanglePro(foot_rec, {0.0f, 0.0f}, -foot_angle * RAD2DEG, DARKBLUE);

    // upper arm
    b2Vec2 upper_arm_p = b2Body_GetWorldPoint(upperArmId, {-upperArmExtent.x, upperArmExtent.y});
    b2Rot upper_arm_rotation = b2Body_GetRotation(upperArmId);
    float upper_arm_angle = b2Rot_GetAngle(upper_arm_rotation);

    Rectangle upper_arm_rec = {upper_arm_p.x * PPM, -upper_arm_p.y * PPM, upperArmExtent.x * 2 * PPM, upperArmExtent.y * 2 * PPM};
    DrawRectanglePro(upper_arm_rec, {0.0f, 0.0f}, -upper_arm_angle * RAD2DEG, BLUE);

    // lower arm
    b2Vec2 lower_arm_p = b2Body_GetWorldPoint(lowerArmId, {-lowerArmExtent.x, lowerArmExtent.y});
    b2Rot lower_arm_rotation = b2Body_GetRotation(lowerArmId);
    float lower_arm_angle = b2Rot_GetAngle(lower_arm_rotation);

    Rectangle lower_arm_rec = {lower_arm_p.x * PPM, -lower_arm_p.y * PPM, lowerArmExtent.x * 2 * PPM, lowerArmExtent.y * 2 * PPM};
    DrawRectanglePro(lower_arm_rec, {0.0f, 0.0f}, -lower_arm_angle * RAD2DEG, PURPLE);
};

void Psik::set_joint_angle(b2JointId jointId, float angle, float speed) {
    float joint_angle = b2RevoluteJoint_GetAngle(jointId);

    float diff = angle - joint_angle;
    b2Joint_WakeBodies(jointId);
    b2RevoluteJoint_SetMotorSpeed(jointId, speed * diff);
};
