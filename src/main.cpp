#include <iostream>
#include <cassert>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "box2d/box2d.h"

#include "common.h"
#include "psik.h"
#include "pose.h"
#include "poses.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#undef RAYGUI_IMPLEMENTATION
#define GUI_WINDOW_FILE_DIALOG_IMPLEMENTATION
#include "gui_window_file_dialog.h"

#include "serialize.h"

enum Error {
    ERROR_FILE_NOT_EXIST,
    ERROR_INVALID_FILE,
};

void export_animation(std::vector<KF> kfs, const char* filepath) {
    json j = json::array();
    for (int i = 0; i < kfs.size(); i++) {
        j.push_back(serialize_keyframe(kfs[i]));
    }

    std::string j_str = j.dump(4);

    SaveFileText(filepath, const_cast<char*>(j_str.c_str()));
}

std::vector<KF> import_animation(const char* filepath) {
    char* j_str = LoadFileText(filepath);

    if (j_str == nullptr) throw ERROR_FILE_NOT_EXIST;
    json j;
    try {
        j = json::parse(j_str);
    } catch (nlohmann::json_abi_v3_11_3::detail::parse_error err) {
        throw ERROR_INVALID_FILE;
    };

    std::vector<KF> kfs;

    for (int i = 0; i < j.size(); i++) {
        KF kf = deserialize_keyframe(j[i]);

        kfs.push_back(kf);
    }

    free(j_str);
    return kfs;
}

struct State {
    float ed_frame_dur = 0.0f;

    Pose ed_pose_copy = Poses::zero;
    char ed_kf_name_text[KF_NAME_MAX_LEN] = {0};
    bool editing_name = false;
    int ed_kf_name_idx = 0;
    std::string error_str;

    bool disable_sliders = false;
    bool disable_keybinds = false;
    bool disable_dragdrop_import = false;
    bool disable_timeline_interact = false;
    bool disable_imp_exp = false;

    bool disable_editor = false;

    float timeline_scroll = 0.0f;
    bool timeline_drag = false;

    void enter_name_edit() {
        editing_name = true;
        disable_sliders = true;
        disable_keybinds = true;
        disable_dragdrop_import = true;
        disable_timeline_interact = true;
        disable_imp_exp = true;
    };

    void exit_name_edit() {
        editing_name = false;
        disable_sliders = false;
        disable_keybinds = false;
        disable_dragdrop_import = false;
        disable_timeline_interact = false;
        disable_imp_exp = false;
    };

    void enter_timeline_drag() {
        timeline_drag = true;
        disable_sliders = true;
    }

    void exit_timeline_drag() {
        timeline_drag = false;
        disable_sliders = false;
    }
};

struct Ground {
    b2BodyId bodyId;
    b2Vec2 extent;

    Ground(b2WorldId worldId) {
        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.position = {0.0f, 0.0f};
        bodyId = b2CreateBody(worldId, &bodyDef);
        extent = {5.8f, 1.5f};
        b2Polygon polygon = b2MakeBox(extent.x, extent.y);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.friction = 1.0f;
        b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
    }

