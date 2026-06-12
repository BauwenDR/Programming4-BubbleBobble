#include "ConfirmCommand.hpp"

void game::ConfirmCommand::Execute()
{
    m_selector.NextLetter();
}

game::ConfirmCommand::ConfirmCommand(NameSelector& selector)
    : m_selector(selector)
{
}
