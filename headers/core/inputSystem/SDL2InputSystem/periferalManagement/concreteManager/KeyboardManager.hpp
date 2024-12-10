#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\AbstractKeyboardManager.hpp"

#include <map>

class KeyboardManager : public AbstractKeyboardManager{

    private:        
        std::map<KeyButton, ButtonState> keyboard_buttons;
        std::map<std::pair<KeyButton, ButtonState>, AbstractInputCommand> keyboard_buttons_events;
        
        inline ButtonState get_keyboard_button_state(KeyButton button) const;
    
    public:
        bool key_pressed_down(KeyButton button) const override;
        bool key_pressed(KeyButton button) const override;
        bool key_released(KeyButton button) const override;

        bool bind_key_event(KeyButton button, ButtonState event, AbstractInputCommand action) override;
        bool unbind_key_event(KeyButton button, ButtonState event) override;

        void press_button(KeyButton button) override;
        void release_button(KeyButton button) override;
};