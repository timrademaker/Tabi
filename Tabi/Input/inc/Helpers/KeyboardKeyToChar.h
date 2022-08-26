#pragma once

#include "Enums/EKeyboard.h"

#include <SequentialConversionTable.h>

namespace tabi
{
    struct KeyboardChar
    {
        /// Character without modifier keys
        char m_Char = 0;
        /// Character with shift as modifier
        char m_Shift = 0;
    };

    class KeyboardCharConversionTable : public SequentialConversionTable<EKeyboard, KeyboardChar, EKeyboard::A, EKeyboard::Pause>
    {
    public:
        KeyboardCharConversionTable();
    };

    static const KeyboardCharConversionTable KeyboardToCharTable;
}
