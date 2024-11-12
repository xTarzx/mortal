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

    // right thigh

    float r_thigh_w = torso_w * 0.8f;
    float r_thigh_h = 0.37f;
    b2Vec2 r_thigh_ext = {r_thigh_w * 0.5f, r_thigh_h * 0.5f};
    b2Vec2 r_thigh_pos = {0.0f, torso_pos.y - torso.extent.y - r_thigh_ext.y};

    this->r_thigh = BodyPart(worldId, r_thigh_pos, r_thigh_ext, weight * 0.22f / 2);

    // left thigh

    float l_thigh_w = torso_w * 0.8f;
    float l_thigh_h = 0.37f;
    b2Vec2 l_thigh_ext = {l_thigh_w * 0.5f, l_thigh_h * 0.5f};
    b2Vec2 l_thigh_pos = {0.0f, torso_pos.y - torso.extent.y - l_thigh_ext.y};

    this->l_thigh = BodyPart(worldId, l_thigh_pos, l_thigh_ext, weight * 0.22f / 2);

    // right shin

    float r_shin_w = r_thigh_w * 0.8f;
    float r_shin_h = 0.36f;
    b2Vec2 r_shin_ext = {r_shin_w * 0.5f, r_shin_h * 0.5f};
    b2Vec2 r_shin_pos = {0.0f, r_thigh_pos.y - r_thigh.extent.y - r_shin_ext.y};

    this->r_shin = BodyPart(worldId, r_shin_pos, r_shin_ext, weight * 0.10f / 2);

    // left shin

    float l_shin_w = l_thigh_w * 0.8f;
    float l_shin_h = 0.36f;
    b2Vec2 l_shin_ext = {l_shin_w * 0.5f, l_shin_h * 0.5f};
    b2Vec2 l_shin_pos = {0.0f, l_thigh_pos.y - l_thigh.extent.y - l_shin_ext.y};

    this->l_shin = BodyPart(worldId, l_shin_pos, l_shin_ext, weight * 0.10f / 2);

    // right foot

    float r_foot_w = 0.26f;
    float r_foot_h = 0.06f;
    b2Vec2 r_foot_ext = {r_foot_w * 0.5f, r_foot_h * 0.5f};
    b2Vec2 r_foot_pos = {0.0f, r_shin_pos.y - r_shin.extent.y - r_foot_ext.y};

    this->r_foot = BodyPart(worldId, r_foot_pos, r_foot_ext, weight * 0.035f / 2);
    // footShapeDef.friction = 1.0f;

    // left foot

    float l_foot_w = 0.26f;
    float l_foot_h = 0.06f;
    b2Vec2 l_foot_ext = {l_foot_w * 0.5f, l_foot_h * 0.5f};
    b2Vec2 l_foot_pos = {0.0f, l_shin_pos.y - l_shin.extent.y - l_foot_ext.y};

    this->l_foot = BodyPart(worldId, l_foot_pos, l_foot_ext, weight * 0.035f / 2);
    // footShapeDef.friction = 1.0f;

    // right upper arm

    float r_upper_arm_w = 0.05f;
    float r_upper_arm_h = 0.35f;
    b2Vec2 r_upper_arm_ext = {r_upper_arm_w * 0.5f, r_upper_arm_h * 0.5f};
    b2Vec2 r_upper_arm_pos = {0.0f, torso_pos.y};

    this->r_upper_arm = BodyPart(worldId, r_upper_arm_pos, r_upper_arm_ext, weight * 0.047f / 2);

    // right lower arm

    float r_lower_arm_w = 0.043f;
    float r_lower_arm_h = 0.29f;
    b2Vec2 r_lower_arm_ext = {r_lower_arm_w * 0.5f, r_lower_arm_h * 0.5f};
    b2Vec2 r_lower_arm_pos = {0.0f, r_upper_arm_pos.y - r_upper_arm.extent.y - r_lower_arm_ext.y};

    this->r_lower_arm = BodyPart(worldId, r_lower_arm_pos, r_lower_arm_ext, weight * 0.022f / 2);

    // left upper arm

    float l_upper_arm_w = 0.05f;
    float l_upper_arm_h = 0.35f;
    b2Vec2 l_upper_arm_ext = {l_upper_arm_w * 0.5f, l_upper_arm_h * 0.5f};
    b2Vec2 l_upper_arm_pos = {0.0f, torso_pos.y};

    this->l_upper_arm = BodyPart(worldId, l_upper_arm_pos, l_upper_arm_ext, weight * 0.047f / 2);

    // left lower arm

    float l_lower_arm_w = 0.043f;
    float l_lower_arm_h = 0.29f;
    b2Vec2 l_lower_arm_ext = {l_lower_arm_w * 0.5f, l_lower_arm_h * 0.5f};
    b2Vec2 l_lower_arm_pos = {0.0f, l_upper_arm_pos.y - l_upper_arm.extent.y - l_lower_arm_ext.y};

    this->l_lower_arm = BodyPart(worldId, l_lower_arm_pos, l_lower_arm_ext, weight * 0.022f / 2);

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

    // right hip joint
    b2RevoluteJointDef r_hip_joint_def = b2DefaultRevoluteJointDef();
    r_hip_joint_def.bodyIdA = torso.id;
    r_hip_joint_def.bodyIdB = r_thigh.id;
    r_hip_joint_def.localAnchorA = {0.0f, -torso.extent.y};
    r_hip_joint_def.localAnchorB = {0.0f, r_thigh.extent.y};
    r_hip_joint_def.lowerAngle = HIP_LOWER_ANGLE;
    r_hip_joint_def.upperAngle = HIP_UPPER_ANGLE;
    r_hip_joint_def.enableLimit = true;
    r_hip_joint_def.maxMotorTorque = 250.0f / 2;
    r_hip_joint_def.motorSpeed = 0.0f;
    r_hip_joint_def.enableMotor = true;

    r_hipJointId = b2CreateRevoluteJoint(worldId, &r_hip_joint_def);

    // left hip joint
    b2RevoluteJointDef l_hip_joint_def = b2DefaultRevoluteJointDef();
    l_hip_joint_def.bodyIdA = torso.id;
    l_hip_joint_def.bodyIdB = l_thigh.id;
    l_hip_joint_def.localAnchorA = {0.0f, -torso.extent.y};
    l_hip_joint_def.localAnchorB = {0.0f, l_thigh.extent.y};
    l_hip_joint_def.lowerAngle = HIP_LOWER_ANGLE;
    l_hip_joint_def.upperAngle = HIP_UPPER_ANGLE;
    l_hip_joint_def.enableLimit = true;
    l_hip_joint_def.maxMotorTorque = 250.0f / 2;
    l_hip_joint_def.motorSpeed = 0.0f;
    l_hip_joint_def.enableMotor = true;

    l_hipJointId = b2CreateRevoluteJoint(worldId, &l_hip_joint_def);

    // right knee joint
    b2RevoluteJointDef r_knee_joint_def = b2DefaultRevoluteJointDef();
    r_knee_joint_def.bodyIdA = r_thigh.id;
    r_knee_joint_def.bodyIdB = r_shin.id;
    r_knee_joint_def.localAnchorA = {0.0f, -r_thigh.extent.y};
    r_knee_joint_def.localAnchorB = {0.0f, r_shin.extent.y};
    r_knee_joint_def.lowerAngle = KNEE_LOWER_ANGLE;
    r_knee_joint_def.upperAngle = KNEE_UPPER_ANGLE;
    r_knee_joint_def.enableLimit = true;
    r_knee_joint_def.maxMotorTorque = 250.0f / 2;
    r_knee_joint_def.motorSpeed = 0.0f;
    r_knee_joint_def.enableMotor = true;

    r_kneeJointId = b2CreateRevoluteJoint(worldId, &r_knee_joint_def);
    // left knee joint
    b2RevoluteJointDef l_knee_joint_def = b2DefaultRevoluteJointDef();
    l_knee_joint_def.bodyIdA = l_thigh.id;
    l_knee_joint_def.bodyIdB = l_shin.id;
    l_knee_joint_def.localAnchorA = {0.0f, -l_thigh.extent.y};
    l_knee_joint_def.localAnchorB = {0.0f, l_shin.extent.y};
    l_knee_joint_def.lowerAngle = KNEE_LOWER_ANGLE;
    l_knee_joint_def.upperAngle = KNEE_UPPER_ANGLE;
    l_knee_joint_def.enableLimit = true;
    l_knee_joint_def.maxMotorTorque = 250.0f / 2;
    l_knee_joint_def.motorSpeed = 0.0f;
    l_knee_joint_def.enableMotor = true;

    l_kneeJointId = b2CreateRevoluteJoint(worldId, &l_knee_joint_def);

    // right ankle joint
    b2RevoluteJointDef r_ankle_joint_def = b2DefaultRevoluteJointDef();
    r_ankle_joint_def.bodyIdA = r_shin.id;
    r_ankle_joint_def.bodyIdB = r_foot.id;
    r_ankle_joint_def.localAnchorA = {-r_shin.extent.x, -r_shin.extent.y};
    r_ankle_joint_def.localAnchorB = {-r_shin.extent.x * 1.6f, r_foot.extent.y};
    r_ankle_joint_def.lowerAngle = ANKLE_LOWER_ANGLE;
    r_ankle_joint_def.upperAngle = ANKLE_UPPER_ANGLE;
    r_ankle_joint_def.enableLimit = true;

    r_ankle_joint_def.maxMotorTorque = 250.0f / 2;
    r_ankle_joint_def.motorSpeed = 0.0f;
    r_ankle_joint_def.enableMotor = true;

    r_ankleJointId = b2CreateRevoluteJoint(worldId, &r_ankle_joint_def);
    // left ankle joint
    b2RevoluteJointDef l_ankle_joint_def = b2DefaultRevoluteJointDef();
    l_ankle_joint_def.bodyIdA = l_shin.id;
    l_ankle_joint_def.bodyIdB = l_foot.id;
    l_ankle_joint_def.localAnchorA = {-l_shin.extent.x, -l_shin.extent.y};
    l_ankle_joint_def.localAnchorB = {-l_shin.extent.x * 1.6f, l_foot.extent.y};
    l_ankle_joint_def.lowerAngle = ANKLE_LOWER_ANGLE;
    l_ankle_joint_def.upperAngle = ANKLE_UPPER_ANGLE;
    l_ankle_joint_def.enableLimit = true;

    l_ankle_joint_def.maxMotorTorque = 250.0f / 2;
    l_ankle_joint_def.motorSpeed = 0.0f;
    l_ankle_joint_def.enableMotor = true;

    l_ankleJointId = b2CreateRevoluteJoint(worldId, &l_ankle_joint_def);

    // right shoulder joint
    b2RevoluteJointDef r_shoulder_joint_def = b2DefaultRevoluteJointDef();
    r_shoulder_joint_def.bodyIdA = torso.id;
    r_shoulder_joint_def.bodyIdB = r_upper_arm.id;
    r_shoulder_joint_def.localAnchorA = {0.0f, torso.extent.y * 0.8f};
    r_shoulder_joint_def.localAnchorB = {0.0f, r_upper_arm.extent.y * 0.9f};
    r_shoulder_joint_def.lowerAngle = SHOULDER_LOWER_ANGLE;
    r_shoulder_joint_def.upperAngle = SHOULDER_UPPER_ANGLE;
    r_shoulder_joint_def.enableLimit = true;
    r_shoulder_joint_def.maxMotorTorque = 200.0f / 2;
    r_shoulder_joint_def.motorSpeed = 0.0f;
    r_shoulder_joint_def.enableMotor = true;

    r_shoulderJointId = b2CreateRevoluteJoint(worldId, &r_shoulder_joint_def);

    // left shoulder joint
    b2RevoluteJointDef l_shoulder_joint_def = b2DefaultRevoluteJointDef();
    l_shoulder_joint_def.bodyIdA = torso.id;
    l_shoulder_joint_def.bodyIdB = l_upper_arm.id;
    l_shoulder_joint_def.localAnchorA = {0.0f, torso.extent.y * 0.8f};
    l_shoulder_joint_def.localAnchorB = {0.0f, l_upper_arm.extent.y * 0.9f};
    l_shoulder_joint_def.lowerAngle = SHOULDER_LOWER_ANGLE;
    l_shoulder_joint_def.upperAngle = SHOULDER_UPPER_ANGLE;
    l_shoulder_joint_def.enableLimit = true;
    l_shoulder_joint_def.maxMotorTorque = 200.0f / 2;
    l_shoulder_joint_def.motorSpeed = 0.0f;
    l_shoulder_joint_def.enableMotor = true;

    l_shoulderJointId = b2CreateRevoluteJoint(worldId, &l_shoulder_joint_def);

    // right elbow joint
    b2RevoluteJointDef r_elbow_joint_def = b2DefaultRevoluteJointDef();
    r_elbow_joint_def.bodyIdA = r_upper_arm.id;
    r_elbow_joint_def.bodyIdB = r_lower_arm.id;
    r_elbow_joint_def.localAnchorA = {0.0f, -r_upper_arm.extent.y * 0.9f};
    r_elbow_joint_def.localAnchorB = {0.0f, r_lower_arm.extent.y * 0.9f};
    r_elbow_joint_def.lowerAngle = ELBOW_LOWER_ANGLE;
    r_elbow_joint_def.upperAngle = ELBOW_UPPER_ANGLE;
    r_elbow_joint_def.enableLimit = true;
    r_elbow_joint_def.maxMotorTorque = 200.0f / 2;
    r_elbow_joint_def.motorSpeed = 0.0f;
    r_elbow_joint_def.enableMotor = true;

    r_elbowJointId = b2CreateRevoluteJoint(worldId, &r_elbow_joint_def);

    // left elbow joint
    b2RevoluteJointDef l_elbow_joint_def = b2DefaultRevoluteJointDef();
    l_elbow_joint_def.bodyIdA = l_upper_arm.id;
    l_elbow_joint_def.bodyIdB = l_lower_arm.id;
    l_elbow_joint_def.localAnchorA = {0.0f, -l_upper_arm.extent.y * 0.9f};
    l_elbow_joint_def.localAnchorB = {0.0f, l_lower_arm.extent.y * 0.9f};
    l_elbow_joint_def.lowerAngle = ELBOW_LOWER_ANGLE;
    l_elbow_joint_def.upperAngle = ELBOW_UPPER_ANGLE;
    l_elbow_joint_def.enableLimit = true;
    l_elbow_joint_def.maxMotorTorque = 200.0f / 2;
    l_elbow_joint_def.motorSpeed = 0.0f;
    l_elbow_joint_def.enableMotor = true;

    l_elbowJointId = b2CreateRevoluteJoint(worldId, &l_elbow_joint_def);
}

