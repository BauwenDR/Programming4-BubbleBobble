#include <iostream>
#include <unordered_map>
#include <SDL3/SDL_gamepad.h>

#include "ControllerInput.hpp"
#include "InputManager.hpp"
#include "InputCommand.hpp"
#include "InputManagerPrivate.hpp"

namespace dae::Input::Controller
{
    const static std::pmr::unordered_map<SDL_GamepadButton, ControllerKey> m_buttonMap {
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

    class ControllerInput::Impl {
    public:
        void Bind(ControllerKey key, std::size_t controllerIndex, CommandTrigger triggerType, InputCommand *command);
        void Unbind(const InputCommand *inputCommand);

        void Update();

        Impl();
        ~Impl();
    private:
        std::vector<SDL_Gamepad*> m_gamepads{};
        std::unordered_map<SDL_Gamepad*, std::size_t> m_gamepadOrder{};

        std::vector<ControllerBinding> m_bindings{};

        // Variables to keep track of the current state of all controllers
        std::vector<uint16_t> m_pressedButtons{};
        std::vector<uint16_t> m_releasedButtons{};
        std::vector<uint16_t> m_heldButtons{};

        // Order in which keys were pressed, this matches the player ordering
        // If gamepad 1 presses a key first it is player 1, if then gamepad 0 presses a key they will be player 2
        // We limit the length to 2, as that is the max gamepads we support
        std::size_t m_currentAssignedPlayer{};

        void DetectGamepads();
    };

    ControllerInput::Impl::Impl() {
        DetectGamepads();
    }

    ControllerInput::Impl::~Impl() {
        for (const auto gamepadId : m_gamepads) {
            SDL_CloseGamepad(gamepadId);
        }
    }

    void ControllerInput::Impl::Bind(ControllerKey key, std::size_t controllerIndex, CommandTrigger triggerType, InputCommand *command)
    {
        m_bindings.emplace_back(key, controllerIndex, command, triggerType);
    }

    void ControllerInput::Impl::Unbind(const InputCommand *inputCommand)
    {
        std::erase_if(m_bindings, [inputCommand](const auto &element) { return element.command == inputCommand; });
    }

    void ControllerInput::Impl::Update()
    {
        // JS can only detect controllers after an input has been provided.
        // So we check each frame if any new controllers have been attached.
        DetectGamepads();
        if (m_gamepads.empty()) return;

        for (std::size_t index{0}; index < m_gamepads.size(); ++index) {
            const auto gamepad{m_gamepads[index]};
            uint16_t inputMask{};

            for (const auto&[sdlButton, controllerKey] : m_buttonMap) {
                if (SDL_GetGamepadButton(gamepad, sdlButton)) {
                    inputMask |= static_cast<int16_t>(controllerKey);
                }
            }

            const auto buttonChanges = m_heldButtons[index] ^ inputMask;
            m_pressedButtons[index] = buttonChanges & inputMask;
            m_releasedButtons[index] = buttonChanges & inputMask;

            m_heldButtons[index] = inputMask;

            if (inputMask > 0 && !m_gamepadOrder.contains(gamepad)) {
                std::cout << "Controller " << m_currentAssignedPlayer << " added \n";
                m_gamepadOrder[gamepad] = m_currentAssignedPlayer;
                ++m_currentAssignedPlayer;
            }

            if (!m_gamepadOrder.contains(gamepad)) continue;

            for (const auto &binding : m_bindings)
            {
                using enum CommandTrigger;

                if (binding.controllerIndex != m_gamepadOrder[gamepad]) continue;

                if (m_pressedButtons[index] & static_cast<uint16_t>(binding.key))
                {
                    ExecuteIfTriggerMatch(&binding, KeyDown);
                }

                if (m_releasedButtons[index] & static_cast<uint16_t>(binding.key))
                {
                    ExecuteIfTriggerMatch(&binding, KeyUp);
                }

                if (m_heldButtons[index] & static_cast<uint16_t>(binding.key))
                {
                    ExecuteIfTriggerMatch(&binding, KeyHeld);
                }
            }
        }
    }

    ControllerInput::ControllerInput()
        : m_impl(std::make_unique<Impl>())
    {
    }

    void ControllerInput::Impl::DetectGamepads() {
        int gamepadCount{};
        const auto gamepadIds{SDL_GetGamepads(&gamepadCount)};

        if (gamepadCount == std::ssize(m_gamepads)) return;

        m_gamepads.resize(gamepadCount);
        m_pressedButtons.resize(gamepadCount);
        m_releasedButtons.resize(gamepadCount);
        m_heldButtons.resize(gamepadCount);

        for (int index{0}; index < gamepadCount; ++index)
        {
            m_gamepads[index] = SDL_OpenGamepad(gamepadIds[index]);
        }
    }

    ControllerInput::~ControllerInput() = default;

    void ControllerInput::Bind(ControllerKey key, std::size_t controllerIndex, CommandTrigger triggerType, InputCommand *command) const {
        m_impl->Bind(key, controllerIndex, triggerType, command);
    }

    void ControllerInput::Unbind(const InputCommand *inputCommand) const {
        m_impl->Unbind(inputCommand);
    }

    void ControllerInput::Update() const {
        m_impl->Update();
    }
}
