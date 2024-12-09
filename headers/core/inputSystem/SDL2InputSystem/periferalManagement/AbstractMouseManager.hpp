#include "../headers/core/inputSystem/Enums/MouseButton.hpp"
#include "../headers/core/inputSystem/Enums/ButtonState.hpp"
#include "../headers/core/inputSystem/AbstractInputCommand.hpp"
#include "AbstractButtonManager.hpp"
#include <map>

class AbstractMouseManager : public AbstractButtonManager{

    public:
        virtual void get_mouse_position(float& x, float& y) const = 0;
        virtual void get_mouse_delta(float& dx, float& dy) const = 0;

        virtual bool mouse_button_pressed_down(MouseButton button) const = 0;
        virtual bool mouse_button_pressed(MouseButton button) const = 0;
        virtual bool mouse_button_released(MouseButton button) const = 0;

        virtual bool bind_mouse_event(MouseButton button, ButtonState event, AbstractInputCommand action) = 0;
        virtual bool unbind_mouse_event(MouseButton button, ButtonState event) = 0;
};