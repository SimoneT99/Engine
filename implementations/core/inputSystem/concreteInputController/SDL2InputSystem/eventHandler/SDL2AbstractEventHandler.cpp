#include "headers/core/inputSystem/SDL2InputSystem/EventHandler/SDL2AbstractEventHandler.hpp"

void SDL2AbstractEventHandler::setNext(std::shared_ptr<SDL2EventHandlerInterface> handler){
    this->next = handler;
}

void SDL2AbstractEventHandler::handle(SDL_Event event) const{
    if(this->can_handle(event)){
        this->concrete_handle(event);
    }else{
        this->next->handle(event);
    }
}