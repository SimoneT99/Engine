#include "../headers/core/inputSystem/Enums/Enums.hpp"
#include "AbstractInputCommand.hpp"
#include <memory>

/**
 * @brief: Interface of the input system, each system must implement these methods to be usable by the engine.
 * BAD: Smell of fat interface... ...but it's a whole system...
 * ISSUE: Who has the responsability to manage the possible race conditions?
 */
class InputControllerInterface
{

public:
    /**
     * Keyboard methods
     */

    /// @brief Allows to poll the system to check if the passed key has been pressed down
    /// @param button The button to check
    /// @return True if the button is pressed down
    virtual bool key_pressed_down(Enums::KeyButton button) const = 0;

    /// @brief Allows to poll the system to check if the passed key has been pressed down
    /// @param button The button to check
    /// @return True if the button is pressed
    virtual bool key_pressed(Enums::KeyButton button) const = 0;

    /// @brief Allows to poll the system to check if the passed key has been released
    /// @param button The button to check
    /// @return True if the button has been released
    virtual bool key_released(Enums::KeyButton button) const = 0;

    /// @brief Allows to bind a key button event to an executable command
    /// @brief NOTE: At the moment only one event is supported at any time for a button
    /// @param button The button to bind
    /// @param event The event to bind
    /// @param action The action to perform
    virtual void bind_key_event(Enums::KeyButton button, Enums::ButtonEvent event, std::unique_ptr<AbstractInputCommand> action) = 0;

    /// @brief Allows to unbind a key button event to an executable command
    /// @param button The button tu unbind
    /// @param event The event to unbind
    virtual void unbind_key_event(Enums::KeyButton button, Enums::ButtonEvent event) = 0;

    /**
     * Mouse methods
     */

    /// @brief Allows to get the mouse raw position
    /// @param x The parameter in wich you want to set the x position
    /// @param y The parameter in wich you want to set the y position
    virtual void get_mouse_position(float &x, float &y) const = 0;

    /// @brief Allows to get the mouse movement delta position
    /// @param dx The parameter in wich you want to set the x delta position
    /// @param dy The parameter in wich you want to set the y delta position
    virtual void get_mouse_delta(float &dx, float &dy) const = 0;

    /// @brief Allows to get the mouse wheel delta
    /// @param dx The parameter in wich you want to set the x delta position
    /// @param dy The parameter in wich you want to set the y delta position
    virtual void get_mouse_wheel_delta(float &dx, float &dy) const = 0;

    /// @brief Allows to poll the system to check if the passed mouse button has been pressed down
    /// @param button The button to check
    /// @return True if the button is pressed down
    virtual bool mouse_button_pressed_down(Enums::MouseButton button) const = 0;

    /// @brief Allows to poll the system to check if the passed mouse button has been pressed down
    /// @param button The button to check
    /// @return True if the button is pressed
    virtual bool mouse_button_pressed(Enums::MouseButton button) const = 0;

    /// @brief Allows to poll the system to check if the passed mouse button has been released
    /// @param button The button to check
    /// @return True if the button has been released
    virtual bool mouse_button_released(Enums::MouseButton button) const = 0;

    /// @brief Allows to bind a mouse button button event to an executable command
    /// @brief NOTE: At the moment only one event is supported at any time for a button
    /// @param button The button to bind
    /// @param event The event to bind
    /// @param action The action to perform
    virtual void bind_mouse_event(Enums::MouseButton button, Enums::ButtonEvent event, std::unique_ptr<AbstractInputCommand> action) = 0;

    /// @brief Allows to unbind a mouse button button event to an executable command
    /// @param button The button tu unbind
    /// @param event The event to unbind
    virtual void unbind_mouse_event(Enums::MouseButton button, Enums::ButtonEvent event) = 0;

    /**
     * Controller methods
     */

    /// @brief Allows to poll the system to check if the passed controller button has been pressed down
    /// @param controllerId The button to check
    /// @param button True if the button is pressed down
    /// @return
    virtual bool controller_button_pressed_down(int controllerId, Enums::ControllerButton button) const = 0;

    /// @brief Allows to poll the system to check if the passed controller button has been pressed down
    /// @param controllerId the id of the controller to check the button of
    /// @param button The button to check
    /// @return True if the button is pressed
    virtual bool controller_button_pressed(int controllerId, Enums::ControllerButton button) const = 0;

    /// @brief Allows to poll the system to check if the passed controller button has been released
    /// @brief NOTE: At the moment only one event is supported at any time for a button
    /// @param controllerId the id of the controller to check the button of
    /// @param button The button to check
    /// @return True if the button  has been released
    virtual bool controller_button_released(int controllerId, Enums::ControllerButton button) const = 0;

    /// @brief Allow to get the axis value
    /// @param controllerId The id of the controller to check the axis of
    /// @param axis The axis to retrive the value of
    /// @param value A reference to the location in wich put the value. Value is in the [-1,1] interval.
    virtual void get_controller_axis(int controllerId, Enums::ControllerAxis axis, float &value) const = 0;

    /// @brief Allows to bind a controller button button event to an executable command
    /// @param controllerId The id of the controller to bind the button of
    /// @param button The button of to bind the event to
    /// @param event The button of to bind
    /// @param action The action to perform
    virtual void bind_controller_event(int controllerId, Enums::ControllerButton button, Enums::ButtonEvent event, std::unique_ptr<AbstractInputCommand> action) = 0;

    /// @brief Allows to unbind a controller button button event to an executable command
    /// @param controllerId The id of the controller to unbind the button of
    /// @param button The button of to unbind the button from
    /// @param event The event to unbind
    virtual void unbind_controller_event(int controllerId, Enums::ControllerButton button, Enums::ButtonEvent event) = 0;

    /**
     * Hook to bind the input system to some tick rate of other system
     */

    /// @brief allow to check if the system is tick bounded, if true the underlying system will use the tick function
    ///        to continue it'operations, the behaviour is dependent on the concrete underlying system
    /// @return true if binded to the tick rate, false otherwise
    virtual bool is_binded() = 0;

    /// @brief allow to signal a "tick" to the input system
    virtual void tick() = 0;
};