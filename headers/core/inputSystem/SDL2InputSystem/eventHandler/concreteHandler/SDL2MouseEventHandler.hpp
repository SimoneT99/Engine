#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractMouseManager.hpp"


class SDL2MouseEventHandler : public SDL2AbstractEventHandler{

    private:
        std::shared_ptr<AbstractMouseManager> abstractMouseManager;

    public:

        SDL2MouseEventHandler(std::shared_ptr<AbstractMouseManager> abstractMouseManager) 
        : abstractMouseManager(abstractMouseManager) 
        {}

        bool can_handle(SDL_Event event) const override;
        void concrete_handle(SDL_Event event) const override;
};