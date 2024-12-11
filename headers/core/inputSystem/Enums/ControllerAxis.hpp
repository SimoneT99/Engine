#include <string>
#include <vector>

namespace Enums{

    enum class ControllerAxis {

        //controller buttons
        CONTROLLER_LEFT_VERICAL_AXIS,
        CONTROLLER_LEFT_HORIZONTAL_AXIS,

        CONTROLLER_RIGHT_VERICAL_AXIS,
        CONTROLLER_RIGHT_HORIZONTAL_AXIS,

        CONTROLLER_LEFT_TRIGGER_AXIS,
        CONTROLLER_RIGHT_TRIGGER_AXIS,

        DEFAULT
    };

    class ControllerAxisHelper{

        public:
            static std::string controllerAxisToString(ControllerAxis controllerAxis);
            static std::vector<ControllerAxis> getControllerAxis();
    };

}  