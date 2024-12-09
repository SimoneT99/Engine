#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\AbstractMouseManager.hpp"
#include <map>

class MouseManager : public AbstractButtonManager{

    private:
        std::map<MouseButton, ButtonState> mouse_buttons;
        std::map<std::pair<MouseButton, ButtonState>, AbstractInputCommand> mouse_buttons_events;
        
        inline ButtonState get_mouse_button_state(MouseButton button) const;

        float mouse_x;
        float mouse_y;

        float mouse_delta_x;
        float mouse_delta_y;

    public:
        void get_mouse_position(float& x, float& y) const;
        void get_mouse_delta(float& dx, float& dy) const;

        bool mouse_button_pressed_down(MouseButton button) const;
        bool mouse_button_pressed(MouseButton button) const;
        bool mouse_button_released(MouseButton button) const;

        bool bind_mouse_event(MouseButton button, ButtonState event, AbstractInputCommand action);
        bool unbind_mouse_event(MouseButton button, ButtonState event);
};