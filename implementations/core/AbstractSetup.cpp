#include "../headers/core/AbstractSetup.hpp"

void AbstractSetup::setup(){

    /**
     * Input system
     */
    this->input_system_thread = std::thread(&AbstractSetup::setup_input_system, this);


    

    /**
     * Waiting for thread to finish.
     */
    this->input_system_thread.join();
};