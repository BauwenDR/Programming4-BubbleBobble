#include "ControllerInput.hpp"

#include <memory>
#include <vector>

#include "ControllerInputImpl.hpp"
#include "InputCommand.hpp"
#include "InputManagerPrivate.hpp"

namespace dae::InputManager::Controller
{
    std::vector<ControllerBinding> m_bindings{};
    std::unique_ptr<ControllerInput> controllerInputImpl{};

    void Initialize()
    {
        controllerInputImpl = std::make_unique<ControllerInputImpl>();
    }

    void Bind(ControllerKey key, CommandTrigger triggerType, InputCommand *command)
    {
        m_bindings.emplace_back(key, command, triggerType);
    }

    void Unbind(const InputCommand *inputCommand)
    {
        std::erase_if(m_bindings, [inputCommand](const auto key) {return key.command == inputCommand;});
    }

    void UpdateKeys()
    {
        controllerInputImpl->Update();

        const uint16_t pressedKeys = controllerInputImpl->GetHeldButtons();
        const uint16_t releasedKeys = controllerInputImpl->GetHeldButtons();
        const uint16_t heldKeys = controllerInputImpl->GetHeldButtons();

        for (const auto &binding : m_bindings)
        {
            using enum CommandTrigger;

            if (pressedKeys & static_cast<uint16_t>(binding.key))
            {
                ExecuteIfTriggerMatch(&binding, KeyDown);
            }

            if (releasedKeys & static_cast<uint16_t>(binding.key))
            {
                ExecuteIfTriggerMatch(&binding, KeyUp);
            }

            if (heldKeys & static_cast<uint16_t>(binding.key))
            {
                ExecuteIfTriggerMatch(&binding, KeyHeld);
            }
        }
    }
}
