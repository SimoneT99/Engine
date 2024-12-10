#include "../SDL2AbstractEventHandler.hpp"
#include "../headers/core/inputSystem/SDL2InputSystem/eventHandler/concreteHandler/SDL2KeyboardEventHandler.hpp"

bool SDL2KeyboardEventHandler::can_handle(SDL_Event event) const{
    return event.type == SDL_KEYDOWN || event.type == SDL_KEYUP;
};

void SDL2KeyboardEventHandler::concrete_handle(SDL_Event event) const{

    switch (event.type) {
        case SDL_KEYDOWN :
            this->abstractKeyboardManager->press_button(this->convertSDLtoKeyButton(event.button.button));
            break;
        case SDL_KEYUP:
            this->abstractKeyboardManager->release_button(this->convertSDLtoKeyButton(event.button.button));
            break;
    }

};

/**
 * NODE: probably slow, might be optimized
 */

KeyButton SDL2KeyboardEventHandler::convertSDLtoKeyButton(SDL_Keycode  sdlButton) const{
    switch (sdlButton) {
        // Lettere
        case SDLK_a: return KeyButton::A;
        case SDLK_b: return KeyButton::B;
        case SDLK_c: return KeyButton::C;
        case SDLK_d: return KeyButton::D;
        case SDLK_e: return KeyButton::E;
        case SDLK_f: return KeyButton::F;
        case SDLK_g: return KeyButton::G;
        case SDLK_h: return KeyButton::H;
        case SDLK_i: return KeyButton::I;
        case SDLK_j: return KeyButton::J;
        case SDLK_k: return KeyButton::K;
        case SDLK_l: return KeyButton::L;
        case SDLK_m: return KeyButton::M;
        case SDLK_n: return KeyButton::N;
        case SDLK_o: return KeyButton::O;
        case SDLK_p: return KeyButton::P;
        case SDLK_q: return KeyButton::Q;
        case SDLK_r: return KeyButton::R;
        case SDLK_s: return KeyButton::S;
        case SDLK_t: return KeyButton::T;
        case SDLK_u: return KeyButton::U;
        case SDLK_v: return KeyButton::V;
        case SDLK_w: return KeyButton::W;
        case SDLK_x: return KeyButton::X;
        case SDLK_y: return KeyButton::Y;
        case SDLK_z: return KeyButton::Z;

        // Numeri
        case SDLK_0: return KeyButton::NUM_0;
        case SDLK_1: return KeyButton::NUM_1;
        case SDLK_2: return KeyButton::NUM_2;
        case SDLK_3: return KeyButton::NUM_3;
        case SDLK_4: return KeyButton::NUM_4;
        case SDLK_5: return KeyButton::NUM_5;
        case SDLK_6: return KeyButton::NUM_6;
        case SDLK_7: return KeyButton::NUM_7;
        case SDLK_8: return KeyButton::NUM_8;
        case SDLK_9: return KeyButton::NUM_9;

        // Tasti funzione
        case SDLK_F1: return KeyButton::F1;
        case SDLK_F2: return KeyButton::F2;
        case SDLK_F3: return KeyButton::F3;
        case SDLK_F4: return KeyButton::F4;
        case SDLK_F5: return KeyButton::F5;
        case SDLK_F6: return KeyButton::F6;
        case SDLK_F7: return KeyButton::F7;
        case SDLK_F8: return KeyButton::F8;
        case SDLK_F9: return KeyButton::F9;
        case SDLK_F10: return KeyButton::F10;
        case SDLK_F11: return KeyButton::F11;
        case SDLK_F12: return KeyButton::F12;

        // Simboli principali
        case SDLK_BACKQUOTE: return KeyButton::GRAVE_ACCENT;
        case SDLK_MINUS: return KeyButton::MINUS;
        case SDLK_EQUALS: return KeyButton::EQUAL;
        case SDLK_LEFTBRACKET: return KeyButton::LEFT_BRACKET;
        case SDLK_RIGHTBRACKET: return KeyButton::RIGHT_BRACKET;
        case SDLK_BACKSLASH: return KeyButton::BACKSLASH;
        case SDLK_SEMICOLON: return KeyButton::SEMICOLON;
        case SDLK_COMMA: return KeyButton::COMMA;
        case SDLK_PERIOD: return KeyButton::PERIOD;
        case SDLK_SLASH: return KeyButton::SLASH;

        // Modificatori
        case SDLK_LSHIFT: return KeyButton::LEFT_SHIFT;
        case SDLK_RSHIFT: return KeyButton::RIGHT_SHIFT;
        case SDLK_LCTRL: return KeyButton::LEFT_CONTROL;
        case SDLK_RCTRL: return KeyButton::RIGHT_CONTROL;
        case SDLK_LALT: return KeyButton::LEFT_ALT;
        case SDLK_RALT: return KeyButton::RIGHT_ALT;
        case SDLK_LGUI: return KeyButton::LEFT_SUPER;
        case SDLK_RGUI: return KeyButton::RIGHT_SUPER;

        // Altri tasti
        case SDLK_SPACE: return KeyButton::SPACE;
        case SDLK_RETURN: return KeyButton::ENTER;
        case SDLK_BACKSPACE: return KeyButton::BACKSPACE;
        case SDLK_TAB: return KeyButton::TAB;
        case SDLK_CAPSLOCK: return KeyButton::CAPS_LOCK;
        case SDLK_ESCAPE: return KeyButton::ESCAPE;
        case SDLK_INSERT: return KeyButton::INSERT;
        case SDLK_DELETE: return KeyButton::DELETE;
        case SDLK_HOME: return KeyButton::HOME;
        case SDLK_END: return KeyButton::END;
        case SDLK_PAGEUP: return KeyButton::PAGE_UP;
        case SDLK_PAGEDOWN: return KeyButton::PAGE_DOWN;
        case SDLK_UP: return KeyButton::ARROW_UP;
        case SDLK_DOWN: return KeyButton::ARROW_DOWN;
        case SDLK_LEFT: return KeyButton::ARROW_LEFT;
        case SDLK_RIGHT: return KeyButton::ARROW_RIGHT;

        default: return KeyButton::END; // Se il tasto non è riconosciuto
    }
};
