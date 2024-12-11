#include <string>
#include <vector>

namespace Enums{

    enum class ControllerButton {

    //controller buttons
    CONTROLLER_DPAD_UP,
    CONTROLLER_DPAD_RIGHT,
    CONTROLLER_DPAD_DOWN,
    CONTROLLER_DPAD_LEFT,

    CONTROLLER_BUTTON_X,
    CONTROLLER_BUTTON_Y,
    CONTROLLER_BUTTON_B,
    CONTROLLER_BUTTON_A,

    CONTROLLER_LEFTSTICK,
    CONTROLLER_RIGHTSTICK,

    CONTROLLER_BACK,
    CONTROLLER_START,

    CONTROLLER_TOUCHPAD,
    
    DEFAULT
};

class ControllerButtonHelper{

    public:
        static std::string controllerButtonToString(ControllerButton controllerButton);
        static std::vector<ControllerButton> getControllerButtons();
};

}