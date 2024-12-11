/**
 * Abstract setup class that orchestrate the engine setup
 * 
 */
#include "../headers/core/inputSystem/AbstractInputControllerBuilder.hpp"

#include <memory>
#include <thread>

class AbstractSetup{

    private:
        std::thread input_system_thread;
        void setup_input_system();

    protected:
        /**
         * Template methods
         */
        virtual std::shared_ptr<AbstractInputControllerBuilder> get_input_controller_builder() = 0;

    public:

        /**
         * Call to setup the engine, the call is blocking, therefore will not continue until all system
         * have been set up.
         */
        void setup();

};