#include "mmenu.h"

Menu::Menu() {
    neon_font = LoadFont(TextFormat("%s/data/fonts/neon_pixel-7.ttf", GetWorkingDirectory()));
    bitroad_font = LoadFont(TextFormat("%s/data/fonts/Bitroad_demo.otf", GetWorkingDirectory()));
    hokjesgeest_font = LoadFont(TextFormat("%s/data/fonts/Hokjesgeest.otf", GetWorkingDirectory()));
    pointless_font = LoadFont(TextFormat("%s/data/fonts/Pointless.ttf", GetWorkingDirectory()));

    // SetTextureFilter(neon_font.texture, TEXTURE_FILTER_POINT);
    // SetTextureFilter(bitroad_font.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(hokjesgeest_font.texture, TEXTURE_FILTER_POINT);
}

void Menu::update(float dt) {
}

void Menu::draw() {
    int screen_width = GetRenderWidth();
    int screen_height = GetRenderHeight();
    Vector2 mouse_pos = GetMousePosition();

    ClearBackground(GetColor(0x1f1f1fff));
    TraceLog(LOG_INFO, "%d", screen_height);

    const char* title = "MORTAL";
    float title_fsz = screen_height * 0.119f;
    float title_spc = 0.0f;
    Vector2 title_msr = MeasureTextEx(hokjesgeest_font, title, title_fsz, title_spc);
    Vector2 title_pos = {screen_width / 2.0f - title_msr.x / 2, title_msr.y * 2};
    DrawTextEx(hokjesgeest_font, title, title_pos, title_fsz, title_spc, WHITE);

    const char* editor_btn_txt = "EDITOR";
    float editor_btn_fsz = title_fsz * 0.35f;
    float editor_btn_spc = 0.0f;
    Vector2 editor_btn_msr = MeasureTextEx(pointless_font, editor_btn_txt, editor_btn_fsz, editor_btn_spc);

    float side_padding = editor_btn_fsz * 0.8f;
    float editor_btn_w = editor_btn_msr.x + side_padding * 2;
    float editor_btn_h = editor_btn_msr.y + side_padding;
    Rectangle editor_btn_rec = {
        screen_width / 2.0f - editor_btn_w / 2.0f,
        screen_height / 2.0f,
        editor_btn_w,
        editor_btn_h,
    };

    bool editor_btn_hvr = CheckCollisionPointRec(mouse_pos, editor_btn_rec);
    Color btn_color = editor_btn_hvr ? GetColor(0x3f3f3fff) : GetColor(0x2f2f2fff);
    Vector2 editor_btn_pos = {editor_btn_rec.x + editor_btn_rec.width / 2.0f - editor_btn_msr.x / 2.0f, editor_btn_rec.y + editor_btn_rec.height / 2.0f - editor_btn_msr.y / 2.0f};

    DrawRectangleRec(editor_btn_rec, btn_color);
    DrawTextEx(pointless_font, editor_btn_txt, editor_btn_pos, editor_btn_fsz, editor_btn_spc, WHITE);

    if (editor_btn_hvr && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (onclick_editor != nullptr) onclick_editor();
    }
}
