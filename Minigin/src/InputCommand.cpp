#include "InputCommand.hpp"

#include "InputManager.hpp"
#include "KeyboardInput.hpp"

void InputCommand::Execute() const
{
    m_function();
}

InputCommand::InputCommand(const std::function<void()> &onInput)
    : m_function(onInput)
{
}

InputCommand::~InputCommand()
{
    dae::Input::Keyboard::Unbind(this);
}
