#ifndef MINIGIN_INPUTMANAGER_HPP
#define MINIGIN_INPUTMANAGER_HPP
#include <SDL3/SDL_keycode.h>

#include "ControllerInput.hpp"
#include "Input.hpp"
#include "Singleton.hpp"

namespace dae::Input::Controller {
	class ControllerInput;
}

class InputCommand;

namespace dae {
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Bind(SDL_Keycode key, Input::CommandTrigger tiggerType, InputCommand *command) const;
		void Bind(Input::ControllerKey key, std::size_t controllerIndex, Input::CommandTrigger tiggerType, InputCommand *command) const;

		void Unbind(const InputCommand *inputCommand) const;

		[[nodiscard]] bool ProcessInput() const;

	private:
		Input::Controller::ControllerInput m_controllerInput{};
	};
}

#endif
