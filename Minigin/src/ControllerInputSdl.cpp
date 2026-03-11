#include "ControllerInput.hpp"
#include "InputManager.hpp"

namespace dae::InputManager::Controller
{
    SDLControllerInput::SDLControllerInput()
    {
        int gamepadCount{};
        auto gamepadIds = SDL_GetGamepads(&gamepadCount);

        if (gamepadCount > 0)
        {
            m_pGamepad = SDL_OpenGamepad(gamepadIds[0]);
        }
    }

    void SDLControllerInput::Update()
    {
        if (m_pGamepad == nullptr) return;

        uint16_t inputMask{};

        if (SDL_GetGamepadButton(m_pGamepad, SDL_GAMEPAD_BUTTON_DPAD_UP))
        {
            inputMask |= static_cast<int16_t>(ControllerKey::DpadUp);
        }

        if (SDL_GetGamepadButton(m_pGamepad, SDL_GAMEPAD_BUTTON_DPAD_DOWN))
        {
            inputMask |= static_cast<int16_t>(ControllerKey::DpadDown);
        }

        if (SDL_GetGamepadButton(m_pGamepad, SDL_GAMEPAD_BUTTON_DPAD_LEFT))
        {
            inputMask |= static_cast<int16_t>(ControllerKey::DpadLeft);
        }

        if (SDL_GetGamepadButton(m_pGamepad, SDL_GAMEPAD_BUTTON_DPAD_RIGHT))
        {
            inputMask |= static_cast<int16_t>(ControllerKey::DpadRight);
        }

        const auto buttonChanges = inputMask ^ m_heldButtons;
        m_pressedButtons = buttonChanges & m_heldButtons;
        m_releasedButtons = buttonChanges & ~m_heldButtons;

        m_heldButtons = inputMask;
    }

    SDLControllerInput::~SDLControllerInput()
    {
        SDL_CloseGamepad(m_pGamepad);
    }
}
