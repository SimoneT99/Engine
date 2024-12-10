#include "../headers\core\inputSystem\SDL2InputSystem\eventHandler\concreteHandler\SDL2MouseEventHandler.hpp"

bool SDL2MouseEventHandler::can_handle(SDL_Event event) const
{
    return event.type == SDL_MOUSEMOTION ||
           event.type == SDL_MOUSEBUTTONDOWN ||
           event.type == SDL_MOUSEBUTTONUP ||
           event.type == SDL_MOUSEWHEEL;
}

void SDL2MouseEventHandler::concrete_handle(SDL_Event event) const
{
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        this->abstractMouseManager->set_mouse_position(event.motion.x, event.motion.y);
        break;
    case SDL_MOUSEBUTTONDOWN:
        this->abstractMouseManager->press_button(this->convertSDLtoMouseButton(event.button.button));
        break;
    case SDL_MOUSEBUTTONUP:
        this->abstractMouseManager->press_button(this->convertSDLtoMouseButton(event.button.button));
        break;
    case SDL_MOUSEWHEEL:
        /**
         * NOTE: Might cause issues later
         */
        this->abstractMouseManager->update_mouse_wheel_delta(event.wheel.x, event.wheel.y);
        break;
    }
}

/**
 * BAD: SDL seems to not support over 6 buttons
 * BAD: Might be slow...
 */

MouseButton SDL2MouseEventHandler::convertSDLtoMouseButton(Uint8 sdlButton) const{
    switch (sdlButton) {
        case SDL_BUTTON_LEFT:   return MouseButton::MOUSE_LEFT;
        case SDL_BUTTON_MIDDLE: return MouseButton::MOUSE_MIDDLE;
        case SDL_BUTTON_RIGHT:  return MouseButton::MOUSE_RIGHT;
        case SDL_BUTTON_X1:     return MouseButton::MOUSE_4;
        case SDL_BUTTON_X2:     return MouseButton::MOUSE_5;
        default:                return MouseButton::MOUSE_6;
    }
}