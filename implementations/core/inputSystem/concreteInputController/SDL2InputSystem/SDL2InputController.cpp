#include "../headers\core\inputSystem\SDL2InputSystem\SDL2InputController.hpp"

SDL2InputController::SDL2InputController(){

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "Error in SDL Input SubSystem initialization: " << SDL_GetError() << std::endl;
    }

}

SDL2InputController::~SDL2InputController(){
    SDL_Quit();
}

//inline functions

inline bool SDL2InputController::check_button_pressed_down(ButtonState state) const{
    return state == ButtonState::PRESSED_DOWN;
}

inline bool SDL2InputController::check_button_pressed(ButtonState state) const{
    return state == ButtonState::PRESSED | state == ButtonState::PRESSED_DOWN;
}

inline bool SDL2InputController::check_button_released(ButtonState state) const{
    return state == ButtonState::RELEASED;
}

inline ButtonState SDL2InputController::get_keyboard_button_state(KeyButton button) const{
    auto state = this->keyboard_buttons.find(button);
    return state != this->keyboard_buttons.end() ? state->second : ButtonState::UNPRESSED;
}

inline ButtonState SDL2InputController::get_mouse_button_state(MouseButton button) const{
    auto state = this->mouse_buttons.find(button);
    return state != this->mouse_buttons.end() ? state->second : ButtonState::UNPRESSED;
}

inline ButtonState SDL2InputController::get_controller_button_state(int controller_id, ControllerButton button) const{
    auto controller_map = this->controller_buttons.find(controller_id);
    if(controller_map == this->controller_buttons.end()){
        std::cerr << "No controller binded with id: " << controller_id << std::endl;
        return ButtonState::UNPRESSED;
    }
    auto state = controller_map->second.find(button);
    return state != controller_map->second.end() ? state->second : ButtonState::UNPRESSED;
}


//Interface methods
// Polling methods for keyboard
bool SDL2InputController::key_pressed_down(KeyButton button) const{
    return this->check_button_pressed_down(this->get_keyboard_button_state(button));
}

bool SDL2InputController::key_pressed(KeyButton button) const{
    return this->check_button_pressed(this->get_keyboard_button_state(button));
}

bool SDL2InputController::key_released(KeyButton button) const{
    return this->check_button_released(this->get_keyboard_button_state(button)); 
}

bool SDL2InputController::bind_key_event(KeyButton button, ButtonState event, AbstractInputCommand action){
    this->keyboard_buttons_events.insert({{button, event}, action});
}

bool SDL2InputController::unbind_key_event(KeyButton button, ButtonState event){
    this->keyboard_buttons_events.erase({button, event});
}

// Mouse methods
void SDL2InputController::get_mouse_position(float& x, float& y) const{
    x = this->mouse_x;
    y = this->mouse_y;
}

void SDL2InputController::get_mouse_delta(float& dx, float& dy) const{
   dx = this->mouse_delta_x;
   dy = this->mouse_delta_y;
}


bool SDL2InputController::mouse_button_pressed_down(MouseButton button) const{
    return this->check_button_pressed_down(this->get_mouse_button_state(button));
}

bool SDL2InputController::mouse_button_pressed(MouseButton button) const{
    return this->check_button_pressed(this->get_mouse_button_state(button));
}

bool SDL2InputController::mouse_button_released(MouseButton button) const{
    return this->check_button_released(this->get_mouse_button_state(button));
}

bool SDL2InputController::bind_mouse_event(MouseButton button, ButtonState event, AbstractInputCommand action){
    this->mouse_buttons_events.insert({{button, event}, action});
}

bool SDL2InputController::unbind_mouse_event(MouseButton button, ButtonState event){
    this->mouse_buttons_events.erase({button, event});
}


// Controller methods
bool SDL2InputController::contoller_button_pressed_down(int controllerId, ControllerButton button) const{
    return this->check_button_pressed_down(this->get_controller_button_state(controllerId, button));
}

bool SDL2InputController::contoller_button_pressed(int controllerId, ControllerButton button) const{
    return this->check_button_pressed(this->get_controller_button_state(controllerId, button));
}

bool SDL2InputController::contoller_button_released(int controllerId, ControllerButton button) const{
    return this->check_button_released(this->get_controller_button_state(controllerId, button));
}
   
void SDL2InputController::get_controller_axis(int controllerId, ControllerAxis axis, float& value) const{
    auto controller_map = this->controller_axys.find(controllerId);
    auto controller_axis = controller_map->second.find(axis);
    value = controller_axis != controller_map->second.end() ? controller_axis->second : 0;
}

bool SDL2InputController::bind_controller_event(int controllerId, ControllerButton button, ButtonState event, AbstractInputCommand action){
    auto controller_map = this->controller_buttons_events.find(controllerId);
    controller_map->second.insert({{button, event}, action});
}

bool SDL2InputController::unbind_controller_event(int controllerId, ControllerButton button, ButtonState event){
    auto controller_map = this->controller_buttons_events.find(controllerId);
    controller_map->second.erase({button, event});
}

void SDL2InputController::update_loop(){

    SDL_Event event;

    while(this->running){
        while(SDL_PollEvent(&event)){
            
            /**
             * We get an sdl event, what we do with it...?
             * A class must have some knowledge on how to threat the event, who does?
             */

        }
    }

}