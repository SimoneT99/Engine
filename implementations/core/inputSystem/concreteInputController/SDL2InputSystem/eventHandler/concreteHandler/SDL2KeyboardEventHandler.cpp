#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractKeyboardManager.hpp"

class SDL2KeyboardEventHandler : public SDL2AbstractEventHandler{

    private:
        std::shared_ptr<AbstractKeyboardManager> abstractKeyboardManager;

    public:

        SDL2KeyboardEventHandler(std::shared_ptr<AbstractKeyboardManager> abstractKeyboardManager) 
        : abstractKeyboardManager(abstractKeyboardManager) 
        {}

        bool can_handle(SDL_Event event) const override;
        void concrete_handle(SDL_Event event) const override;

};