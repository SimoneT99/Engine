#include "../headers/core/inputSystem/Enums/MouseButton.hpp"

std::string mouseButtonToString(MouseButton mouseButton){

    switch (mouseButton) {
        case MouseButton::MOUSE_LEFT: return "MOUSE_LEFT";
        case MouseButton::MOUSE_RIGHT: return "MOUSE_RIGHT";
        case MouseButton::MOUSE_MIDDLE: return "MOUSE_MIDDLE";

        case MouseButton::MOUSE_4: return "MOUSE_4";
        case MouseButton::MOUSE_5: return "MOUSE_5";
        case MouseButton::MOUSE_6: return "MOUSE_6";
        case MouseButton::MOUSE_7: return "MOUSE_7";
        case MouseButton::MOUSE_8: return "MOUSE_8";

        case MouseButton::DEFAULT: return "DEFAULT";
        default: return "UNKNOWN";
    }

}

std::vector<MouseButton> getMouseButtons() {
    return {
        MouseButton::MOUSE_LEFT,
        MouseButton::MOUSE_RIGHT,
        MouseButton::MOUSE_MIDDLE,
        MouseButton::MOUSE_4,
        MouseButton::MOUSE_5,
        MouseButton::MOUSE_6,
        MouseButton::MOUSE_7,
        MouseButton::MOUSE_8,
        MouseButton::DEFAULT
    };
}