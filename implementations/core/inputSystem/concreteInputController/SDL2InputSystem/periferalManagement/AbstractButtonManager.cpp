#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\AbstractButtonManager.hpp"

inline bool AbstractButtonManager::check_button_pressed_down(ButtonState state) const{
    return state == ButtonState::PRESSED_DOWN;
}

inline bool AbstractButtonManager::check_button_pressed(ButtonState state) const{
    return state == ButtonState::PRESSED | state == ButtonState::PRESSED_DOWN;
}

inline bool AbstractButtonManager::check_button_released(ButtonState state) const{
    return state == ButtonState::RELEASED;
}
