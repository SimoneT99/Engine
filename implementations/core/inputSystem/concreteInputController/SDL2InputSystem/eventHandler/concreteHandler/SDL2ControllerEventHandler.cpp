#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractControllerManager.hpp"

class SDL2ControllerEventHandler : public SDL2AbstractEventHandler{

    private:

        int controller_id;

        std::shared_ptr<AbstractControllerManager> abstractControllerManager;

    public:

        SDL2ControllerEventHandler(std::shared_ptr<AbstractControllerManager> abstractControllerManager, int controller_id) 
        : abstractControllerManager(abstractControllerManager),
          controller_id(controller_id)
        {}

        bool can_handle(SDL_Event event) const override;
        void concrete_handle(SDL_Event event) const override;

};