#include "MessageToTerminalCommand.hpp"

void MessageToTerminalCommand::execute_command(){

    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout<< "[" << std::ctime(&now_c) <<"] " << this->message << std::endl;

};