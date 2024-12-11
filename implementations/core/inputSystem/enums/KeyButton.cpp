#include "../headers/core/inputSystem/Enums/KeyButton.hpp"

std::string KeyButtonHelper::keyButtonToString(KeyButton keyButton){
    switch (keyButton) {
        // Lettere
        case KeyButton::A: return "A";
        case KeyButton::B: return "B";
        case KeyButton::C: return "C";
        case KeyButton::D: return "D";
        case KeyButton::E: return "E";
        case KeyButton::F: return "F";
        case KeyButton::G: return "G";
        case KeyButton::H: return "H";
        case KeyButton::I: return "I";
        case KeyButton::J: return "J";
        case KeyButton::K: return "K";
        case KeyButton::L: return "L";
        case KeyButton::M: return "M";
        case KeyButton::N: return "N";
        case KeyButton::O: return "O";
        case KeyButton::P: return "P";
        case KeyButton::Q: return "Q";
        case KeyButton::R: return "R";
        case KeyButton::S: return "S";
        case KeyButton::T: return "T";
        case KeyButton::U: return "U";
        case KeyButton::V: return "V";
        case KeyButton::W: return "W";
        case KeyButton::X: return "X";
        case KeyButton::Y: return "Y";
        case KeyButton::Z: return "Z";

        // Numeri
        case KeyButton::NUM_0: return "NUM_0";
        case KeyButton::NUM_1: return "NUM_1";
        case KeyButton::NUM_2: return "NUM_2";
        case KeyButton::NUM_3: return "NUM_3";
        case KeyButton::NUM_4: return "NUM_4";
        case KeyButton::NUM_5: return "NUM_5";
        case KeyButton::NUM_6: return "NUM_6";
        case KeyButton::NUM_7: return "NUM_7";
        case KeyButton::NUM_8: return "NUM_8";
        case KeyButton::NUM_9: return "NUM_9";

        // Tasti funzione
        case KeyButton::F1: return "F1";
        case KeyButton::F2: return "F2";
        case KeyButton::F3: return "F3";
        case KeyButton::F4: return "F4";
        case KeyButton::F5: return "F5";
        case KeyButton::F6: return "F6";
        case KeyButton::F7: return "F7";
        case KeyButton::F8: return "F8";
        case KeyButton::F9: return "F9";
        case KeyButton::F10: return "F10";
        case KeyButton::F11: return "F11";
        case KeyButton::F12: return "F12";

        // Simboli principali
        case KeyButton::GRAVE_ACCENT: return "GRAVE_ACCENT";
        case KeyButton::MINUS: return "MINUS";
        case KeyButton::EQUAL: return "EQUAL";
        case KeyButton::LEFT_BRACKET: return "LEFT_BRACKET";
        case KeyButton::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case KeyButton::BACKSLASH: return "BACKSLASH";
        case KeyButton::SEMICOLON: return "SEMICOLON";
        case KeyButton::APOSTROPHE: return "APOSTROPHE";
        case KeyButton::COMMA: return "COMMA";
        case KeyButton::PERIOD: return "PERIOD";
        case KeyButton::SLASH: return "SLASH";

        // Modificatori
        case KeyButton::LEFT_SHIFT: return "LEFT_SHIFT";
        case KeyButton::RIGHT_SHIFT: return "RIGHT_SHIFT";
        case KeyButton::LEFT_CONTROL: return "LEFT_CONTROL";
        case KeyButton::RIGHT_CONTROL: return "RIGHT_CONTROL";
        case KeyButton::LEFT_ALT: return "LEFT_ALT";
        case KeyButton::RIGHT_ALT: return "RIGHT_ALT";
        case KeyButton::LEFT_SUPER: return "LEFT_SUPER";
        case KeyButton::RIGHT_SUPER: return "RIGHT_SUPER";

        // Navigazione e spaziatura
        case KeyButton::SPACE: return "SPACE";
        case KeyButton::ENTER: return "ENTER";
        case KeyButton::BACKSPACE: return "BACKSPACE";
        case KeyButton::TAB: return "TAB";
        case KeyButton::CAPS_LOCK: return "CAPS_LOCK";

        // Tasti di navigazione
        case KeyButton::ESCAPE: return "ESCAPE";
        case KeyButton::INSERT: return "INSERT";
        case KeyButton::DELETE: return "DELETE";
        case KeyButton::HOME: return "HOME";
        case KeyButton::END: return "END";
        case KeyButton::PAGE_UP: return "PAGE_UP";
        case KeyButton::PAGE_DOWN: return "PAGE_DOWN";

        // Frecce
        case KeyButton::ARROW_UP: return "ARROW_UP";
        case KeyButton::ARROW_DOWN: return "ARROW_DOWN";
        case KeyButton::ARROW_LEFT: return "ARROW_LEFT";
        case KeyButton::ARROW_RIGHT: return "ARROW_RIGHT";

        // Default
        case KeyButton::DEFAULT: return "DEFAULT";

        default: return "UNKNOWN";
    }
}

std::vector<KeyButton> KeyButtonHelper::getKeyButtons() {
    return {
        KeyButton::A, KeyButton::B, KeyButton::C, KeyButton::D, KeyButton::E, KeyButton::F, KeyButton::G, KeyButton::H,
        KeyButton::I, KeyButton::J, KeyButton::K, KeyButton::L, KeyButton::M, KeyButton::N, KeyButton::O, KeyButton::P,
        KeyButton::Q, KeyButton::R, KeyButton::S, KeyButton::T, KeyButton::U, KeyButton::V, KeyButton::W, KeyButton::X,
        KeyButton::Y, KeyButton::Z,
        KeyButton::NUM_0, KeyButton::NUM_1, KeyButton::NUM_2, KeyButton::NUM_3, KeyButton::NUM_4, KeyButton::NUM_5,
        KeyButton::NUM_6, KeyButton::NUM_7, KeyButton::NUM_8, KeyButton::NUM_9,
        KeyButton::F1, KeyButton::F2, KeyButton::F3, KeyButton::F4, KeyButton::F5, KeyButton::F6, KeyButton::F7,
        KeyButton::F8, KeyButton::F9, KeyButton::F10, KeyButton::F11, KeyButton::F12,
        KeyButton::GRAVE_ACCENT, KeyButton::MINUS, KeyButton::EQUAL, KeyButton::LEFT_BRACKET, KeyButton::RIGHT_BRACKET,
        KeyButton::BACKSLASH, KeyButton::SEMICOLON, KeyButton::APOSTROPHE, KeyButton::COMMA, KeyButton::PERIOD, KeyButton::SLASH,
        KeyButton::LEFT_SHIFT, KeyButton::RIGHT_SHIFT, KeyButton::LEFT_CONTROL, KeyButton::RIGHT_CONTROL,
        KeyButton::LEFT_ALT, KeyButton::RIGHT_ALT, KeyButton::LEFT_SUPER, KeyButton::RIGHT_SUPER,
        KeyButton::SPACE, KeyButton::ENTER, KeyButton::BACKSPACE, KeyButton::TAB, KeyButton::CAPS_LOCK,
        KeyButton::ESCAPE, KeyButton::INSERT, KeyButton::DELETE, KeyButton::HOME, KeyButton::END, KeyButton::PAGE_UP,
        KeyButton::PAGE_DOWN, KeyButton::ARROW_UP, KeyButton::ARROW_DOWN, KeyButton::ARROW_LEFT, KeyButton::ARROW_RIGHT,
        KeyButton::DEFAULT
    };
}