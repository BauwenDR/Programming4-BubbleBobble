#include "ControllerInput.hpp"
#include "InputManagerPrivate.hpp"

#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

// TODO: test with 2 controllers on Windows
// When writing this implementation I only had one (XInput compatible) Controller laying around
// I will test with multiple controllers when I can get my hand on some (most likely when going home)
// For the time being this class is only guaranteed to work with one controller

namespace dae::Input::Controller
{
    class ControllerInput::Impl {
    public:
        void Bind(ControllerKey key, size_t controllerIndex, CommandTrigger triggerType, ICommand *command);
        void Unbind(const ICommand *inputCommand);

        void Update();

    private:
        constexpr static uint8_t MAX_CONTROLLERS{2};

        std::vector<ControllerBinding> m_bindings{};

        // Variables to keep track of the current state of all controllers
        std::array<uint16_t, MAX_CONTROLLERS> m_pressedButtons{};
        std::array<uint16_t, MAX_CONTROLLERS> m_releasedButtons{};
        std::array<uint16_t, MAX_CONTROLLERS> m_heldButtons{};
    };

    void ControllerInput::Impl::Bind(ControllerKey key, std::size_t controllerIndex, CommandTrigger triggerType, ICommand *command)
    {
        m_bindings.emplace_back(key, controllerIndex, command, triggerType);
    }

    void ControllerInput::Impl::Unbind(const ICommand *inputCommand)
    {
        std::erase_if(m_bindings, [inputCommand](const auto &element) { return element.command == inputCommand; });
    }

    void ControllerInput::Impl::Update()
    {
        for (uint8_t index{0}; index < MAX_CONTROLLERS; ++index) {
            XINPUT_STATE state{};
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            const auto xInputState{ XInputGetState(index, &state) };

            if (xInputState != ERROR_SUCCESS) return;

            const uint16_t inputMask{state.Gamepad.wButtons};

            const uint16_t buttonChanges = m_heldButtons[index] ^ inputMask;
            m_pressedButtons[index] = buttonChanges & inputMask;
            m_releasedButtons[index] = buttonChanges & ~inputMask;

            m_heldButtons[index] = inputMask;

            for (const auto &binding : m_bindings)
            {
                using enum CommandTrigger;

                if (binding.controllerIndex != index) continue;

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

    ControllerInput::~ControllerInput() = default;

    void ControllerInput::Bind(ControllerKey key, std::size_t controllerIndex, CommandTrigger triggerType, ICommand *command) const {
        m_impl->Bind(key, controllerIndex, triggerType, command);
    }

    void ControllerInput::Unbind(const ICommand *inputCommand) const {
        m_impl->Unbind(inputCommand);
    }

    void ControllerInput::Update() const {
        m_impl->Update();
    }
}
