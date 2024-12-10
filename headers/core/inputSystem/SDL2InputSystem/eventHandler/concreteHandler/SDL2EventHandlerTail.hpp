#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractControllerManager.hpp"
#include "../headers/core/inputSystem/enums/ControllerButton.hpp"
#include "../headers/core/inputSystem/enums/ControllerAxis.hpp"
#include <iostream>

class SDL2EventHandlerTail : public SDL2AbstractEventHandler{

    protected:
        bool can_handle(SDL_Event event) const override;
        void concrete_handle(SDL_Event event) const override;
};