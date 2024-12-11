#include "../headers/core/inputSystem/AbstractInputControllerBuilder.hpp"

class SDL2InputControllerbuilder : public AbstractInputControllerBuilder{

    public:
    std::shared_ptr<InputControllerInterface> get_input_controller_interface() override;
    
};