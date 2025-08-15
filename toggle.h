#pragma once

struct Toggles {
    bool display_normals = false;
    bool edit_mode = false;
    bool wireframe = false;
    bool terrain_edit = false;
};

void check_toggle_key(const Input* input, Toggles& toggles);