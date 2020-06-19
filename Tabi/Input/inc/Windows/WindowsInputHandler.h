#pragma once

#include "IInputHandler.h"

#include <TabiContainers.h>

namespace tabi
{
    enum class EMouse;
    enum class EKeyboard;
    enum class EController;
    

    class InputHandler : public IInputHandler
    {
    public:
        // Determine device type internally
        virtual bool IsButtonDown(unsigned int a_Button) override;

        virtual float GetAxisValue(unsigned int a_Axis) override;


    private:
        static unsigned int ConvertButtonToGainput(EMouse a_Button);
        static unsigned int ConvertButtonToGainput(EKeyboard a_Button);
        static unsigned int ConvertButtonToGainput(EController a_Button);

        static tabi::unordered_map<EMouse, unsigned int> ms_MouseTable;
        static tabi::unordered_map<EKeyboard, unsigned int> ms_KeyboardTable;
        static tabi::unordered_map<EController, unsigned int> ms_ControllerTable;
    };
}