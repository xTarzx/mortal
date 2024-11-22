#pragma once

#include "gui_window_file_dialog.h"

#include "box2d/box2d.h"

#include "psik.h"
#include "ground.h"
#include "pose.h"
#include "poses.h"

struct EditorState {
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

    void enter_name_edit();

    void exit_name_edit();

    void enter_timeline_drag();

    void exit_timeline_drag();
};

class Editor {
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    b2WorldDef worldDef;
    b2WorldId worldId;
    Psik psik;
    Ground ground;

    std::vector<KF> kfs;
    Poser poser;

    Camera2D camera;
    float camera_speed = 150.0f;
    float zoom_speed = 1.0f;

    EditorState state;
    GuiWindowFileDialogState fileDialogState;
    bool is_export;

   public:
    Editor();
    ~Editor();

    void update(float dt);
    void draw();
};