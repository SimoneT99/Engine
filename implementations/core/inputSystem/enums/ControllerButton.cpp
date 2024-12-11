#include "../headers/core/inputSystem/Enums/ControllerButton.hpp"

std::string ControllerButtonHelper::controllerButtonToString(ControllerButton controllerButton){
    switch(controllerButton){
        case ControllerButton::CONTROLLER_DPAD_UP: return "CONTROLLER_DPAD_UP";
        case ControllerButton::CONTROLLER_DPAD_RIGHT: return "CONTROLLER_DPAD_RIGHT";
        case ControllerButton::CONTROLLER_DPAD_DOWN: return "CONTROLLER_DPAD_DOWN";
        case ControllerButton::CONTROLLER_DPAD_LEFT: return "CONTROLLER_DPAD_LEFT";

        case ControllerButton::CONTROLLER_BUTTON_X: return "CONTROLLER_BUTTON_X";
        case ControllerButton::CONTROLLER_BUTTON_Y: return "CONTROLLER_BUTTON_Y";
        case ControllerButton::CONTROLLER_BUTTON_B: return "CONTROLLER_BUTTON_B";
        case ControllerButton::CONTROLLER_BUTTON_A: return "CONTROLLER_BUTTON_A";

        case ControllerButton::CONTROLLER_LEFTSTICK: return "CONTROLLER_LEFTSTICK";
        case ControllerButton::CONTROLLER_RIGHTSTICK: return "CONTROLLER_RIGHTSTICK";

        case ControllerButton::CONTROLLER_BACK: return "CONTROLLER_BACK";
        case ControllerButton::CONTROLLER_START: return "CONTROLLER_START";

        case ControllerButton::CONTROLLER_TOUCHPAD: return "CONTROLLER_TOUCHPAD";

        case ControllerButton::DEFAULT: return "DEFAULT";
        default: return "UNKNOWN";
    }
}

std::vector<ControllerButton> ControllerButtonHelper::getControllerButtons() {
    return {
        ControllerButton::CONTROLLER_DPAD_UP,
        ControllerButton::CONTROLLER_DPAD_RIGHT,
        ControllerButton::CONTROLLER_DPAD_DOWN,
        ControllerButton::CONTROLLER_DPAD_LEFT,
        ControllerButton::CONTROLLER_BUTTON_X,
        ControllerButton::CONTROLLER_BUTTON_Y,
        ControllerButton::CONTROLLER_BUTTON_B,
        ControllerButton::CONTROLLER_BUTTON_A,
        ControllerButton::CONTROLLER_LEFTSTICK,
        ControllerButton::CONTROLLER_RIGHTSTICK,
        ControllerButton::CONTROLLER_BACK,
        ControllerButton::CONTROLLER_START,
        ControllerButton::CONTROLLER_TOUCHPAD,
        ControllerButton::DEFAULT
    };
}