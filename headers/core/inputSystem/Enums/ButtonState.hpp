#include <string>
#include <vector>

namespace Enums{

        enum ButtonState{

        PRESSED_DOWN,
        PRESSED,
        RELEASED,
        UNPRESSED
    };

    /**
     * Better solutions are welcome...
     */

    class ButtonStateHelper{

        public:
            static std::string buttonStateToString(ButtonState buttonState);
            static std::vector<ButtonState> getButtonState();
    };

}

