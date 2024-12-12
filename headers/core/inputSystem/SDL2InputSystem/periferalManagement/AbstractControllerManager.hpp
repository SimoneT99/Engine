#include "../headers/core/inputSystem/Enums/ControllerButton.hpp"
#include "../headers/core/inputSystem/Enums/ButtonState.hpp"
#include "../headers/core/inputSystem/Enums/ControllerAxis.hpp"
#include "../headers/core/inputSystem/AbstractInputCommand.hpp"
#include "AbstractButtonManager.hpp"
#include <map>

class AbstractControllerManager : public AbstractButtonManager{

    public:
        virtual bool controller_button_pressed_down(ControllerButton button) const = 0;
        virtual bool controller_button_pressed(ControllerButton button) const = 0;
        virtual bool controller_button_released(ControllerButton button) const = 0;
    
        virtual void get_controller_axis(ControllerAxis axis, float& value) const = 0;

        virtual bool bind_controller_event(ControllerButton button, ButtonState event, AbstractInputCommand action) = 0;
        virtual bool unbind_controller_event(ControllerButton button, ButtonState event) = 0;

        /**
         * Note: value will be clamped in a [-1,1] interval
         */
        virtual void set_axis(ControllerAxis axis, float value);

        virtual void press_button(ControllerButton button);
        virtual void release_button(ControllerButton button);

};