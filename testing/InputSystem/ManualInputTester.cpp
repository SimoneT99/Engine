#include "../headers/core/inputSystem/Enums/Enums.hpp"
#include "../headers/core/inputSystem/InputSystem.hpp"
#include "MessageToTerminalCommand.hpp"

/**
 * Quick tool that can be used to check button presses
 */
#include <memory>

int main(int argc, char* argv[]){   
    std::shared_ptr<InputSystem> inputSystem = InputSystem::get_istance();
    inputSystem->setBuilder(get_builder());
    inputSystem->startInputSystem();

    std::shared_ptr<InputControllerInterface> inputControllerInterface = inputSystem->getInputController();

    /**********   Active Binding   ****************/


    /**
     * Keyboard Setup
     */
    auto keyButtons = Enums::KeyButtonHelper::getKeyButtons();

    for(auto it = keyButtons.begin(); it != keyButtons.end(); ++it){
        /**
         * Pressed down
         */
        
        inputControllerInterface->bind_key_event(
            *it, 
            Enums::ButtonEvent::PRESSED, 
            std::make_unique<MessageToTerminalCommand>("KeyButton " + Enums::KeyButtonHelper::keyButtonToString(*it) + " Pressed")
            );

        /**
         * Pressed
         */

        inputControllerInterface->bind_key_event(
            *it, 
            Enums::ButtonEvent::PRESSED_DOWN, 
            std::make_unique<MessageToTerminalCommand>("KeyButton " + Enums::KeyButtonHelper::keyButtonToString(*it) + " Pressed down")
            );

        /**
         * Released
         */
        
        inputControllerInterface->bind_key_event(
            *it, 
            Enums::ButtonEvent::RELEASED, 
            std::make_unique<MessageToTerminalCommand>("KeyButton " + Enums::KeyButtonHelper::keyButtonToString(*it) + " Released")
            );

    }

    /**
     * Mouse Setup
     */
    auto mouseButtons = Enums::MouseButtonHelper::getMouseButtons();

    for(auto it = mouseButtons.begin(); it != mouseButtons.end(); ++it){
        /**
         * Pressed down
         */
        
        inputControllerInterface->bind_mouse_event(
            *it, 
            Enums::ButtonEvent::PRESSED, 
            std::make_unique<MessageToTerminalCommand>("MouseButton " + Enums::MouseButtonHelper::mouseButtonToString(*it) + " Pressed")
            );

        /**
         * Pressed
         */

        inputControllerInterface->bind_mouse_event(
            *it, 
            Enums::ButtonEvent::PRESSED_DOWN, 
            std::make_unique<MessageToTerminalCommand>("MouseButton " + Enums::MouseButtonHelper::mouseButtonToString(*it) + " Pressed down")
            );

        /**
         * Released
         */
        
        inputControllerInterface->bind_mouse_event(
            *it, 
            Enums::ButtonEvent::RELEASED, 
            std::make_unique<MessageToTerminalCommand>("MouseButton " + Enums::MouseButtonHelper::mouseButtonToString(*it) + " Released")
            );

    }

    /**
     * Controller Setup
     * TODO:Setup the controller support testing
     */


    /**********   Polling testing   ****************/

}

/**********************************************************************************************/

/**
 * Here you can select the input system builder you want to use
 */

std::shared_ptr<AbstractInputControllerBuilder> get_builder(){

}