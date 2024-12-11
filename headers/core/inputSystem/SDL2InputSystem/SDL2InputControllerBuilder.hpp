#include "../headers/core/inputSystem/AbstractInputControllerBuilder.hpp"

class SDL2InputControllerBuilder : public AbstractInputControllerBuilder{

    public:
    std::shared_ptr<InputControllerInterface> get_input_controller_interface() override;

};