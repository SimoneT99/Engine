#include "../headers/core/inputSystem/AbstractInputCommand.hpp"
#include <string>
#include <iostream>
#include <chrono>

/**
 * Simple input command that prints informations when the action is called
 */

class MessageToTerminalCommand : public AbstractInputCommand{
    
    std::string message;

    public:
        MessageToTerminalCommand(std::string message) : message(message) {}
        void execute_command();
};