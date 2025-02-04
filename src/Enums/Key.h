#ifndef KEY_H
#define KEY_H
#include <string>
#include <stdexcept>
#include <unordered_map>

#include <windows.h>

enum class Key {
    A = 0x41, // ASCII 'A'
    B = 0x42, // ASCII 'B'
    C = 0x43, // ASCII 'C'
    D = 0x44, // ASCII 'D'
    E = 0x45, // ASCII 'E'
    F = 0x46, // ASCII 'F'
    G = 0x47, // ASCII 'G'
    H = 0x48, // ASCII 'H'
    I = 0x49, // ASCII 'I'
    J = 0x4A, // ASCII 'J'
    K = 0x4B, // ASCII 'K'
    L = 0x4C, // ASCII 'L'
    M = 0x4D, // ASCII 'M'
    N = 0x4E, // ASCII 'N'
    O = 0x4F, // ASCII 'O'
    P = 0x50, // ASCII 'P'
    Q = 0x51, // ASCII 'Q'
    R = 0x52, // ASCII 'R'
    S = 0x53, // ASCII 'S'
    T = 0x54, // ASCII 'T'
    U = 0x55, // ASCII 'U'
    V = 0x56, // ASCII 'V'
    W = 0x57, // ASCII 'W'
    X = 0x58, // ASCII 'X'
    Y = 0x59, // ASCII 'Y'
    Z = 0x5A, // ASCII 'Z'

    ONE = 0x30, // ASCII '0'
    TWO = 0x31, // ASCII '1'
    THREE = 0x32, // ASCII '2'
    FOUR = 0x33, // ASCII '3'
    FIVE = 0x34, // ASCII '4'
    SIX = 0x35, // ASCII '5'
    SEVEN = 0x36, // ASCII '6'
    EIGHT = 0x37, // ASCII '7'
    NINE = 0x38, // ASCII '8'
    ZERO = 0x39, // ASCII '9'

    ESC = VK_ESCAPE, // Windows API ESC
    TAB = VK_TAB, // Windows API TAB
    SPACE = VK_SPACE, // Windows API SPACE
    ENTER = VK_RETURN, // Windows API ENTER
    BACKSPACE = VK_BACK, // Windows API BACKSPACE
    SHIFT = VK_SHIFT, // Windows API SHIFT
    CTRL = VK_CONTROL, // Windows API CTRL
    ALT = VK_MENU, // Windows API ALT
    CAPSLOCK = VK_CAPITAL, // Windows API CAPSLOCK
    NUMLOCK = VK_NUMLOCK, // Windows API NUMLOCK
    SCROLLLOCK = VK_SCROLL, // Windows API SCROLLLOCK
    PAUSE = VK_PAUSE, // Windows API PAUSE
    INSERT = VK_INSERT, // Windows API INSERT
    DEL = VK_DELETE, // Windows API DELETE
    HOME = VK_HOME, // Windows API HOME
    END = VK_END, // Windows API END
    PAGEUP = VK_PRIOR, // Windows API PAGEUP
    PAGEDOWN = VK_NEXT, // Windows API PAGEDOWN
    LEFT = VK_LEFT, // Windows API LEFT
    RIGHT = VK_RIGHT, // Windows API RIGHT
    UP = VK_UP, // Windows API UP
    DOWN = VK_DOWN, // Windows API DOWN

    WIN = VK_LWIN, // Windows API WINDOWS
    UNDEFINED = -1
};


