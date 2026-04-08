#ifndef MINIGIN_INPUTMANAGER_HPP
#define MINIGIN_INPUTMANAGER_HPP
#include <SDL3/SDL_keycode.h>

#include "../../private/Input/ControllerInput.hpp"
#include "Input.hpp"
#include "Singleton.hpp"

namespace dae::Input::Controller {
	class ControllerInput;
}

namespace dae {
	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Bind(SDL_Keycode key, Input::CommandTrigger tiggerType, ICommand *command) const;
		void Bind(Input::ControllerKey key, std::size_t controllerIndex, Input::CommandTrigger tiggerType, ICommand *command) const;

		void Unbind(const ICommand *inputCommand) const;

		[[nodiscard]] bool ProcessInput() const;

	private:
		Input::Controller::ControllerInput m_controllerInput{};
	};
}

#endif
