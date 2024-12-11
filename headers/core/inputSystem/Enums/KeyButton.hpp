#include <string>
#include <vector>

/*
    Engine rapresentation for common buttons
    thanks chatGpt
*/

namespace Enums{

enum class KeyButton {

    // Lettere
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    // Numeri
    NUM_0, NUM_1, NUM_2, NUM_3, NUM_4,
    NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,

    // Tasti funzione
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

    // Simboli principali
    GRAVE_ACCENT,      // `
    MINUS,             // -
    EQUAL,             // =
    LEFT_BRACKET,      // [
    RIGHT_BRACKET,     // ]
    BACKSLASH,         // 
    SEMICOLON,         // ;
    APOSTROPHE,        // '
    COMMA,             // ,
    PERIOD,            // .
    SLASH,             // /

    // Modificatori
    LEFT_SHIFT,
    RIGHT_SHIFT,
    LEFT_CONTROL,
    RIGHT_CONTROL,
    LEFT_ALT,
    RIGHT_ALT,
    LEFT_SUPER,        // Windows/Command key
    RIGHT_SUPER,       // Windows/Command key

    // Navigazione e spaziatura
    SPACE,
    ENTER,
    BACKSPACE,
    TAB,
    CAPS_LOCK,

    // Tasti di navigazione
    ESCAPE,
    INSERT,
    DELETE,
    HOME,
    END,
    PAGE_UP,
    PAGE_DOWN,

    // Frecce
    ARROW_UP,
    ARROW_DOWN,
    ARROW_LEFT,
    ARROW_RIGHT,

    DEFAULT,
};

class KeyButtonHelper{

    public:
        static std::string keyButtonToString(KeyButton keyButton);
        static std::vector<KeyButton> getKeyButtons();

};

}