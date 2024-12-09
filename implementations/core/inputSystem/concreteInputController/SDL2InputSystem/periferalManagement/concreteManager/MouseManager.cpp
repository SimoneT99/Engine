#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\concreteManager\MouseManager.hpp"

inline ButtonState MouseManager::get_mouse_button_state(MouseButton button) const{
    auto state = this->mouse_buttons.find(button);
    return state != this->mouse_buttons.end() ? state->second : ButtonState::UNPRESSED;
}

/**
 * BAD: possible race condition!
 */

void MouseManager::get_mouse_delta(float& dx, float& dy) const{
    dx = this->mouse_delta_x;
    dy = this->mouse_delta_y;

}

void MouseManager::get_mouse_position(float& x, float& y) const{
    x = this->mouse_x;
    y = this->mouse_y;
}


bool MouseManager::mouse_button_pressed_down(MouseButton button) const{
    return this->check_button_pressed_down(this->get_mouse_button_state(button));
}

bool MouseManager::mouse_button_pressed(MouseButton button) const{
    return this->check_button_pressed(this->get_mouse_button_state(button));
}

bool MouseManager::mouse_button_released(MouseButton button) const{
    return this->check_button_released(this->get_mouse_button_state(button));
}


bool MouseManager::bind_mouse_event(MouseButton button, ButtonState event, AbstractInputCommand action){
    this->mouse_buttons_events.insert({{button, event}, action});
}

bool MouseManager::unbind_mouse_event(MouseButton button, ButtonState event){
    this->mouse_buttons_events.erase({button, event});
}
