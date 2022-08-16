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

    Add(EKeyboard::KEY0, { '0', ')' });
    Add(EKeyboard::KEY1, { '1', '!' });
    Add(EKeyboard::KEY2, { '2', '@' });
    Add(EKeyboard::KEY3, { '3', '#' });
    Add(EKeyboard::KEY4, { '4', '$' });
    Add(EKeyboard::KEY5, { '5', '%' });
    Add(EKeyboard::KEY6, { '6', '^' });
    Add(EKeyboard::KEY7, { '7', '&' });
    Add(EKeyboard::KEY8, { '8', '*' });
    Add(EKeyboard::KEY9, { '9', '(' });

    Add(EKeyboard::KP_0, { '0' });
    Add(EKeyboard::KP_1, { '1' });
    Add(EKeyboard::KP_2, { '2' });
    Add(EKeyboard::KP_3, { '3' });
    Add(EKeyboard::KP_4, { '4' });
    Add(EKeyboard::KP_5, { '5' });
    Add(EKeyboard::KP_6, { '6' });
    Add(EKeyboard::KP_7, { '7' });
    Add(EKeyboard::KP_8, { '8' });
    Add(EKeyboard::KP_9, { '9' });

    Add(EKeyboard::KP_PLUS, { '+' });
    Add(EKeyboard::KP_MINUS, { '-' });
    Add(EKeyboard::KP_ASTERISK, { '*' });
    Add(EKeyboard::KP_SLASH, { '/' });
    Add(EKeyboard::KP_DOT, { '.' });
}
