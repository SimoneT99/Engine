#include "../headers/core/inputSystem/Enums/ControllerAxis.hpp"

std::string ControllerAxisHelper::controllerAxisToString(ControllerAxis controllerAxis){
    switch(controllerAxis){
        case ControllerAxis::CONTROLLER_LEFT_VERICAL_AXIS: return "CONTROLLER_LEFT_VERICAL_AXIS";
        case ControllerAxis::CONTROLLER_LEFT_HORIZONTAL_AXIS: return "CONTROLLER_LEFT_HORIZONTAL_AXIS";

        case ControllerAxis::CONTROLLER_RIGHT_VERICAL_AXIS: return "CONTROLLER_RIGHT_VERICAL_AXIS";
        case ControllerAxis::CONTROLLER_RIGHT_HORIZONTAL_AXIS: return "CONTROLLER_RIGHT_HORIZONTAL_AXIS";

        case ControllerAxis::CONTROLLER_LEFT_TRIGGER_AXIS: return "CONTROLLER_LEFT_TRIGGER_AXIS";
        case ControllerAxis::CONTROLLER_RIGHT_TRIGGER_AXIS: return "CONTROLLER_RIGHT_TRIGGER_AXIS";

        case ControllerAxis::DEFAULT: return "DEFAULT";
        default: return "UNKNOWN";
    }
}

std::vector<ControllerAxis> getControllerAxisVector() {
    return {
        ControllerAxis::CONTROLLER_LEFT_VERICAL_AXIS,
        ControllerAxis::CONTROLLER_LEFT_HORIZONTAL_AXIS,
        ControllerAxis::CONTROLLER_RIGHT_VERICAL_AXIS,
        ControllerAxis::CONTROLLER_RIGHT_HORIZONTAL_AXIS,
        ControllerAxis::CONTROLLER_LEFT_TRIGGER_AXIS,
        ControllerAxis::CONTROLLER_RIGHT_TRIGGER_AXIS,
        ControllerAxis::DEFAULT
    };
}