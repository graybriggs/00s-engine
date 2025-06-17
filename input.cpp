
#include "input.h"

Input::Input():
    key{false}
{

}

void Input::set_mouse_cursor(double x, double y) {
    cursor_pos = {x, y};
}

mouse_cursor_pos Input::get_cursor_pos() {
    return { cursor_pos.xpos, cursor_pos.ypos };
}