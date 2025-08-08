
#include "input.h"

#include <iostream>

Input::Input()
{
    left_mouse_click = false;
}

// perhaps keep this as type double in device and convert here??
void Input::set_mouse_cursor(int x, int y) {
    cursor_pos = {x, y};
}

mouse_cursor_pos Input::get_cursor_pos() {
    
    cursor_pos.xpos;
    cursor_pos.ypos;

    return cursor_pos;
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

