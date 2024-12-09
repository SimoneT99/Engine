#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\concreteManager\KeyboardManager.hpp"

inline ButtonState KeyboardManager::get_keyboard_button_state(KeyButton button) const{
    auto state = this->keyboard_buttons.find(button);
    return state != this->keyboard_buttons.end() ? state->second : ButtonState::UNPRESSED;
}

bool KeyboardManager::key_pressed_down(KeyButton button) const{
    return this->check_button_pressed_down(this->get_keyboard_button_state(button));
}

bool KeyboardManager::key_pressed(KeyButton button) const{
    return this->check_button_pressed(this->get_keyboard_button_state(button));
}

bool KeyboardManager::key_released(KeyButton button) const{
    return this->check_button_released(this->get_keyboard_button_state(button)); 
}

bool KeyboardManager::bind_key_event(KeyButton button, ButtonState event, AbstractInputCommand action){
    this->keyboard_buttons_events.insert({{button, event}, action});
}

bool KeyboardManager::unbind_key_event(KeyButton button, ButtonState event){
    this->keyboard_buttons_events.erase({button, event});
}
