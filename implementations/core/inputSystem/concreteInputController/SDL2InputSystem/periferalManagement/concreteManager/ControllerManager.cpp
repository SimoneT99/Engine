#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\concreteManager\ControllerManager.hpp"

inline ButtonState ControllerManager::get_controller_button_state(ControllerButton button) const{
    auto state = this->controller_buttons.find(button);
    return state != this->controller_buttons.end() ? state->second : ButtonState::UNPRESSED;
}

bool ControllerManager::contoller_button_pressed_down(ControllerButton button) const{
    return this->check_button_pressed_down(this->get_controller_button_state(button));
}

bool ControllerManager::contoller_button_pressed(ControllerButton button) const{
    return this->check_button_pressed(this->get_controller_button_state(button));
}

bool ControllerManager::contoller_button_released(ControllerButton button) const{
    return this->check_button_released(this->get_controller_button_state(button));
}
   
void ControllerManager::get_controller_axis(ControllerAxis axis, float& value) const{
    auto controller_axis = this->controller_axis.find(axis);
    value = controller_axis != this->controller_axis.end() ? controller_axis->second : 0;
}

bool ControllerManager::bind_controller_event(ControllerButton button, ButtonState event, AbstractInputCommand action){
    this->controller_buttons_events.insert({{button, event}, action});
}

bool ControllerManager::unbind_controller_event(ControllerButton button, ButtonState event){
    this->controller_buttons_events.erase({button, event});
}