    void draw() {
        b2Vec2 p = b2Body_GetWorldPoint(bodyId, {-extent.x, extent.y});

        DrawRectangle(p.x * PPM, -p.y * PPM, extent.x * 2 * PPM, extent.y * 2 * PPM, GetColor(0x8095b9));
    }
};

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "mortal");

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);

    Ground ground = Ground(worldId);
    Psik psik = Psik(worldId);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    Camera2D camera{
        .offset = {GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f},
        .target = {0.0f, -2.3f * PPM},
        .rotation = 0.0f,
        .zoom = 1.84f,

    };

    float camera_speed = 150.0f;
    float zoom_speed = 1.0f;

    std::vector<KF> kfs1 = {
        {.pose = Poses::standing, .frame_dur = 8},
        {.pose = Poses::standing_rlx, .frame_dur = 0},
        {.pose = Poses::jump_prep, .frame_dur = 0},
        {.pose = Poses::prep_swing, .frame_dur = 3},
        {.pose = Poses::jump0, .frame_dur = 6},
        {.pose = Poses::jump, .frame_dur = 0},
        {.pose = Poses::tuck, .frame_dur = 0},
        {.pose = Poses::land0, .frame_dur = 6},
        {.pose = Poses::land, .frame_dur = 4},
    };
    // std::vector<KF> kfs2 = {
    //     {.pose = Poses::standing, .frame_dur = 15},
    //     {.pose = Poses::standing_rlx, .frame_dur = 0},
    //     {.pose = Poses::jump_prep, .frame_dur = 0},
    //     {.pose = Poses::prep_swing, .frame_dur = 3},
    //     {.pose = Poses::jump0, .frame_dur = 6},
    //     {.pose = Poses::jump, .frame_dur = 0},
    //     {.pose = Poses::pike, .frame_dur = 0},
    //     {.pose = Poses::land0, .frame_dur = 6},
    //     {.pose = Poses::land, .frame_dur = 0},
    // };

    // std::vector<KF> vk = {
    //     {.pose = Poses::standing, .frame_dur = 15},
    //     {.pose = Poses::standing_rlx, .frame_dur = 0},
    //     {.pose = Poses::jump_prep, .frame_dur = 0},
    //     {.pose = Poses::prep_swing, .frame_dur = 3},
    //     {.pose = Poses::jump0, .frame_dur = 6},
    //     {.pose = Poses::jump, .frame_dur = 0},
    //     {.pose = Poses::split, .frame_dur = 0},

    // };

    std::vector<KF> edit_kfs = {};

    Poser poser = Poser(&psik, kfs1);
    poser.play = false;

    State state;

    GuiWindowFileDialogState fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
    bool is_export = false;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        int screen_width = GetRenderWidth();
        int screen_height = GetRenderHeight();
        Vector2 mouse_pos = GetMousePosition();

        if (!state.disable_dragdrop_import && IsFileDropped()) {
            FilePathList files = LoadDroppedFiles();
            char* filepath = files.paths[0];
            try {
                std::vector<KF> new_anim = import_animation(filepath);
                poser.reset();
                poser.kfs = new_anim;
            } catch (Error error) {
                switch (error) {
                    case ERROR_FILE_NOT_EXIST:
                        state.error_str = TextFormat("file does not exist: %s", filepath);
                        TraceLog(LOG_WARNING, state.error_str.c_str());
                        break;
                    case ERROR_INVALID_FILE:
                        state.error_str = TextFormat("invalid file: %s", filepath);
                        TraceLog(LOG_WARNING, state.error_str.c_str());
                        break;

                    default:
                        TraceLog(LOG_FATAL, "unreachable: %d", error);
                        break;
                }
            };

            UnloadDroppedFiles(files);
        }
        if (!state.disable_keybinds) {
            if (IsKeyPressed(KEY_R)) {
                b2DestroyWorld(worldId);
                worldId = b2CreateWorld(&worldDef);
                int kf = poser.kf;
                poser.reset();
                if (!poser.play)
                    poser.kf = kf;
                ground = Ground(worldId);
                psik = Psik(worldId);
            }

            if (IsKeyPressed(KEY_P)) poser.play = !poser.play;

            if (IsKeyPressed(KEY_C)) {
                if (poser.kfs.size() > 0) {
                    state.ed_pose_copy = poser.kfs[poser.kf].pose;
                }
            }

            if (IsKeyPressed(KEY_V)) {
                if (poser.kfs.size() > 0) {
                    poser.kfs[poser.kf].pose = state.ed_pose_copy;
                }
            }

            if (IsKeyPressed(KEY_SPACE)) {
                if (IsKeyDown(KEY_LEFT_SHIFT)) {
                    poser.prev_kf();
                } else {
                    poser.next_kf();
                }
            }

            if (IsKeyPressed(KEY_H)) {
                state.disable_editor = !state.disable_editor;
            }

            Vector2 cam_mov = {(float)IsKeyDown(KEY_D) - (float)IsKeyDown(KEY_A), (float)IsKeyDown(KEY_S) - (float)IsKeyDown(KEY_W)};
            int zoom_dir = IsKeyDown(KEY_E) - IsKeyDown(KEY_Q);

            camera.zoom += zoom_dir * zoom_speed * dt;
            camera.offset = {screen_width / 2.0f, screen_height / 2.0f};
            camera.target = Vector2Add(camera.target, Vector2Scale(cam_mov, dt * camera_speed));

        }  // keybinds

        poser.update();

        b2World_Step(worldId, timeStep, subStepCount);

        BeginDrawing();
        ClearBackground(GetColor(0x1f1f1fff));

        BeginMode2D(camera);

        ground.draw();

        psik.draw();

        EndMode2D();

        if (fileDialogState.windowActive) GuiLock();

        // timeline
        float timeline_height = screen_height * 0.20f;
        if (state.timeline_drag && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) state.exit_timeline_drag();
        if (!state.disable_editor) {
            Rectangle timeline_rec = {0.0f, screen_height - timeline_height, (float)screen_width, timeline_height};
            DrawRectangleRec(timeline_rec, GetColor(0x333333ff));

            float sz = timeline_height * 0.65f;
            float padding = sz * 0.1f;
            float x = padding + state.timeline_scroll;
            float y = screen_height - timeline_height / 2 - sz / 2;

            bool on_kf = false;
            for (int i = 0; i < poser.kfs.size(); i++) {
                Rectangle box = {x, y, sz, sz};
                DrawRectangleRec(box, GetColor(0x555555ff));

                {  // kf name
                    const char* text = poser.kfs[i].name.c_str();
                    float font_sz = sz * 0.1f;
                    Vector2 msr = MeasureTextEx(GetFontDefault(), text, font_sz, 0.0f);
                    DrawText(text, box.x, box.y, font_sz, WHITE);
                }

                const char* i_str = TextFormat("%d", i);
                float font_sz = sz * 0.8f;
                Vector2 msr = MeasureTextEx(GetFontDefault(), i_str, font_sz, 0.0f);
                DrawText(i_str, box.x + box.width / 2 - msr.x / 2, box.y + box.height / 2 - msr.y / 2, font_sz, i == poser.kf ? BLUE : WHITE);

                KF& kf = poser.kfs[i];

                const char* frame_dur_str = TextFormat("dur: %d/%d", i == poser.kf ? poser.frame : 0, kf.frame_dur);
                font_sz = sz * 0.2f;
                msr = MeasureTextEx(GetFontDefault(), frame_dur_str, font_sz, 0.0f);
                DrawText(frame_dur_str, box.x, box.y + box.height - msr.y, font_sz, WHITE);

                if (!state.disable_timeline_interact) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, box)) {
                        poser.play = false;
                        poser.kf = i;
                        poser.frame = 0;
                    }

                    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && CheckCollisionPointRec(mouse_pos, box)) {
                        state.ed_kf_name_idx = i;
                        strcpy(state.ed_kf_name_text, poser.kfs[state.ed_kf_name_idx].name.c_str());
                        state.enter_name_edit();
                    };
                }
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, timeline_rec)) {
                    state.enter_timeline_drag();
                }

                x += sz + padding;
            }

            float leftover = x - screen_width - state.timeline_scroll;
            if (state.timeline_drag && leftover > 0) {
                Vector2 mouse_rel = GetMouseDelta();
                state.timeline_scroll += mouse_rel.x;
                state.timeline_scroll = std::max(-leftover, std::min(0.0f, state.timeline_scroll));
            }

            {  // auto
                float circle_rad = sz * 0.1f;
                float x = timeline_rec.x + timeline_rec.width - circle_rad;
                float y = timeline_rec.y + timeline_rec.height - circle_rad;

                if (poser.play) {
                    DrawCircle(x, y, circle_rad, RED);
                }
            }

            {
                // add kf button
                float button_height = timeline_height * 0.25f;
                float font_sz = button_height * 0.8f;
                Vector2 add_msr = MeasureTextEx(GetFontDefault(), "add", font_sz, 0.0f);

                float add_button_width = add_msr.x + screen_width * 0.01f;
                Rectangle add_kf_btn = {screen_width - add_button_width, screen_height - timeline_height, add_button_width, button_height};

                DrawRectangleRec(add_kf_btn, BLUE);
                DrawText("add", add_kf_btn.x + add_kf_btn.width / 2 - add_msr.x / 2, add_kf_btn.y + add_kf_btn.height / 2 - add_msr.y / 2, font_sz, WHITE);

                Vector2 ins_l_msr = MeasureTextEx(GetFontDefault(), "<", font_sz, 0.0f);
                Rectangle ins_l_btn = {add_kf_btn.x - add_kf_btn.height, add_kf_btn.y, add_kf_btn.height, add_kf_btn.height};
                DrawRectangleRec(ins_l_btn, DARKBLUE);
                DrawText("<", ins_l_btn.x + ins_l_btn.width / 2 - ins_l_msr.x, ins_l_btn.y + ins_l_btn.height / 2 - ins_l_msr.y / 2, font_sz, WHITE);

                if (!state.disable_timeline_interact) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, add_kf_btn)) {  // insert to right
                        if (poser.kf + 1 >= poser.kfs.size()) {
                            poser.kfs.push_back(KF{.pose = Poses::zero, .frame_dur = 0});

                        } else {
                            poser.kfs.insert(poser.kfs.begin() + poser.kf + 1, KF{.pose = Poses::zero, .frame_dur = 0});
                        }
                        poser.next_kf();
                        poser.play = false;
                    }
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, ins_l_btn)) {  // insert to left
                        if (poser.kfs.size() == 0) {
                            poser.kfs.push_back(KF{.pose = Poses::zero, .frame_dur = 0});

                        } else {
                            poser.kfs.insert(poser.kfs.begin() + poser.kf, KF{.pose = Poses::zero, .frame_dur = 0});
                        }
                        poser.play = false;
                    }
                }

                // rm kf button
                if (poser.kfs.size()) {
                    Vector2 msr = MeasureTextEx(GetFontDefault(), "del", font_sz, 0.0f);
                    float button_width = msr.x + screen_width * 0.01f;
                    Rectangle rm_kf_btn = {screen_width - add_kf_btn.width - ins_l_btn.width - button_width * 1.25f, screen_height - timeline_height, button_width, button_height};

                    DrawRectangleRec(rm_kf_btn, RED);
                    DrawText("del", rm_kf_btn.x + rm_kf_btn.width / 2 - msr.x / 2, rm_kf_btn.y + rm_kf_btn.height / 2 - msr.y / 2, font_sz, WHITE);

                    if (!state.disable_timeline_interact && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, rm_kf_btn)) {
                        poser.kfs.erase(poser.kfs.begin() + poser.kf, poser.kfs.begin() + poser.kf + 1);
                        if (poser.kf > 0) {
                            poser.kf -= 1;
                        }
                        poser.play = false;
                    }

                    {  // clear kfs
                        const char* text = "clear";
                        Vector2 msr = MeasureTextEx(GetFontDefault(), text, font_sz, 0.0f);
                        float button_width = msr.x + screen_width * 0.01f;
                        Rectangle btn = {rm_kf_btn.x - button_width - screen_width * 0.01f, screen_height - timeline_height, button_width, button_height};

                        DrawRectangleRec(btn, RED);
                        DrawText(text, btn.x + btn.width / 2 - msr.x / 2, btn.y + btn.height / 2 - msr.y / 2, font_sz, WHITE);

                        if (!state.disable_timeline_interact && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, btn)) {
                            poser.kfs.clear();
                            poser.reset();
                        }
                    }
                }
            }

            // -- timeline

            if (state.disable_sliders) GuiDisable();
            // pose editor
            if (poser.kfs.size() > 0) {
                Pose* cur_pose = &poser.kfs[poser.kf].pose;

                {  // left

                    float slider_width = screen_width * 0.12f;
                    float slider_height = screen_height * 0.04f;

                    float ed_x = 0.0f;
                    float ed_y = screen_height * 0.25f;

                    // shoulder
                    Rectangle l_shoulder_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_shoulder_angle_slider, "", TextFormat("l shoulder angle: %.2f", cur_pose->l_shoulder_angle * RAD2DEG), &cur_pose->l_shoulder_angle, SHOULDER_LOWER_ANGLE, SHOULDER_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle l_shoulder_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_shoulder_force_slider, "", TextFormat("l shoulder force: %.2f", cur_pose->l_shoulder_force), &cur_pose->l_shoulder_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.l_shoulderJointId));

                    // elbow
                    ed_y += slider_height;
                    Rectangle l_elbow_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_elbow_angle_slider, "", TextFormat("l elbow angle: %.2f", cur_pose->l_elbow_angle * RAD2DEG), &cur_pose->l_elbow_angle, ELBOW_LOWER_ANGLE, ELBOW_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle l_elbow_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_elbow_force_slider, "", TextFormat("l elbow force: %.2f", cur_pose->l_elbow_force), &cur_pose->l_elbow_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.l_elbowJointId));

                    // hip
                    ed_y += slider_height;
                    Rectangle l_hip_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_hip_angle_slider, "", TextFormat("l hip angle: %.2f", cur_pose->l_hip_angle * RAD2DEG), &cur_pose->l_hip_angle, HIP_LOWER_ANGLE, HIP_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle l_hip_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_hip_force_slider, "", TextFormat("l hip force: %.2f", cur_pose->l_hip_force), &cur_pose->l_hip_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.l_hipJointId));

                    // knee
                    ed_y += slider_height;
                    Rectangle l_knee_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_knee_angle_slider, "", TextFormat("l knee angle: %.2f", cur_pose->l_knee_angle * RAD2DEG), &cur_pose->l_knee_angle, KNEE_LOWER_ANGLE, KNEE_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle l_knee_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_knee_force_slider, "", TextFormat("l knee force: %.2f", cur_pose->l_knee_force), &cur_pose->l_knee_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.l_kneeJointId));

                    // ankle
                    ed_y += slider_height;
                    Rectangle l_ankle_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_ankle_angle_slider, "", TextFormat("l ankle angle: %.2f", cur_pose->l_ankle_angle * RAD2DEG), &cur_pose->l_ankle_angle, ANKLE_LOWER_ANGLE, ANKLE_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle l_ankle_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(l_ankle_force_slider, "", TextFormat("l ankle force: %.2f", cur_pose->l_ankle_force), &cur_pose->l_ankle_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.l_ankleJointId));
                }  // left

                {  // right

                    float slider_width = screen_width * 0.12f;
                    float slider_height = screen_height * 0.04f;

                    float ed_x = screen_width - slider_width;
                    float ed_y = screen_height * 0.25f;

                    // shoulder
                    Rectangle r_shoulder_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_shoulder_angle_slider, TextFormat("r shoulder angle: %.2f", cur_pose->r_shoulder_angle * RAD2DEG), "", &cur_pose->r_shoulder_angle, SHOULDER_LOWER_ANGLE, SHOULDER_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle r_shoulder_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_shoulder_force_slider, TextFormat("r shoulder force: %.2f", cur_pose->r_shoulder_force), "", &cur_pose->r_shoulder_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.r_shoulderJointId));

                    // elbow
                    ed_y += slider_height;
                    Rectangle r_elbow_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_elbow_angle_slider, TextFormat("r elbow angle: %.2f", cur_pose->r_elbow_angle * RAD2DEG), "", &cur_pose->r_elbow_angle, ELBOW_LOWER_ANGLE, ELBOW_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle r_elbow_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_elbow_force_slider, TextFormat("r elbow force: %.2f", cur_pose->r_elbow_force), "", &cur_pose->r_elbow_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.r_elbowJointId));

                    // hip
                    ed_y += slider_height;
                    Rectangle r_hip_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_hip_angle_slider, TextFormat("r hip angle: %.2f", cur_pose->r_hip_angle * RAD2DEG), "", &cur_pose->r_hip_angle, HIP_LOWER_ANGLE, HIP_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle r_hip_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_hip_force_slider, TextFormat("r hip force: %.2f", cur_pose->r_hip_force), "", &cur_pose->r_hip_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.r_hipJointId));

                    // knee
                    ed_y += slider_height;
                    Rectangle r_knee_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_knee_angle_slider, TextFormat("r knee angle: %.2f", cur_pose->r_knee_angle * RAD2DEG), "", &cur_pose->r_knee_angle, KNEE_LOWER_ANGLE, KNEE_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle r_knee_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_knee_force_slider, TextFormat("r knee force: %.2f", cur_pose->r_knee_force), "", &cur_pose->r_knee_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.r_kneeJointId));

                    // ankle
                    ed_y += slider_height;
                    Rectangle r_ankle_angle_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_ankle_angle_slider, TextFormat("r ankle angle: %.2f", cur_pose->r_ankle_angle * RAD2DEG), "", &cur_pose->r_ankle_angle, ANKLE_LOWER_ANGLE, ANKLE_UPPER_ANGLE);

                    ed_y += slider_height;
                    Rectangle r_ankle_force_slider = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(r_ankle_force_slider, TextFormat("r ankle force: %.2f", cur_pose->r_ankle_force), "", &cur_pose->r_ankle_force, 0.0f, b2RevoluteJoint_GetMaxMotorTorque(psik.r_ankleJointId));
                }  // right

                {  // frame dur
                    float slider_width = screen_width * 0.15f;
                    float slider_height = screen_height * 0.04f;
                    state.ed_frame_dur = poser.kfs[poser.kf].frame_dur;

                    float ed_x = 0.0f;
                    float ed_y = screen_height - timeline_height - slider_height;

                    Rectangle frame_dur_rec = {ed_x, ed_y, slider_width, slider_height};
                    GuiSlider(frame_dur_rec, "", TextFormat("frame duration"), &state.ed_frame_dur, 0.0f, 100.0f);
                    int ed_dur = std::round(state.ed_frame_dur);
                    if (ed_dur != poser.kfs[poser.kf].frame_dur) {
                        poser.play = false;
                        poser.kfs[poser.kf].frame_dur = ed_dur;
                    }
                }  // frame dur

            }  // -- pose editor
        }
        if (state.disable_sliders) GuiEnable();

        {  // import export
            float button_height = timeline_height * 0.25f;
            float font_sz = button_height * 0.8f;
            Vector2 msr = MeasureTextEx(GetFontDefault(), "export", font_sz, 0.0f);
            float export_width = msr.x * 1.35f;
            Rectangle rec = {screen_width - export_width, 0.0f, export_width, button_height};

            DrawRectangleRec(rec, BLUE);
            DrawText("export", rec.x + rec.width / 2 - msr.x / 2, rec.y + rec.height / 2 - msr.y / 2, font_sz, WHITE);

            if (!state.disable_imp_exp && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, rec)) {
                fileDialogState = InitGuiWindowFileDialog(GetWorkingDirectory());
                fileDialogState.windowActive = true;
                fileDialogState.saveFileMode = true;
                is_export = true;
                state.disable_keybinds = true;
            }

            msr = MeasureTextEx(GetFontDefault(), "import", font_sz, 0.0f);
            float import_width = msr.x * 1.35f;
            rec = {screen_width - import_width - export_width * 1.25f, 0.0f, import_width, button_height};

            DrawRectangleRec(rec, BLUE);
            DrawText("import", rec.x + rec.width / 2 - msr.x / 2, rec.y + rec.height / 2 - msr.y / 2, font_sz, WHITE);

            if (!state.disable_imp_exp && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mouse_pos, rec)) {
                fileDialogState.windowActive = true;
                is_export = false;
                state.disable_keybinds = true;
            }
        }  // -- import export

        if (state.editing_name) {  // keyframe name popup
            float kf_name_rec_w = screen_width * 0.25;
            float kf_name_rec_h = screen_height * 0.18;
            Rectangle kf_name_rec = {screen_width / 2 - kf_name_rec_w / 2, screen_height / 2 - kf_name_rec_h / 2, kf_name_rec_w, kf_name_rec_h};
            int res = GuiTextInputBox(kf_name_rec, "keyframe name", "", "ok;cancel", state.ed_kf_name_text, KF_NAME_MAX_LEN, nullptr);
            switch (res) {
                case 1:  // ok
                    poser.kfs[state.ed_kf_name_idx].name = state.ed_kf_name_text;
                    memset(state.ed_kf_name_text, 0, KF_NAME_MAX_LEN);
                    state.exit_name_edit();
                    break;
                case 0:
                case 2:  // cancel
                    memset(state.ed_kf_name_text, 0, KF_NAME_MAX_LEN);
                    state.exit_name_edit();
                    break;
                case -1:
                    state.disable_keybinds = true;

                    break;
                default:
                    TraceLog(LOG_INFO, "unhandled: %d", res);
                    break;
            }
        }

        if (!state.error_str.empty()) {
            float err_rec_w = screen_width * 0.25;
            float err_rec_h = screen_height * 0.18;
            Rectangle err_rec = {screen_width / 2 - err_rec_w / 2, screen_height / 2 - err_rec_h / 2, err_rec_w, err_rec_h};
            if (GuiMessageBox(err_rec, "Error", state.error_str.c_str(), "ok") > 0) {
                state.error_str.clear();
            };
        }

        GuiUnlock();
        GuiWindowFileDialog(&fileDialogState);

        if (fileDialogState.SelectFilePressed) {
            char* filepath = fileDialogState.fileNameText;

            if (is_export) {
                export_animation(poser.kfs, filepath);
            } else {
                try {
                    std::vector<KF> new_anim = import_animation(filepath);
                    poser.reset();
                    poser.kfs = new_anim;
                } catch (Error error) {
                    switch (error) {
                        case ERROR_FILE_NOT_EXIST:
                            state.error_str = TextFormat("file does not exist: %s", filepath);
                            TraceLog(LOG_WARNING, state.error_str.c_str());
                            break;
                        case ERROR_INVALID_FILE:
                            state.error_str = TextFormat("invalid file: %s", filepath);
                            TraceLog(LOG_WARNING, state.error_str.c_str());
                            break;

                        default:
                            TraceLog(LOG_FATAL, "unreachable: %d", error);
                            break;
                    }
                };
            }

            fileDialogState.SelectFilePressed = false;
            state.disable_keybinds = false;
        }

        if (fileDialogState.CancelFilePressed) state.disable_keybinds = false;

        EndDrawing();
    }

    b2DestroyWorld(worldId);
    CloseWindow();
    return 0;
}
