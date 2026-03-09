#ifndef MINIGIN_INPUTMANAGER_HPP
#define MINIGIN_INPUTMANAGER_HPP
#include <SDL3/SDL_keycode.h>

class ICommand;

// Controller key abstracts away Xinput and SDL bindings
enum class CommandTrigger
{
	KeyDown,
	KeyUp,
	KeyHeld
};

enum class ControllerKey
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
		void Bind(SDL_Keycode key, CommandTrigger tiggerType, ICommand* command);
		void Bind(ControllerKey key, CommandTrigger triggerType, ICommand* command);
		bool ProcessInput();
	};
}

#endif