Color darken_color(Color color, float v) {
    return ColorTint(color, Color{
                                (unsigned char)(255 - 255 * v),
                                (unsigned char)(255 - 255 * v),
                                (unsigned char)(255 - 255 * v),
                                255});
}

void Psik::draw() {
    Color upper_arm_color = BLUE;
    Color lower_arm_color = PURPLE;
    Color thigh_color = BLUE;
    Color shin_color = DARKBLUE;
    Color foot_color = DARKBLUE;
    float dark_factor = 0.5f;

    // left upper arm
    b2Vec2 l_upper_arm_p = b2Body_GetWorldPoint(l_upper_arm.id, {-l_upper_arm.extent.x, l_upper_arm.extent.y});
    b2Rot l_upper_arm_rotation = b2Body_GetRotation(l_upper_arm.id);
    float l_upper_arm_angle = b2Rot_GetAngle(l_upper_arm_rotation);

    Rectangle l_upper_arm_rec = {l_upper_arm_p.x * PPM, -l_upper_arm_p.y * PPM, l_upper_arm.extent.x * 2 * PPM, l_upper_arm.extent.y * 2 * PPM};
    DrawRectanglePro(l_upper_arm_rec, {0.0f, 0.0f}, -l_upper_arm_angle * RAD2DEG, darken_color(upper_arm_color, dark_factor));

    // left lower arm
    b2Vec2 l_lower_arm_p = b2Body_GetWorldPoint(l_lower_arm.id, {-l_lower_arm.extent.x, l_lower_arm.extent.y});
    b2Rot l_lower_arm_rotation = b2Body_GetRotation(l_lower_arm.id);
    float l_lower_arm_angle = b2Rot_GetAngle(l_lower_arm_rotation);

    Rectangle l_lower_arm_rec = {l_lower_arm_p.x * PPM, -l_lower_arm_p.y * PPM, l_lower_arm.extent.x * 2 * PPM, l_lower_arm.extent.y * 2 * PPM};
    DrawRectanglePro(l_lower_arm_rec, {0.0f, 0.0f}, -l_lower_arm_angle * RAD2DEG, darken_color(lower_arm_color, dark_factor));

    // left thigh
    b2Vec2 l_thigh_p = b2Body_GetWorldPoint(l_thigh.id, {-l_thigh.extent.x, l_thigh.extent.y});
    b2Rot l_thigh_rotation = b2Body_GetRotation(l_thigh.id);
    float l_thigh_angle = b2Rot_GetAngle(l_thigh_rotation);

    Rectangle l_thigh_rec = {l_thigh_p.x * PPM, -l_thigh_p.y * PPM, l_thigh.extent.x * 2 * PPM, l_thigh.extent.y * 2 * PPM};
    DrawRectanglePro(l_thigh_rec, {0.0f, 0.0f}, -l_thigh_angle * RAD2DEG, darken_color(thigh_color, dark_factor));

    // left shin
    b2Vec2 l_shin_p = b2Body_GetWorldPoint(l_shin.id, {-l_shin.extent.x, l_shin.extent.y});
    b2Rot l_shin_rotation = b2Body_GetRotation(l_shin.id);
    float l_shin_angle = b2Rot_GetAngle(l_shin_rotation);

    Rectangle l_shin_rec = {l_shin_p.x * PPM, -l_shin_p.y * PPM, l_shin.extent.x * 2 * PPM, l_shin.extent.y * 2 * PPM};
    DrawRectanglePro(l_shin_rec, {0.0f, 0.0f}, -l_shin_angle * RAD2DEG, darken_color(shin_color, dark_factor));

    // left foot

    b2Vec2 l_foot_p = b2Body_GetWorldPoint(l_foot.id, {-l_foot.extent.x, l_foot.extent.y});
    b2Rot l_foot_rotation = b2Body_GetRotation(l_foot.id);
    float l_foot_angle = b2Rot_GetAngle(l_foot_rotation);

    Rectangle l_foot_rec = {l_foot_p.x * PPM, -l_foot_p.y * PPM, l_foot.extent.x * 2 * PPM, l_foot.extent.y * 2 * PPM};
    DrawRectanglePro(l_foot_rec, {0.0f, 0.0f}, -l_foot_angle * RAD2DEG, darken_color(foot_color, dark_factor));

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

    // right thigh
    b2Vec2 r_thigh_p = b2Body_GetWorldPoint(r_thigh.id, {-r_thigh.extent.x, r_thigh.extent.y});
    b2Rot r_thigh_rotation = b2Body_GetRotation(r_thigh.id);
    float r_thigh_angle = b2Rot_GetAngle(r_thigh_rotation);

    Rectangle r_thigh_rec = {r_thigh_p.x * PPM, -r_thigh_p.y * PPM, r_thigh.extent.x * 2 * PPM, r_thigh.extent.y * 2 * PPM};
    DrawRectanglePro(r_thigh_rec, {0.0f, 0.0f}, -r_thigh_angle * RAD2DEG, thigh_color);

    // right shin
    b2Vec2 r_shin_p = b2Body_GetWorldPoint(r_shin.id, {-r_shin.extent.x, r_shin.extent.y});
    b2Rot r_shin_rotation = b2Body_GetRotation(r_shin.id);
    float r_shin_angle = b2Rot_GetAngle(r_shin_rotation);

    Rectangle r_shin_rec = {r_shin_p.x * PPM, -r_shin_p.y * PPM, r_shin.extent.x * 2 * PPM, r_shin.extent.y * 2 * PPM};
    DrawRectanglePro(r_shin_rec, {0.0f, 0.0f}, -r_shin_angle * RAD2DEG, shin_color);

    // right foot

    b2Vec2 r_foot_p = b2Body_GetWorldPoint(r_foot.id, {-r_foot.extent.x, r_foot.extent.y});
    b2Rot r_foot_rotation = b2Body_GetRotation(r_foot.id);
    float r_foot_angle = b2Rot_GetAngle(r_foot_rotation);

    Rectangle r_foot_rec = {r_foot_p.x * PPM, -r_foot_p.y * PPM, r_foot.extent.x * 2 * PPM, r_foot.extent.y * 2 * PPM};
    DrawRectanglePro(r_foot_rec, {0.0f, 0.0f}, -r_foot_angle * RAD2DEG, foot_color);

    // right upper arm
    b2Vec2 r_upper_arm_p = b2Body_GetWorldPoint(r_upper_arm.id, {-r_upper_arm.extent.x, r_upper_arm.extent.y});
    b2Rot r_upper_arm_rotation = b2Body_GetRotation(r_upper_arm.id);
    float r_upper_arm_angle = b2Rot_GetAngle(r_upper_arm_rotation);

    Rectangle r_upper_arm_rec = {r_upper_arm_p.x * PPM, -r_upper_arm_p.y * PPM, r_upper_arm.extent.x * 2 * PPM, r_upper_arm.extent.y * 2 * PPM};
    DrawRectanglePro(r_upper_arm_rec, {0.0f, 0.0f}, -r_upper_arm_angle * RAD2DEG, upper_arm_color);

    // right lower arm
    b2Vec2 r_lower_arm_p = b2Body_GetWorldPoint(r_lower_arm.id, {-r_lower_arm.extent.x, r_lower_arm.extent.y});
    b2Rot r_lower_arm_rotation = b2Body_GetRotation(r_lower_arm.id);
    float r_lower_arm_angle = b2Rot_GetAngle(r_lower_arm_rotation);

    Rectangle r_lower_arm_rec = {r_lower_arm_p.x * PPM, -r_lower_arm_p.y * PPM, r_lower_arm.extent.x * 2 * PPM, r_lower_arm.extent.y * 2 * PPM};
    DrawRectanglePro(r_lower_arm_rec, {0.0f, 0.0f}, -r_lower_arm_angle * RAD2DEG, lower_arm_color);
};

void Psik::set_joint_angle(b2JointId jointId, float angle, float speed) {
    float joint_angle = b2RevoluteJoint_GetAngle(jointId);

    float diff = angle - joint_angle;
    b2Joint_WakeBodies(jointId);
    b2RevoluteJoint_SetMotorSpeed(jointId, speed * diff);
};
