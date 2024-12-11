#include "InputControllerInterface.hpp"

/**
 * This builder allow to detach the building logic of the chosen input system from
 *      the logic of the system itself.
 * If you need to build your own system you need to develop also a builder, then you istance
 * it as you want and pass it to the InputSystem "setBuilder" method, this way when the system
 * it's started it will be used the one you chosed, configured the way you wanted it to be!
 */

#include <memory>

class AbstractInputControllerBuilder{
    public:
    virtual std::shared_ptr<InputControllerInterface> get_input_controller_interface() = 0;
};