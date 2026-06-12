#ifndef MINIGIN_LETTERCHANGECOMMAND_HPP
#define MINIGIN_LETTERCHANGECOMMAND_HPP
#include "Event/ICommand.hpp"
#include "Manager/NameSelector.hpp"

namespace game
{
    class LetterChangeCommand final : public dae::ICommand
    {
    public:
        void Execute() override;

        LetterChangeCommand(NameSelector &selector, bool up);
        ~LetterChangeCommand() override = default;

    private:
        NameSelector &m_selector;
        bool m_isUp{};
    };
}

#endif //MINIGIN_LETTERCHANGECOMMAND_HPP
