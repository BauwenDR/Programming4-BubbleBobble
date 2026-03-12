#include <unordered_map>

#include "ControllerInputImpl.hpp"
#include "InputManager.hpp"

namespace dae::InputManager::Controller
{
    const std::pmr::unordered_map<SDL_GamepadButton, ControllerKey> m_buttonMap {
        {SDL_GAMEPAD_BUTTON_DPAD_UP, ControllerKey::DpadUp},
        {SDL_GAMEPAD_BUTTON_DPAD_DOWN, ControllerKey::DpadDown},
        {SDL_GAMEPAD_BUTTON_DPAD_LEFT, ControllerKey::DpadLeft},
        {SDL_GAMEPAD_BUTTON_DPAD_RIGHT, ControllerKey::DpadRight},
        {SDL_GAMEPAD_BUTTON_SOUTH, ControllerKey::A},
        {SDL_GAMEPAD_BUTTON_EAST, ControllerKey::B},
        {SDL_GAMEPAD_BUTTON_WEST, ControllerKey::X},
        {SDL_GAMEPAD_BUTTON_NORTH, ControllerKey::Y},
        {SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, ControllerKey::L1},
        {SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, ControllerKey::R1},
        {SDL_GAMEPAD_BUTTON_LEFT_STICK, ControllerKey::LeftStick},
        {SDL_GAMEPAD_BUTTON_RIGHT_STICK, ControllerKey::RightStick},
        {SDL_GAMEPAD_BUTTON_BACK , ControllerKey::Select},
        {SDL_GAMEPAD_BUTTON_START, ControllerKey::Start}
    };

    void ControllerInputImpl::Update()
    {
        if (m_pGamepad == nullptr) return;

        uint16_t inputMask{};

        for (const auto&[sdlButton, miniginButton] : m_buttonMap) {
            if (SDL_GetGamepadButton(m_pGamepad, sdlButton)) {
                inputMask |= static_cast<int16_t>(miniginButton);
            }
        }

        const auto buttonChanges = inputMask ^ m_heldButtons;
        m_pressedButtons = buttonChanges & m_heldButtons;
        m_releasedButtons = buttonChanges & ~m_heldButtons;

        m_heldButtons = inputMask;
    }

    ControllerInputImpl::ControllerInputImpl()
    {
        int gamepadCount{};
        const auto gamepadIds = SDL_GetGamepads(&gamepadCount);

        if (gamepadCount > 0)
        {
            m_pGamepad = SDL_OpenGamepad(gamepadIds[0]);
        }
    }


    ControllerInputImpl::~ControllerInputImpl()
    {
        SDL_CloseGamepad(m_pGamepad);
    }
}
