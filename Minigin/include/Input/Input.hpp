#ifndef MINIGIN_INPUT_HPP
#define MINIGIN_INPUT_HPP

#include <cstdint>

namespace dae::Input {
    // The kind of key command that will trigger the command to
    // This type is also used to bridge between Controller and Keyboard input
    enum class CommandTrigger : uint8_t
    {
        KeyDown,
        KeyUp,
        KeyHeld
    };

    // Controller key abstracts away Xinput and SDL bindings (bitmask is the same as XInput to keep that code sane)
    enum class ControllerKey : uint16_t
    {
        DpadUp = 0x0001,
        DpadDown = 0x0002,
        DpadLeft = 0x0004,
        DpadRight = 0x0008,
        Start = 0x0010,
        Select = 0x0020,
        LeftStick = 0x0040,
        RightStick = 0x0080,
        L1 = 0x0100,
        R1 = 0x0200,
        L2 = 0x0400,
        R2 = 0x0800,
        A = 0x1000,
        B = 0x2000,
        X = 0x4000,
        Y = 0x8000,
    };
}

#endif //MINIGIN_INPUT_HPP