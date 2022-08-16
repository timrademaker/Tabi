#include "Helpers/KeyboardKeyToChar.h"

static const tabi::KeyboardCharConversionTable KeyboardToCharTable;

tabi::KeyboardCharConversionTable::KeyboardCharConversionTable()
    : SequentialConversionTable({0, 0})
{
    Add(EKeyboard::A, { 'a', 'A' });
    Add(EKeyboard::B, { 'b', 'B' });
    Add(EKeyboard::C, { 'c', 'C' });
    Add(EKeyboard::D, { 'd', 'D' });
    Add(EKeyboard::E, { 'e', 'E' });
    Add(EKeyboard::F, { 'f', 'F' });
    Add(EKeyboard::G, { 'g', 'G' });
    Add(EKeyboard::H, { 'h', 'H' });
    Add(EKeyboard::I, { 'i', 'I' });
    Add(EKeyboard::J, { 'j', 'J' });
    Add(EKeyboard::K, { 'k', 'K' });
    Add(EKeyboard::L, { 'l', 'L' });
    Add(EKeyboard::M, { 'm', 'M' });
    Add(EKeyboard::N, { 'n', 'N' });
    Add(EKeyboard::O, { 'o', 'O' });
    Add(EKeyboard::P, { 'p', 'P' });
    Add(EKeyboard::Q, { 'q', 'Q' });
    Add(EKeyboard::R, { 'r', 'R' });
    Add(EKeyboard::S, { 's', 'S' });
    Add(EKeyboard::T, { 't', 'T' });
    Add(EKeyboard::U, { 'u', 'U' });
    Add(EKeyboard::V, { 'v', 'V' });
    Add(EKeyboard::W, { 'w', 'W' });
    Add(EKeyboard::X, { 'x', 'X' });
    Add(EKeyboard::Y, { 'y', 'Y' });
    Add(EKeyboard::Z, { 'z', 'Z' });

    Add(EKeyboard::Minus, { '-', '_' });
    Add(EKeyboard::Equals, { '=', '+' });
    Add(EKeyboard::BracketLeft, { '[', '{' });
    Add(EKeyboard::BracketRight, { ']', '}' });
    Add(EKeyboard::Semicolon, { ';', ':' });
    Add(EKeyboard::Apostrophe, { '\'', '"' });
    Add(EKeyboard::Comma, { ',', '<' });
    Add(EKeyboard::Period, { '.', '>' });
    Add(EKeyboard::Slash, { '/', '?' });
    Add(EKeyboard::Backslash, { '\\', '|' });
    Add(EKeyboard::AccentGrave, { '`', '~' });

    Add(EKeyboard::Space, { ' ' });

    Add(EKeyboard::Key0, { '0', ')' });
    Add(EKeyboard::Key1, { '1', '!' });
    Add(EKeyboard::Key2, { '2', '@' });
    Add(EKeyboard::Key3, { '3', '#' });
    Add(EKeyboard::Key4, { '4', '$' });
    Add(EKeyboard::Key5, { '5', '%' });
    Add(EKeyboard::Key6, { '6', '^' });
    Add(EKeyboard::Key7, { '7', '&' });
    Add(EKeyboard::Key8, { '8', '*' });
    Add(EKeyboard::Key9, { '9', '(' });

    Add(EKeyboard::Keypad0, { '0' });
    Add(EKeyboard::Keypad1, { '1' });
    Add(EKeyboard::Keypad2, { '2' });
    Add(EKeyboard::Keypad3, { '3' });
    Add(EKeyboard::Keypad4, { '4' });
    Add(EKeyboard::Keypad5, { '5' });
    Add(EKeyboard::Keypad6, { '6' });
    Add(EKeyboard::Keypad7, { '7' });
    Add(EKeyboard::Keypad8, { '8' });
    Add(EKeyboard::Keypad9, { '9' });

    Add(EKeyboard::KeypadPlus, { '+' });
    Add(EKeyboard::KeypadMinus, { '-' });
    Add(EKeyboard::KeypadAsterisk, { '*' });
    Add(EKeyboard::KeypadSlash, { '/' });
    Add(EKeyboard::KeypadPeriod, { '.' });
}
