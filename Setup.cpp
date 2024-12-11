#include "headers/core/Setup.hpp"
#include "headers/core/inputSystem/SDL2InputSystem/SDL2InputControllerBuilder.hpp"

/**
 * Input system
 */

std::shared_ptr<AbstractInputControllerBuilder> Setup::get_input_controller_builder(){
    /**
     * Here you can setup the builder as you want
     */
    return std::make_shared<SDL2InputControllerBuilder>();
}
