#include "SDL2EventHandlerInterface.hpp"

class SDL2AbstractEventHandler : public SDL2EventHandlerInterface{

    private:
        std::shared_ptr<SDL2EventHandlerInterface> next;

    protected:
        virtual bool can_handle(SDL_Event event) const = 0;
        virtual void concrete_handle(SDL_Event event) const = 0;

    public:
        void setNext(std::shared_ptr<SDL2EventHandlerInterface> handler) override;
        void handle(SDL_Event event) const override;
};