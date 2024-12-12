#include "../headers\core\inputSystem\InputControllerInterface.hpp"
#include "../include/SDL2/SDL.h"
#include "../headers/core/inputSystem/AbstractInputCommand.hpp"

#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractMouseManager.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractKeyboardManager.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractControllerManager.hpp"

#include <iostream>
#include <map>

class SDL2InputController : public InputControllerInterface {

    private:
    
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

        /**
         * Interface methods
         */

        // Polling methods for keyboard
        bool key_pressed_down(Enums::KeyButton button) const override;
        bool key_pressed(Enums::KeyButton button) const override;
        bool key_released(Enums::KeyButton button) const override;

        void bind_key_event(Enums::KeyButton button, Enums::ButtonEvent event, std::unique_ptr<AbstractInputCommand> action) override;
        void unbind_key_event(Enums::KeyButton button, Enums::ButtonEvent event) override;

        // Mouse methods
        void get_mouse_position(float& x, float& y) const override;
        void get_mouse_delta(float& dx, float& dy) const override;
        void get_mouse_wheel_delta(float& dx, float& dy) const override;

        bool mouse_button_pressed_down(Enums::MouseButton button) const override;
        bool mouse_button_pressed(Enums::MouseButton button) const override;
        bool mouse_button_released(Enums::MouseButton button) const override;

        void bind_mouse_event(Enums::MouseButton button, Enums::ButtonEvent event, std::unique_ptr<AbstractInputCommand> action) override;
        void unbind_mouse_event(Enums::MouseButton button, Enums::ButtonEvent event) override;

        // Controller methods
        bool controller_button_pressed_down(int controllerId, Enums::ControllerButton button) const override;
        bool controller_button_pressed(int controllerId, Enums::ControllerButton button) const override;
        bool controller_button_released(int controllerId, Enums::ControllerButton button) const override;
        
        void get_controller_axis(int controllerId, Enums::ControllerAxis axis, float& value) const override;

        void bind_controller_event(int controllerId, Enums::ControllerButton button, Enums::ButtonEvent event, std::unique_ptr<AbstractInputCommand> action) override;
        void unbind_controller_event(int controllerId, Enums::ControllerButton button, Enums::ButtonEvent event) override;

        virtual bool is_binded() = 0;
        virtual void tick() = 0;

        /**
         * Methods used to setup or manage internally the system
         */

        void set_keyboard_manager(std::shared_ptr<AbstractKeyboardManager> keyboardManager);
        void set_mouse_manager(std::shared_ptr<AbstractMouseManager> mouseManager);

};