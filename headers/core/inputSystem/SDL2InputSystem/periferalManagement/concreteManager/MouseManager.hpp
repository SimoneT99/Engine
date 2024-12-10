#include "../headers\core\inputSystem\SDL2InputSystem\periferalManagement\AbstractMouseManager.hpp"
#include <map>

class MouseManager : public AbstractMouseManager{

    private:
        std::map<MouseButton, ButtonState> mouse_buttons;
        std::map<std::pair<MouseButton, ButtonState>, AbstractInputCommand> mouse_buttons_events;
        
        inline ButtonState get_mouse_button_state(MouseButton button) const;

        float mouse_x;
        float mouse_y;

        float mouse_delta_x;
        float mouse_delta_y;

        float wheel_delta_x;
        float wheel_delta_y;


    public:
        void get_mouse_position(float& x, float& y) const override;
        void get_mouse_delta(float& dx, float& dy) const override;
        void get_mouse_wheel_delta(float& dx, float& dy) const override;

        bool mouse_button_pressed_down(MouseButton button) const override;
        bool mouse_button_pressed(MouseButton button) const override;
        bool mouse_button_released(MouseButton button) const override;

        bool bind_mouse_event(MouseButton button, ButtonState event, AbstractInputCommand action) override;
        bool unbind_mouse_event(MouseButton button, ButtonState event) override;

        void set_mouse_position(float x, float y) override;
        void update_mouse_wheel_delta(float dx, float dy) override;
        virtual void press_button(MouseButton button) = 0;
        virtual void release_button(MouseButton button) = 0;

};