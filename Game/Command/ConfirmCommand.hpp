#ifndef MINIGIN_CONFIRMCOMMAND_HPP
#define MINIGIN_CONFIRMCOMMAND_HPP
#include "Event/ICommand.hpp"
#include "Manager/NameSelector.hpp"

namespace game
{
    class ConfirmCommand final : public dae::ICommand
    {
    public:
        void Execute() override;

        explicit ConfirmCommand(NameSelector &selector);
        ~ConfirmCommand() override = default;

    private:
        NameSelector &m_selector;
    };
}

#endif //MINIGIN_CONFIRMCOMMAND_HPP
