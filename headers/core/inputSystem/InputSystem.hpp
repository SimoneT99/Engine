#include "InputControllerInterface.hpp"
#include "AbstractInputcontrollerBuilder.hpp"

/**
 * @brief: This class is a singletone class that allow the access to the input system in each point of the engine.
 * It's system indipendent, therefore you can chose any system you like by passing the builder 
 * you'd like it to use during the setup step.
 */

/**
 * BAD: what if the interface we provide is not enough? How can the developer use his own interface?
 */

#include <memory>
#include <iostream>

class InputSystem{

    private:
    std::shared_ptr<AbstractInputControllerBuilder> builder;
    std::shared_ptr<InputControllerInterface> input_controller;

    public:
    static std::shared_ptr<InputSystem> input_system;
    
    /**
     * Get istance method from the singletone pattern
     */

    static std::shared_ptr<InputSystem> get_istance();

    /**
     * This sets the builder of the input system to use during setup
     */
    void setBuilder(std::shared_ptr<AbstractInputControllerBuilder> builder);

    /**
     * This runs the builder in order to setup the InputInterface.
     * WARNING: DO NOT CALL THIS BEFORE YOU SET THE BUILDER 
     */
    void startInputSystem();
};