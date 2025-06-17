
#include "input.h"

Input::Input()
{
    left_mouse_click = false;
}


void Input::set_mouse_cursor(double x, double y) {
    cursor_pos = {x, y};
}

mouse_cursor_pos Input::get_cursor_pos() {
    return { cursor_pos.xpos, cursor_pos.ypos };
}

void Input::set_left_mouse_click() {
    left_mouse_click = true;
}

void Input::set_left_mouse_release() {
    left_mouse_click = false;
}

bool Input::get_left_mouse_button_state() {
    return left_mouse_click;
}

