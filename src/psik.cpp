#include <raylib.h>
#include "common.h"
#include "psik.h"

BodyPart::BodyPart() {};

BodyPart::BodyPart(b2WorldId worldId, b2Vec2 position, b2Vec2 extent, float weight) {
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    this->id = b2CreateBody(worldId, &bodyDef);
    this->extent = extent;
    b2Polygon poly = b2MakeBox(extent.x, extent.y);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = weight / ((this->extent.x * 2) * (this->extent.y * 2));
    shapeDef.filter.groupIndex = -Group::PLAYER;
    b2CreatePolygonShape(this->id, &shapeDef, &poly);
}

Psik::Psik(b2WorldId worldId) {
    float weight = 64.0f;

    // torso
    float torso_w = 0.19f;
    float torso_h = 0.53f;
    b2Vec2 torso_ext = {torso_w * 0.5f, torso_h * 0.5f};
    b2Vec2 torso_pos = {0.0f, 2.6f};

    this->torso = BodyPart(worldId, torso_pos, torso_ext, weight * 0.48f);

    // head
    float head_w = 0.13f;
    float head_h = 0.20f;
    b2Vec2 head_ext = {head_w * 0.5f, head_h * 0.5f};
    b2Vec2 head_pos = {0.0f, torso_pos.y + torso.extent.y + head_ext.y};

    this->head = BodyPart(worldId, head_pos, head_ext, weight * 0.08f);

    // thigh

    float thigh_w = torso_w * 0.8f;
    float thigh_h = 0.37f;
    b2Vec2 thigh_ext = {thigh_w * 0.5f, thigh_h * 0.5f};
    b2Vec2 thigh_pos = {0.0f, torso_pos.y - torso.extent.y - thigh_ext.y};

    this->thigh = BodyPart(worldId, thigh_pos, thigh_ext, weight * 0.22f);

    // shin

    float shin_w = thigh_w * 0.8f;
    float shin_h = 0.36f;
    b2Vec2 shin_ext = {shin_w * 0.5f, shin_h * 0.5f};
    b2Vec2 shin_pos = {0.0f, thigh_pos.y - thigh.extent.y - shin_ext.y};

    this->shin = BodyPart(worldId, shin_pos, shin_ext, weight * 0.10f);

    // foot

    float foot_w = 0.26f;
    float foot_h = 0.06f;
    b2Vec2 foot_ext = {foot_w * 0.5f, foot_h * 0.5f};
    b2Vec2 foot_pos = {0.0f, shin_pos.y - shin.extent.y - foot_ext.y};

    this->foot = BodyPart(worldId, foot_pos, foot_ext, weight * 0.035f);
    // footShapeDef.friction = 1.0f;

    // upper arm

    float upperArm_w = 0.05f;
    float upperArm_h = 0.35f;
    b2Vec2 upper_arm_ext = {upperArm_w * 0.5f, upperArm_h * 0.5f};
    b2Vec2 upper_arm_pos = {0.0f, torso_pos.y};

    this->upper_arm = BodyPart(worldId, upper_arm_pos, upper_arm_ext, weight * 0.047f);

    // lower arm

    float lowerArm_w = 0.043f;
    float lowerArm_h = 0.29f;
    b2Vec2 lower_arm_ext = {lowerArm_w * 0.5f, lowerArm_h * 0.5f};
    b2Vec2 lower_arm_pos = {0.0f, upper_arm_pos.y - upper_arm.extent.y - lower_arm_ext.y};

    this->lower_arm = BodyPart(worldId, lower_arm_pos, lower_arm_ext, weight * 0.022f);

    // neck joint
    b2RevoluteJointDef neck_joint_def = b2DefaultRevoluteJointDef();
    neck_joint_def.bodyIdA = torso.id;
    neck_joint_def.bodyIdB = head.id;
    neck_joint_def.localAnchorA = {0.0f, torso.extent.y};
    neck_joint_def.localAnchorB = {0.0f, -head.extent.y};
    neck_joint_def.lowerAngle = 0.0f;
    neck_joint_def.upperAngle = 0.0f;
    neck_joint_def.enableLimit = true;
    b2CreateRevoluteJoint(worldId, &neck_joint_def);

    // hip joint
    b2RevoluteJointDef hip_joint_def = b2DefaultRevoluteJointDef();
    hip_joint_def.bodyIdA = torso.id;
    hip_joint_def.bodyIdB = thigh.id;
    hip_joint_def.localAnchorA = {0.0f, -torso.extent.y};
    hip_joint_def.localAnchorB = {0.0f, thigh.extent.y};
    hip_joint_def.lowerAngle = HIP_LOWER_ANGLE;
    hip_joint_def.upperAngle = HIP_UPPER_ANGLE;
    hip_joint_def.enableLimit = true;
    hip_joint_def.maxMotorTorque = 250.0f;
    hip_joint_def.motorSpeed = 0.0f;
    hip_joint_def.enableMotor = true;

    hipJointId = b2CreateRevoluteJoint(worldId, &hip_joint_def);

    // knee joint
    b2RevoluteJointDef knee_joint_def = b2DefaultRevoluteJointDef();
    knee_joint_def.bodyIdA = thigh.id;
    knee_joint_def.bodyIdB = shin.id;
    knee_joint_def.localAnchorA = {0.0f, -thigh.extent.y};
    knee_joint_def.localAnchorB = {0.0f, shin.extent.y};
    knee_joint_def.lowerAngle = KNEE_LOWER_ANGLE;
    knee_joint_def.upperAngle = KNEE_UPPER_ANGLE;
    knee_joint_def.enableLimit = true;
    knee_joint_def.maxMotorTorque = 250.0f;
    knee_joint_def.motorSpeed = 0.0f;
    knee_joint_def.enableMotor = true;

    kneeJointId = b2CreateRevoluteJoint(worldId, &knee_joint_def);

    // ankle joint
    b2RevoluteJointDef ankle_joint_def = b2DefaultRevoluteJointDef();
    ankle_joint_def.bodyIdA = shin.id;
    ankle_joint_def.bodyIdB = foot.id;
    ankle_joint_def.localAnchorA = {-shin.extent.x, -shin.extent.y};
    ankle_joint_def.localAnchorB = {-shin.extent.x * 1.6f, foot.extent.y};
    ankle_joint_def.lowerAngle = ANKLE_LOWER_ANGLE;
    ankle_joint_def.upperAngle = ANKLE_UPPER_ANGLE;
    ankle_joint_def.enableLimit = true;

    ankle_joint_def.maxMotorTorque = 250.0f;
    ankle_joint_def.motorSpeed = 0.0f;
    ankle_joint_def.enableMotor = true;

    ankleJointId = b2CreateRevoluteJoint(worldId, &ankle_joint_def);

    // shoulder joint
    b2RevoluteJointDef shoulder_joint_def = b2DefaultRevoluteJointDef();
    shoulder_joint_def.bodyIdA = torso.id;
    shoulder_joint_def.bodyIdB = upper_arm.id;
    shoulder_joint_def.localAnchorA = {0.0f, torso.extent.y * 0.8f};
    shoulder_joint_def.localAnchorB = {0.0f, upper_arm.extent.y * 0.9f};
    shoulder_joint_def.lowerAngle = SHOULDER_LOWER_ANGLE;
    shoulder_joint_def.upperAngle = SHOULDER_UPPER_ANGLE;
    shoulder_joint_def.enableLimit = true;
    shoulder_joint_def.maxMotorTorque = 200.0f;
    shoulder_joint_def.motorSpeed = 0.0f;
    shoulder_joint_def.enableMotor = true;

    shoulderJointId = b2CreateRevoluteJoint(worldId, &shoulder_joint_def);

    // elbow joint
    b2RevoluteJointDef elbow_joint_def = b2DefaultRevoluteJointDef();
    elbow_joint_def.bodyIdA = upper_arm.id;
    elbow_joint_def.bodyIdB = lower_arm.id;
    elbow_joint_def.localAnchorA = {0.0f, -upper_arm.extent.y * 0.9f};
    elbow_joint_def.localAnchorB = {0.0f, lower_arm.extent.y * 0.9f};
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
    b2Vec2 torso_p = b2Body_GetWorldPoint(torso.id, {-torso.extent.x, torso.extent.y});
    b2Rot torso_rotation = b2Body_GetRotation(torso.id);
    float torso_angle = b2Rot_GetAngle(torso_rotation);

    Rectangle torso_rec = {torso_p.x * PPM, -torso_p.y * PPM, torso.extent.x * 2 * PPM, torso.extent.y * 2 * PPM};
    DrawRectanglePro(torso_rec, {0.0f, 0.0f}, -torso_angle * RAD2DEG, DARKBLUE);

    // head
    b2Vec2 head_p = b2Body_GetWorldPoint(head.id, {-head.extent.x, head.extent.y});
    b2Rot head_rotation = b2Body_GetRotation(head.id);
    float head_angle = b2Rot_GetAngle(head_rotation);

    Rectangle head_rec = {head_p.x * PPM, -head_p.y * PPM, head.extent.x * 2 * PPM, head.extent.y * 2 * PPM};
    DrawRectanglePro(head_rec, {0.0f, 0.0f}, -head_angle * RAD2DEG, BLUE);

    // thigh
    b2Vec2 thigh_p = b2Body_GetWorldPoint(thigh.id, {-thigh.extent.x, thigh.extent.y});
    b2Rot thigh_rotation = b2Body_GetRotation(thigh.id);
    float thigh_angle = b2Rot_GetAngle(thigh_rotation);

    Rectangle thigh_rec = {thigh_p.x * PPM, -thigh_p.y * PPM, thigh.extent.x * 2 * PPM, thigh.extent.y * 2 * PPM};
    DrawRectanglePro(thigh_rec, {0.0f, 0.0f}, -thigh_angle * RAD2DEG, BLUE);

    // shin
    b2Vec2 shin_p = b2Body_GetWorldPoint(shin.id, {-shin.extent.x, shin.extent.y});
    b2Rot shin_rotation = b2Body_GetRotation(shin.id);
    float shin_angle = b2Rot_GetAngle(shin_rotation);

    Rectangle shin_rec = {shin_p.x * PPM, -shin_p.y * PPM, shin.extent.x * 2 * PPM, shin.extent.y * 2 * PPM};
    DrawRectanglePro(shin_rec, {0.0f, 0.0f}, -shin_angle * RAD2DEG, DARKBLUE);

    // foot

    b2Vec2 foot_p = b2Body_GetWorldPoint(foot.id, {-foot.extent.x, foot.extent.y});
    b2Rot foot_rotation = b2Body_GetRotation(foot.id);
    float foot_angle = b2Rot_GetAngle(foot_rotation);

    Rectangle foot_rec = {foot_p.x * PPM, -foot_p.y * PPM, foot.extent.x * 2 * PPM, foot.extent.y * 2 * PPM};
    DrawRectanglePro(foot_rec, {0.0f, 0.0f}, -foot_angle * RAD2DEG, DARKBLUE);

    // upper arm
    b2Vec2 upper_arm_p = b2Body_GetWorldPoint(upper_arm.id, {-upper_arm.extent.x, upper_arm.extent.y});
    b2Rot upper_arm_rotation = b2Body_GetRotation(upper_arm.id);
    float upper_arm_angle = b2Rot_GetAngle(upper_arm_rotation);

    Rectangle upper_arm_rec = {upper_arm_p.x * PPM, -upper_arm_p.y * PPM, upper_arm.extent.x * 2 * PPM, upper_arm.extent.y * 2 * PPM};
    DrawRectanglePro(upper_arm_rec, {0.0f, 0.0f}, -upper_arm_angle * RAD2DEG, BLUE);

    // lower arm
    b2Vec2 lower_arm_p = b2Body_GetWorldPoint(lower_arm.id, {-lower_arm.extent.x, lower_arm.extent.y});
    b2Rot lower_arm_rotation = b2Body_GetRotation(lower_arm.id);
    float lower_arm_angle = b2Rot_GetAngle(lower_arm_rotation);

    Rectangle lower_arm_rec = {lower_arm_p.x * PPM, -lower_arm_p.y * PPM, lower_arm.extent.x * 2 * PPM, lower_arm.extent.y * 2 * PPM};
    DrawRectanglePro(lower_arm_rec, {0.0f, 0.0f}, -lower_arm_angle * RAD2DEG, PURPLE);
};

void Psik::set_joint_angle(b2JointId jointId, float angle, float speed) {
    float joint_angle = b2RevoluteJoint_GetAngle(jointId);

    float diff = angle - joint_angle;
    b2Joint_WakeBodies(jointId);
    b2RevoluteJoint_SetMotorSpeed(jointId, speed * diff);
};
