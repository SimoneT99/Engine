#include <string>
#include <vector>

namespace Enums{

enum MouseButton{

    // Mouse Buttons
    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,

    MOUSE_4,
    MOUSE_5,
    MOUSE_6,
    MOUSE_7,
    MOUSE_8,

    DEFAULT
};

class MouseButtonHelper{

    public:
        static std::string mouseButtonToString(MouseButton mouseButton);
        static std::vector<MouseButton> getMouseButtons();
};

}