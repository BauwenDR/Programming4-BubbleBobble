#ifndef MINIGIN_MAINMENUCOMMAND_HPP
#define MINIGIN_MAINMENUCOMMAND_HPP
#include "Event/ICommand.hpp"

namespace game
{
    class MainMenuCommand final : public dae::ICommand
    {
    public:
        void Execute() override;
        ~MainMenuCommand() override = default;
    };
}

#endif //MINIGIN_MAINMENUCOMMAND_HPP
