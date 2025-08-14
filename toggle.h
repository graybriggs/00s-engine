#pragma once

struct Toggles {
    bool display_normals = false;
    bool edit_mode = false;
    bool wireframe = false;
};

void check_toggle_key(Input* input, Toggles& toggles);