#include "../headers/core/inputSystem/Enums/ButtonState.hpp"

/**
 * I do not like this class...
 */

class AbstractButtonManager{

    protected:
        inline bool check_button_pressed_down(ButtonState state) const;
        inline bool check_button_pressed(ButtonState state) const;
        inline bool check_button_released(ButtonState state) const;
        virtual inline void tick() = 0;
};