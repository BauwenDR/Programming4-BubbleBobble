#ifndef MINIGIN_INPUTMANAGER_HPP
#define MINIGIN_INPUTMANAGER_HPP
#include <SDL3/SDL_keycode.h>

class InputCommand;

// The kind of key command that will trigger the command to
// This type is also used to bridge between Controller and Keyboard input
enum class CommandTrigger : uint8_t
{
	KeyDown,
	KeyUp,
	KeyHeld
};

// Controller key abstracts away Xinput and SDL bindings
enum class ControllerKey : uint8_t
{
	DpadUp,
	DpadDown,
	DpadLeft,
	DpadRight,
	A,
	B,
	X,
	Y,
	L1,
	R1,
	L2,
	R2,
	Start,
	Select,
	LeftStick,
	RightStick,
};

namespace dae
{
	namespace InputManager {
		void Bind(SDL_Keycode key, CommandTrigger tiggerType, InputCommand* command);
		void Unbind(const InputCommand *inputCommand);

		// void Bind(ControllerKey key, CommandTrigger triggerType, ICommand* command);
		bool ProcessInput();

	};
}

#endif