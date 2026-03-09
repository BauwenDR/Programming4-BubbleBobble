#include "InputManager.hpp"

#include <unordered_map>

#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>

#include "ICommand.hpp"

namespace dae::InputManager
{
	std::unordered_map<SDL_Keycode, ICommand*> m_keyboardBindings{};
	std::unordered_map<SDL_Keycode, ICommand*> m_controllerBindings{};
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP) {
			auto it = m_keyboardBindings.find({e.key.key, e.type});
			if (it != keyBindings.end()) {
				it->second->Execute();
			}
		}

		// etc...
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	return true;
}
