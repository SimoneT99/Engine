#include "../headers/core/inputSystem/Enums/KeyButton.hpp"
#include "../headers/core/inputSystem/Enums/ButtonState.hpp"
#include "../headers/core/inputSystem/AbstractInputCommand.hpp"
#include "AbstractButtonManager.hpp"
#include <map>

class AbstractKeyboardManager : public AbstractButtonManager{

    public:
        virtual bool key_pressed_down(KeyButton button) const = 0;
        virtual bool key_pressed(KeyButton button) const = 0;
        virtual bool key_released(KeyButton button) const = 0;

        virtual bool bind_key_event(KeyButton button, ButtonState event, AbstractInputCommand action) = 0;
        virtual bool unbind_key_event(KeyButton button, ButtonState event) = 0;

        virtual void press_button(KeyButton button);
        virtual void release_button(KeyButton button);
};