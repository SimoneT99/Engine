#include "../headers/core/inputSystem/SDL2InputSystem/eventHandler/concreteHandler/SDL2EventHandlerTail.hpp"

bool SDL2EventHandlerTail::can_handle(SDL_Event event) const{
    return true;
}

void SDL2EventHandlerTail::concrete_handle(SDL_Event event) const{
    std::cerr << "Untreated SDL2Event fired " << static_cast<int>(event.type);
}
