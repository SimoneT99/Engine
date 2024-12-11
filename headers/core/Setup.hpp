#include "AbstractSetup.hpp"

class Setup : public AbstractSetup{

    protected:
        std::shared_ptr<AbstractInputControllerBuilder> get_input_controller_builder() override;
};