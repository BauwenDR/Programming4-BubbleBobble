#include "ControllerInput.hpp"

#if _WIN32 or _WIN64
#include <Windows.h>
#include <Xinput.h>

void dae::InputManager::Controller::XControllerInput::Update() {
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
#endif
