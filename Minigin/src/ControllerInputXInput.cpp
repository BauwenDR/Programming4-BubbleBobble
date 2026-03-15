#include "ControllerInput.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

namespace dae::Input::Controller
{
    void ControllerInput::Update() {
        XINPUT_STATE state{};
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        const auto xInputState{ XInputGetState(0, &state) };

        if (xInputState != ERROR_SUCCESS) return;

        const uint16_t inputMask = state.Gamepad.wButtons;

        const uint16_t buttonChanges = inputMask ^ m_heldButtons;
        m_pressedButtons = buttonChanges & m_heldButtons;
        m_releasedButtons = buttonChanges & ~m_heldButtons;

        m_heldButtons = inputMask;
    }

    ControllerInput::ControllerInput() {}

    ControllerInput::~ControllerInput() {}
}
