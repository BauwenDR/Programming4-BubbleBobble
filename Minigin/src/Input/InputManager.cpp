#include "Input/InputManager.hpp"

#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>

#include "../../private/Input/ControllerInput.hpp"
#include "../../private/Input/KeyboardInput.hpp"

void dae::InputManager::Bind(SDL_Keycode key, Input::CommandTrigger tiggerType, ICommand *command) const {
	Input::Keyboard::Bind(key, tiggerType, command);
}

void dae::InputManager::Bind(Input::ControllerKey key, std::size_t controllerIndex, Input::CommandTrigger tiggerType, ICommand *command) const {
	m_controllerInput.Bind(key, controllerIndex, tiggerType, command);
}

void dae::InputManager::Unbind(const ICommand *inputCommand) const {
	Input::Keyboard::Unbind(inputCommand);
	m_controllerInput.Unbind(inputCommand);
}

bool dae::InputManager::ProcessInput() const {
	SDL_Event e;

	// Keyboard input
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		Input::Keyboard::ProcessEvent(e);
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	// Trigger all held down events
	Input::Keyboard::ProcessHeldKeys();

	// Controller input (all states)
	m_controllerInput.Update();

	return true;
}
