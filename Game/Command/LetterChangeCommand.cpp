#include "LetterChangeCommand.hpp"

void game::LetterChangeCommand::Execute()
{
    if (m_isUp)
    {
        m_selector.CycleUp();
    } else
    {
        m_selector.CycleDown();
    }
}

game::LetterChangeCommand::LetterChangeCommand(NameSelector& selector, bool up)
    : m_selector(selector)
      , m_isUp(up)
{
}
