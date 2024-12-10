#include "../headers\core\inputSystem\InputControllerInterface.hpp"
#include "../include/SDL2/SDL.h"
#include "../headers/core/inputSystem/Enums/ButtonState.hpp"
#include "../headers/core/inputSystem/AbstractInputCommand.hpp"

#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractMouseManager.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractKeyboardManager.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractControllerManager.hpp"

#include <iostream>
#include <map>

class SDL2InputController : public AbstractInputController {

    private:
        //States

        /**
         * Managers. (i know it's a bad name...).
         * TODO: who build and manages these? We need dependency injection somehow? Builder maybe?
         */
        std::shared_ptr<AbstractMouseManager> mouse_manager;
        std::shared_ptr<AbstractKeyboardManager> keyboard_manager;
        std::map<int, std::shared_ptr<AbstractControllerManager>> controller_managers;

        /**
         * Chain of responsability to handle the events
         * TODO: how do we manage this chain? we could add or remove nodes to allow less or more inputs...
         */

        std::atomic<bool> running = false;

    protected:

        void update_loop();


    public:
    SDL2InputController();
    ~SDL2InputController();

    // Polling methods for keyboard
    bool key_pressed_down(KeyButton button) const override;
    bool key_pressed(KeyButton button) const override;
    bool key_released(KeyButton button) const override;

    bool bind_key_event(KeyButton button, ButtonState event, AbstractInputCommand action) override;
    bool unbind_key_event(KeyButton button, ButtonState event) override;

    // Mouse methods
    void get_mouse_position(float& x, float& y) const override;
    void get_mouse_delta(float& dx, float& dy) const override;
    void get_mouse_wheel_delta(float& dx, float& dy) const override;

    bool mouse_button_pressed_down(MouseButton button) const override;
    bool mouse_button_pressed(MouseButton button) const override;
    bool mouse_button_released(MouseButton button) const override;

    bool bind_mouse_event(MouseButton button, ButtonState event, AbstractInputCommand action) override;
    bool unbind_mouse_event(MouseButton button, ButtonState event) override;

    // Controller methods
    bool contoller_button_pressed_down(int controllerId, ControllerButton button) const override;
    bool contoller_button_pressed(int controllerId, ControllerButton button) const override;
    bool contoller_button_released(int controllerId, ControllerButton button) const override;
    
    void get_controller_axis(int controllerId, ControllerAxis axis, float& value) const override;

    bool bind_controller_event(int controllerId, ControllerButton button, ButtonState event, AbstractInputCommand action) override;
    bool unbind_controller_event(int controllerId, ControllerButton button, ButtonState event) override;
};