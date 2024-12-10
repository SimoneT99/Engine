#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\AbstractControllerManager.hpp"
#include "AbstractButtonManager.hpp"
#include <map>

class ControllerManager : public AbstractControllerManager{

    private:
        std::map<ControllerButton, ButtonState> controller_buttons;
        std::map<std::pair<ControllerButton, ButtonState>, AbstractInputCommand> controller_buttons_events;
        std::map<ControllerAxis, float> controller_axis;

        inline ButtonState get_controller_button_state(ControllerButton button) const;

    public:
        bool contoller_button_pressed_down(ControllerButton button) const override;
        bool contoller_button_pressed(ControllerButton button) const override;
        bool contoller_button_released(ControllerButton button) const override;
    
        void get_controller_axis(ControllerAxis axis, float& value) const override;

        bool bind_controller_event(ControllerButton button, ButtonState event, AbstractInputCommand action) override;
        bool unbind_controller_event(ControllerButton button, ButtonState event) override;
};