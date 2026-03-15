#ifndef MINIGIN_KEYBOARDINPUT_HPP
#define MINIGIN_KEYBOARDINPUT_HPP
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>

#include "InputManager.hpp"

class InputCommand;

namespace dae::Input::Keyboard
{
    struct KeyboardBinding
    {
        SDL_Keycode key{};
        InputCommand* command{};
        CommandTrigger trigger{};
    };

    void Bind(SDL_Keycode key, CommandTrigger triggerType, InputCommand *command);
    void Unbind(const InputCommand *inputCommand);

    void ProcessEvent(const SDL_Event& event);
    void ProcessHeldKeys();
}
#endif //MINIGIN_KEYBOARDINPUT_HPP