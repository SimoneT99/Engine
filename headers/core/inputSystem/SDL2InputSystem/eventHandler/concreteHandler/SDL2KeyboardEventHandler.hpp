#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/periferalManagement/AbstractKeyboardManager.hpp"
#include "../headers/core/inputSystem/Enums/KeyButton.hpp"

class SDL2KeyboardEventHandler : public SDL2AbstractEventHandler{

    private:
        std::shared_ptr<AbstractKeyboardManager> abstractKeyboardManager;
        KeyButton convertSDLtoKeyButton(SDL_Keycode  sdlButton) const;

    protected:
        bool can_handle(SDL_Event event) const override;
        void concrete_handle(SDL_Event event) const override;

    public:
        SDL2KeyboardEventHandler(std::shared_ptr<AbstractKeyboardManager> abstractKeyboardManager) 
        : abstractKeyboardManager(abstractKeyboardManager) 
        {}



};