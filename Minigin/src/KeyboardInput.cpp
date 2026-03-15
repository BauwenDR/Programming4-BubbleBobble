#include "KeyboardInput.hpp"

#include <algorithm>
#include <set>
#include <vector>

#include "InputCommand.hpp"
#include "InputManagerPrivate.hpp"

namespace dae::Input::Keyboard
{
    std::set<SDL_Keycode> m_heldKeys{};
    std::vector<KeyboardBinding> m_bindings{};
}

void dae::Input::Keyboard::Bind(SDL_Keycode key, CommandTrigger triggerType, InputCommand *command)
{
    m_bindings.emplace_back(key, command, triggerType);
}

void dae::Input::Keyboard::Unbind(const InputCommand *inputCommand)
{
    std::erase_if(m_bindings, [inputCommand](const auto key) {return key.command == inputCommand;});
}

void dae::Input::Keyboard::ProcessEvent(const SDL_Event &event)
{
    const SDL_Keycode keycode{event.key.key};
    const auto &binding{std::ranges::find_if(m_bindings, [keycode] (const auto key) {return key.key == keycode;})};

    // If there is no action using this key, there is no use in tracking it
    if (binding == m_bindings.end()) return;

    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        m_heldKeys.emplace(keycode);
        ExecuteIfTriggerMatch(std::to_address(binding), CommandTrigger::KeyDown);
    }

    if (event.type == SDL_EVENT_KEY_UP)
    {
        m_heldKeys.erase(keycode);
        ExecuteIfTriggerMatch(std::to_address(binding), CommandTrigger::KeyUp);
    }
}

void dae::Input::Keyboard::ProcessHeldKeys()
{
    for (const auto &binding : m_bindings)
    {
        if (m_heldKeys.contains(binding.key))
        {
            ExecuteIfTriggerMatch(&binding, CommandTrigger::KeyHeld);
        }
    }
}
