#include "../headers/core/inputSystem/concreteInputController/InputController.hpp"

InputController::InputController(
    float polling_rate,
    int ticks_to_wait
) : 
    polling_rate(polling_rate),
    ticks_to_wait(ticks_to_wait),
    running(true)
{
    this->input_thread = std::thread(&InputController::inputLoop, this);
}

InputController::~InputController(){
    this->running = false;
    this->input_thread.join();
}

void InputController::inputLoop(){

    while(running){
        //TODO: here we need to check the inputs
    }
}