#include "InputManager.hpp"

#include <algorithm>
#include <vector>
#include <set>

#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>

#include "ICommand.hpp"

struct KeyboardBinding
{
	SDL_Keycode key;
	ICommand* command;
	CommandTrigger trigger;
};

namespace dae::InputManager
{
	std::set<SDL_Keycode> m_heldKeyboardKeys{};
	std::vector<KeyboardBinding> m_keyboardBindings{};

	void ExecuteIfTriggerMatch(const KeyboardBinding *binding, CommandTrigger commandTrigger)
	{
		// Extract some names into local variables for easier to read code
		const auto &trigger{binding->trigger};
		const auto &command{binding->command};

		if (trigger == commandTrigger)
		{
			command->Execute();
		}
	}
}

void dae::InputManager::Bind(SDL_Keycode key, CommandTrigger triggerType, ICommand *command)
{
	m_keyboardBindings.emplace_back(key, command, triggerType);
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;

	// Keyboard input
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		ImGui_ImplSDL3_ProcessEvent(&e);

		const SDL_Keycode keycode{e.key.key};
		const auto &binding{std::ranges::find_if(m_keyboardBindings, [keycode] (const auto key) {return key.key == keycode;})};

		// If there is no action using this key, there is no use in tracking it
		if (binding == m_keyboardBindings.end()) continue;

		if (e.type == SDL_EVENT_KEY_DOWN)
		{
			m_heldKeyboardKeys.emplace(keycode);
			ExecuteIfTriggerMatch(binding.base(), CommandTrigger::KeyDown);
		}

		if (e.type == SDL_EVENT_KEY_UP)
		{
			m_heldKeyboardKeys.erase(keycode);
			ExecuteIfTriggerMatch(binding.base(), CommandTrigger::KeyUp);
		}
	}

	// Trigger all held down events
	for (const auto keycode : m_heldKeyboardKeys)
	{
		const auto &binding{std::ranges::find_if(m_keyboardBindings, [keycode] (const auto key) {return key.key == keycode;})};
		if (binding == m_keyboardBindings.end()) continue;

		ExecuteIfTriggerMatch(binding.base(), CommandTrigger::KeyHeld);
	}

	// Controller input

	return true;
}
