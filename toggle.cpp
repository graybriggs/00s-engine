
#include "input.h"
#include "key.h"
#include "toggle.h"

#include <iostream>

void check_toggle_key(const Input* input, Toggles& toggles) {
    if (input->key[Key_N] && !input->previous_key[Key_N]) {
        if (toggles.display_normals) {
            toggles.display_normals = false;
            std::cout << "Normals: OFF\n";
        }
        else {
            toggles.display_normals = true;
            std::cout << "Normals: ON\n";
        }
    }
    if (input->key[Key_E] && !input->previous_key[Key_E]) {
        if (toggles.edit_mode) {
            toggles.edit_mode = false;
            std::cout << "Edit mode: OFF\n";
        }
        else {
            toggles.edit_mode = true;
            std::cout << "Edit mode: ON\n";
        }
    }
    if (input->key[Key_NUM1] && !input->previous_key[Key_NUM1]) {
        if (toggles.wireframe) {
            toggles.wireframe = false;
            std::cout << "Wireframe mode: OFF\n";
        }
        else {
            toggles.wireframe = true;
            std::cout << "Wireframe mode: ON\n";
        }
    }
    if (input->key[Key_T] && !input->previous_key[Key_T]) {
        if (toggles.terrain_edit) {
            toggles.terrain_edit = false;
            std::cout << "Terrain Edit mode: OFF\n";
        }
        else {
            toggles.terrain_edit = true;
            std::cout << "Terrain Edit mode: ON\n";
        }
    }
}