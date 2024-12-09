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
        /**
         * TODO: mouse motion
         */
        break;
    case SDL_MOUSEBUTTONDOWN:
        /**
         * TODO: mouse button down
         */
        break;
    case SDL_MOUSEBUTTONUP:
        /**
         * TODO: mouse button up
         */
        break;
    case SDL_MOUSEWHEEL:
        /**
         * TODO: F**********************************K!
         */
        break;
    }
}
