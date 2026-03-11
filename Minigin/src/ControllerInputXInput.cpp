#include "ControllerInput.hpp"

#if _WIN32 or _WIN64
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "Xinput.lib")

void dae::InputManager::Controller::XControllerInput::Update() {
    XINPUT_STATE state{};
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    const uint16_t inputMask = static_cast<uint16_t>(XInputGetState(0, &state));

    const auto buttonChanges = inputMask ^ m_heldButtons;
    m_pressedButtons = buttonChanges & m_heldButtons;
    m_releasedButtons = buttonChanges & ~m_heldButtons;

    m_heldButtons = inputMask;
}
#endif
