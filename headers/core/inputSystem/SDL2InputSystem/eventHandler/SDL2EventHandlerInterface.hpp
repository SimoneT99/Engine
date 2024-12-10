#include "../include/SDL2/SDL.h"
#include <memory>

/**
 * Event handler interface to manage the events polled during the update loop
 */

class SDL2EventHandlerInterface{

    public:
        virtual void setNext(std::shared_ptr<SDL2EventHandlerInterface> handler);
        
        /**
         * NOTE: Why we pass it by value? it will not be modified... 
         */
        virtual void handle(SDL_Event event) const;
};