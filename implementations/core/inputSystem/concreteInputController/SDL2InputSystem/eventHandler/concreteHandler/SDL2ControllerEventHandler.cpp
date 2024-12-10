#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/eventHandler/concreteHandler/SDL2ControllerEventHandler.hpp"

inline float SDL2ControllerEventHandler::normalize_SDL2_axis(int value) const{
  return value * this->scaling_factor - this->translation_factor;
}

bool SDL2ControllerEventHandler::can_handle(SDL_Event event) const{
  return (event.type == SDL_CONTROLLERAXISMOTION && event.caxis.which == this->controller_id) ||
         (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.which == this->controller_id) ||
         (event.type == SDL_CONTROLLERBUTTONUP && event.cbutton.which == this->controller_id);
}

void SDL2ControllerEventHandler::concrete_handle(SDL_Event event) const{
  switch (event.type) {
        case SDL_CONTROLLERAXISMOTION :
            this->abstractControllerManager->set_axis(
              this->convertSDLAxistoControllerButton(event.caxis.axis),
              this->normalize_SDL2_axis(event.caxis.value)
            );
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            this->abstractControllerManager->release_button(this->convertSDLtoControllerButton(event.button.button));
            break;
        case SDL_CONTROLLERBUTTONUP:
            this->abstractControllerManager->press_button(this->convertSDLtoControllerButton(event.button.button));
            break;
    }
}


/**
 * NODE: probably slow, might be optimized
 */

ControllerButton SDL2ControllerEventHandler::convertSDLtoControllerButton(SDL_Keycode  sdlButton) const{
  switch (sdlButton) {
        case SDL_CONTROLLER_BUTTON_DPAD_UP : return ControllerButton::CONTROLLER_DPAD_UP;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT : return ControllerButton::CONTROLLER_DPAD_RIGHT;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN : return ControllerButton::CONTROLLER_DPAD_DOWN;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT : return ControllerButton::CONTROLLER_DPAD_LEFT;

        case SDL_CONTROLLER_BUTTON_X : return ControllerButton::CONTROLLER_BUTTON_X;
        case SDL_CONTROLLER_BUTTON_Y : return ControllerButton::CONTROLLER_BUTTON_Y;
        case SDL_CONTROLLER_BUTTON_B : return ControllerButton::CONTROLLER_BUTTON_B;
        case SDL_CONTROLLER_BUTTON_A : return ControllerButton::CONTROLLER_BUTTON_A;

        case SDL_CONTROLLER_BUTTON_LEFTSTICK : return ControllerButton::CONTROLLER_LEFTSTICK;
        case SDL_CONTROLLER_BUTTON_RIGHTSTICK : return ControllerButton::CONTROLLER_RIGHTSTICK;

        case SDL_CONTROLLER_BUTTON_BACK : return ControllerButton::CONTROLLER_BACK;
        case SDL_CONTROLLER_BUTTON_START : return ControllerButton::CONTROLLER_START;

        case SDL_CONTROLLER_BUTTON_TOUCHPAD : return ControllerButton::CONTROLLER_TOUCHPAD;

        default : return ControllerButton::DEFAULT;
    }
}


ControllerAxis SDL2ControllerEventHandler::convertSDLAxistoControllerButton(SDL_Keycode sdlAxis) const{
  switch (sdlAxis) {
        case SDL_CONTROLLER_AXIS_LEFTX : return ControllerAxis::CONTROLLER_LEFT_HORIZONTAL_AXIS;
        case SDL_CONTROLLER_AXIS_LEFTY : return ControllerAxis::CONTROLLER_LEFT_VERICAL_AXIS;
        case SDL_CONTROLLER_AXIS_RIGHTX : return ControllerAxis::CONTROLLER_RIGHT_HORIZONTAL_AXIS;
        case SDL_CONTROLLER_AXIS_RIGHTY : return ControllerAxis::CONTROLLER_RIGHT_VERICAL_AXIS;
        case SDL_CONTROLLER_AXIS_TRIGGERLEFT : return ControllerAxis::CONTROLLER_LEFT_TRIGGER_AXIS;
        case SDL_CONTROLLER_AXIS_TRIGGERRIGHT : return ControllerAxis::CONTROLLER_RIGHT_TRIGGER_AXIS;
        default : return ControllerAxis::DEFAULT;
    }
}
