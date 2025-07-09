#pragma once

#include <array>



struct mouse_cursor_pos {
    double xpos;
    double ypos;
};

class Input {
public:
    
    Input();
    void set_mouse_cursor(double x, double y);
    mouse_cursor_pos get_cursor_pos();
    void set_left_mouse_click();
    void set_left_mouse_release();
    bool get_left_mouse_button_state();
//private:
    std::array<bool, 8> key{};
    mouse_cursor_pos cursor_pos;
    bool left_mouse_click;
};