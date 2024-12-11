#include "../headers/core/inputSystem/Enums/ButtonState.hpp"

std::string ButtonStateHelper::buttonStateToString(ButtonState buttonState){
    switch(buttonState){
        case ButtonState::PRESSED_DOWN: return "PRESSED_DOWN";
        case ButtonState::PRESSED: return "PRESSED";
        case ButtonState::RELEASED: return "RELEASED";
        case ButtonState::UNPRESSED: return "UNPRESSED";
    }
}


std::vector<ButtonState> ButtonStateHelper::getButtonState(){

    std::vector<ButtonState> buttons = { 
        ButtonState::PRESSED_DOWN,
        ButtonState::PRESSED,
        ButtonState::RELEASED,
        ButtonState::UNPRESSED
    };

    return buttons;

};