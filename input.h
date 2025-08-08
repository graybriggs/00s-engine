#pragma once

#include <array>



struct mouse_cursor_pos {
    int xpos;
    int ypos;
};

class Input {
public:
    
    Input();
    void set_mouse_cursor(int x, int y);
    mouse_cursor_pos get_cursor_pos();
    void set_left_mouse_click();
    void set_left_mouse_release();
    bool get_left_mouse_button_state();
//private:
    std::array<bool, 40> key{};
    mouse_cursor_pos cursor_pos;
    bool left_mouse_click;
};