#include "InputManager.hpp"
#include "InputManagerPrivate.hpp"

#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>

#include "ControllerInput.hpp"
#include "KeyboardInput.hpp"

void dae::InputManager::Init()
{
	Controller::Initialize();
}

void dae::InputManager::Bind(SDL_Keycode key, CommandTrigger tiggerType, InputCommand *command)
{
	Keyboard::Bind(key, tiggerType, command);
}

void dae::InputManager::Bind(ControllerKey key, CommandTrigger tiggerType, InputCommand *command)
{
	Controller::Bind(key, tiggerType, command);
}

void dae::InputManager::Unbind(const InputCommand *inputCommand)
{
	Keyboard::Unbind(inputCommand);
	Controller::Unbind(inputCommand);
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;

	// Keyboard input
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		Keyboard::ProcessEvent(e);
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	// Trigger all held down events
	Keyboard::ProcessHeldKeys();

	// Controller input (all states)
	Controller::UpdateKeys();

	return true;
}
