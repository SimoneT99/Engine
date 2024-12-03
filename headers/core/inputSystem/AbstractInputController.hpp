#include "KeyButton.hpp"
#include "AbstractInputCommand.hpp"

class AbstractInputController{

    public:

        //Polling methods
        bool key_pressed(KeyButton button);
        bool key_pressed_down(KeyButton button);
        bool key_released(KeyButton button);

        //Key polling management
        bool add_key(KeyButton button);
        bool remove_key(KeyButton button);

        //Key Event binding
        bool key_pressed_bind_event(KeyButton button, AbstractInputCommand action);
        bool key_pressed_unbind_event(KeyButton button);

        bool key_pressed_down_bind_event(KeyButton button, AbstractInputCommand action);
        bool key_pressed_down_unbind_event(KeyButton button);

        bool key_released_bind_event(KeyButton button, AbstractInputCommand action);
        bool key_released_unbind_event(KeyButton button);

};