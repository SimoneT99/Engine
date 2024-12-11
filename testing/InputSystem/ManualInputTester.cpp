#include "../headers/core/inputSystem/Enums/Enums.hpp"
#include "../headers/core/inputSystem/InputSystem.hpp"
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

    /**
     * Mouse Setup
     */


    /**
     * Controller Setup
     */



    /**********   Polling testing   ****************/

}

/**********************************************************************************************/

/**
 * Here you can select the input system builder you want to use
 */

std::shared_ptr<AbstractInputControllerBuilder> get_builder(){

}