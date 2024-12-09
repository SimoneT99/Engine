#include "KeyButton.hpp"
#include "MouseButton.hpp"
#include "ControllerButton.hpp"
#include "ControllerAxis.hpp"
#include "AbstractInputCommand.hpp"

/**
 * Interface of the input system
 * BAD: Smell of fat interface...
 */

class AbstractInputController {

public:
    virtual ~AbstractInputController() = default;

    // Polling methods for keyboard
    virtual bool key_pressed_down(KeyButton button) const = 0;
    virtual bool key_pressed(KeyButton button) const = 0;
    virtual bool key_released(KeyButton button) const = 0;

    virtual bool bind_key_event(KeyButton button, ButtonState event, AbstractInputCommand action) = 0;
    virtual bool unbind_key_event(KeyButton button, ButtonState event) = 0;

    // Mouse methods
    virtual void get_mouse_position(float& x, float& y) const = 0;
    virtual void get_mouse_delta(float& dx, float& dy) const = 0;

    virtual bool mouse_button_pressed_down(MouseButton button) const = 0;
    virtual bool mouse_button_pressed(MouseButton button) const = 0;
    virtual bool mouse_button_released(MouseButton button) const = 0;

    virtual bool bind_mouse_event(MouseButton button, ButtonState event, AbstractInputCommand action) = 0;
    virtual bool unbind_mouse_event(MouseButton button, ButtonState event) = 0;

    // Controller methods
    virtual bool contoller_button_pressed_down(int controllerId, ControllerButton button) const = 0;
    virtual bool contoller_button_pressed(int controllerId, ControllerButton button) const = 0;
    virtual bool contoller_button_released(int controllerId, ControllerButton button) const = 0;
    
    virtual void get_controller_axis(int controllerId, ControllerAxis axis, float& value) const = 0;

    virtual bool bind_controller_event(int controllerId, ControllerButton button, ButtonState event, AbstractInputCommand action) = 0;
    virtual bool unbind_controller_event(int controllerId, ControllerButton button, ButtonState event) = 0;
};