static const std::unordered_map<std::string, Key> FromStringToKey = {
    {"A", Key::A}, {"B", Key::B}, {"C", Key::C}, {"D", Key::D}, {"E", Key::E}, {"F", Key::F},
    {"G", Key::G}, {"H", Key::H}, {"I", Key::I}, {"J", Key::J}, {"K", Key::K}, {"L", Key::L},
    {"M", Key::M}, {"N", Key::N}, {"O", Key::O}, {"P", Key::P}, {"Q", Key::Q}, {"R", Key::R},
    {"S", Key::S}, {"T", Key::T}, {"U", Key::U}, {"V", Key::V}, {"W", Key::W}, {"X", Key::X},
    {"Y", Key::Y}, {"Z", Key::Z},
    {"0", Key::ZERO}, {"1", Key::ONE}, {"2", Key::TWO}, {"3", Key::THREE}, {"4", Key::FOUR},
    {"5", Key::FIVE}, {"6", Key::SIX}, {"7", Key::SEVEN}, {"8", Key::EIGHT}, {"9", Key::NINE},
    {"Escape", Key::ESC}, {"Tab", Key::TAB}, {"Space", Key::SPACE}, {"Enter", Key::ENTER},
    {"Backspace", Key::BACKSPACE}, {"Shift", Key::SHIFT}, {"Ctrl", Key::CTRL}, {"Alt", Key::ALT},
    {"CapsLock", Key::CAPSLOCK}, {"NumLock", Key::NUMLOCK}, {"ScrollLock", Key::SCROLLLOCK},
    {"Pause", Key::PAUSE}, {"Insert", Key::INSERT}, {"Delete", Key::DEL}, {"Home", Key::HOME},
    {"End", Key::END}, {"PageUp", Key::PAGEUP}, {"PageDown", Key::PAGEDOWN}, {"Left", Key::LEFT},
    {"Right", Key::RIGHT}, {"Up", Key::UP}, {"Down", Key::DOWN}, {"Win", Key::WIN}
};

static const std::unordered_map<Key, std::string> FromKeyToString = {
    {Key::A, "A"}, {Key::B, "B"}, {Key::C, "C"}, {Key::D, "D"}, {Key::E, "E"}, {Key::F, "F"},
    {Key::G, "G"}, {Key::H, "H"}, {Key::I, "I"}, {Key::J, "J"}, {Key::K, "K"}, {Key::L, "L"},
    {Key::M, "M"}, {Key::N, "N"}, {Key::O, "O"}, {Key::P, "P"}, {Key::Q, "Q"}, {Key::R, "R"},
    {Key::S, "S"}, {Key::T, "T"}, {Key::U, "U"}, {Key::V, "V"}, {Key::W, "W"}, {Key::X, "X"},
    {Key::Y, "Y"}, {Key::Z, "Z"},
    {Key::ZERO, "0"}, {Key::ONE, "1"}, {Key::TWO, "2"}, {Key::THREE, "3"}, {Key::FOUR, "4"},
    {Key::FIVE, "5"}, {Key::SIX, "6"}, {Key::SEVEN, "7"}, {Key::EIGHT, "8"}, {Key::NINE, "9"},
    {Key::ESC, "Escape"}, {Key::TAB, "Tab"}, {Key::SPACE, "Space"}, {Key::ENTER, "Enter"},
    {Key::BACKSPACE, "Backspace"}, {Key::SHIFT, "Shift"}, {Key::CTRL, "Ctrl"}, {Key::ALT, "Alt"},
    {Key::CAPSLOCK, "CapsLock"}, {Key::NUMLOCK, "NumLock"}, {Key::SCROLLLOCK, "ScrollLock"},
    {Key::PAUSE, "Pause"}, {Key::INSERT, "Insert"}, {Key::DEL, "Delete"}, {Key::HOME, "Home"},
    {Key::END, "End"}, {Key::PAGEUP, "PageUp"}, {Key::PAGEDOWN, "PageDown"}, {Key::LEFT, "Left"},
    {Key::RIGHT, "Right"}, {Key::UP, "Up"}, {Key::DOWN, "Down"}, {Key::WIN, "Win"}
};


static std::string key_to_string(const Key key) {
    if (const auto it = FromKeyToString.find(key); it != FromKeyToString.end() && it->second != "Undefined") {
        return it->second;
    }
    throw std::invalid_argument("Unsupported key code");
}

static Key string_to_key(const std::string &str) {
    if (const auto it = FromStringToKey.find(str); it != FromStringToKey.end() && it->second != Key::UNDEFINED) {
        return it->second;
    }
    throw std::invalid_argument("Unsupported key string: " + str);
}

static bool operator==(const Key lhs, const std::string &rhs) {
    return key_to_string(lhs) == rhs;
}

static bool operator!=(const Key lhs, const std::string &rhs) {
    return !(lhs == rhs);
}

#endif
